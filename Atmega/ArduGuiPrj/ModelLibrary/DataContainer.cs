using System;
using System.Collections.Generic;

using ArduGui.Controller;

namespace ArduGui.Model
{
    public delegate bool NotifyChanges();

    public class Value
    {
        double _value;
        public double Val
        {
            get { return _value; }
            set { _value = value; }
        }

        DateTime _timestamp;
        public DateTime Timestamp
        {
            get { return _timestamp; }
            set { _timestamp = value; }
        }
        public Value(double value, DateTime timestamp)
        {
            Val = value;
            Timestamp = timestamp;
        }
    }

    public interface IModelContainer
    {
        bool AddObserver(IViewObserver newObserver);
        bool Reset();
        string LastRawMessage();
        bool MessageReceiver(string newMsg);
        bool UserKeyInput(string ch);
    }

    public class SimpleDispatch : IModelContainer
    {
        public UserKeyInput OnKeyInput;
        static object LockDispatcher;
        List<String> m_RawMsg;
        List<IViewObserver> NewObserverList;
        List<IViewObserver> ObserverList;
        string m_LastMessage;

        public SimpleDispatch()
        {
            LockDispatcher = new object();
            Reset();
        }

        public bool UserKeyInput(string ch)
        {
            if (OnKeyInput != null)
            {
                return OnKeyInput(ch);
            }
            return false;
        }
        public bool AddObserver(IViewObserver newObserver)
        {
            NewObserverList.Add(newObserver);
            newObserver.dataContainer = this;
            return true;
        }
        public List<String> RawMsgBuffer
        {
          get { return m_RawMsg; }
          set { m_RawMsg = value; }
        }

        public bool Reset()
        {
            m_LastMessage = "";
            RawMsgBuffer = new List<String>();
            ObserverList = new List<IViewObserver>();
            NewObserverList = new List<IViewObserver>();
            return true;
        }
        
        public string LastRawMessage()
        {
            lock (LockDispatcher)
            {
                return m_LastMessage;
            }
        }

        bool ObserverRegistered(IViewObserver rObs)
        {
            foreach (IViewObserver obs in ObserverList)
            {

                if (Object.Equals(obs, rObs)) return true;
            }
            return false;
        }

        public bool MessageReceiver(string newMsg)
        {
            lock (LockDispatcher)
            {
                m_LastMessage = newMsg;
                m_RawMsg.Add(newMsg);
            }
            if (NewObserverList.Count > 0)
            {
                foreach (IViewObserver obs in NewObserverList)
                {
                    if (!ObserverRegistered(obs))
                        ObserverList.Add(obs);
                }
                NewObserverList.Clear();
            }
            
            MessageItem msg = MessageTranslater.StringToMsg(m_LastMessage);
            if (msg.Type == MessageType.Configuration)
            {
                GuiCommand currentGuiCommand = GuiConfigCommands.GetGuiCommandType(msg.Content);
                if (currentGuiCommand == GuiCommand.TimeSync)
                {
                    MessageTranslater.SyncTimestamp = DateTime.Now;
                    MessageTranslater.Sync_uCTicks = Convert.ToUInt32(msg.uCTicks);
                    //return true;
                }
            }
            if (MessageTranslater.Sync_uCTicks != 0)
            {
                int diff = Convert.ToInt32(msg.uCTicks) - (int)MessageTranslater.Sync_uCTicks;
                msg.Timestamp = MessageTranslater.SyncTimestamp.AddMilliseconds(diff);
            }
            else
            {
                msg.Timestamp = DateTime.Now;
            }
            try
            {
                foreach (IViewObserver obs in ObserverList)
                    obs.NotifyChanges(msg);
            }
            catch
            {
            }

            return true;
        }
    }
}