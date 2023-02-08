using System;
using System.Collections.Generic;
using ArduGui.Model;

namespace ArduGui.Controller
{
    public delegate bool NewMessageReceived(string newMsg);
    public delegate bool UserKeyInput(string msgStr);
    public delegate Value[] LoadDataFunction(int ID, DateTime from, DateTime to, bool FromValue);

    public interface IViewObserver
    {
        string Id { get; set; }
        IModelContainer dataContainer { get; set; }
        bool NotifyChanges(MessageItem msg);
        LoadDataFunction LoadDBData { get; set; }
    }

    public interface IMessageAdapter
    {
        NewMessageReceived OnNewMessage { get; set; }
        bool IsRunnig();
        bool Open();
        bool Close();
        bool UserKeyInput(string msgStr);
    }

    public class MessageAdapterFactory
    {
        public static IMessageAdapter Create(COMSettings settings, NewMessageReceived MsgSink)
        {
            SerialFIFO serIO = new SerialFIFO();
            serIO.OnNewMessage += MsgSink;
            serIO.Init(settings);
            return serIO;
        }
    }

}