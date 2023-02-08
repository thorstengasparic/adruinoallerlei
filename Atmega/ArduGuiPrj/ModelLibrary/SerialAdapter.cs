
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.Threading;
using ArduGui.Controller;

namespace ArduGui.Controller
{
    public class COMSettings
    {
        public string PortName = "";
        public string BaudRate = "";
        public string Parity = "";
        public string DataBits = "";
        public string StopBits = "";
        public string Handshake = "";
        public COMSettings()
        {
            PortName = "COM3";
            BaudRate = "115200";
            Parity = "None";
            DataBits = "8";
            StopBits = "One";
            Handshake = "None";
        }
    }

    public class SerialFIFO : IMessageAdapter
    {
        bool m_continue;
        SerialPort SerialPort;

        public NewMessageReceived m_OnNewMessage;
        static object lockthis = null;
        int currentIndex;
        public List<string> strListIncommingMsg = null;
        Thread readThread = null;
        Thread dispatchThread = null;

        public NewMessageReceived OnNewMessage
        {
            get
            {
                return m_OnNewMessage;
            }

            set
            {
                m_OnNewMessage += value;
            }
        }
        public bool IsRunnig()
        {
            return m_continue;
        }
        public SerialFIFO()
        {
            OnNewMessage = null;
            if (lockthis == null) lockthis = new object();
            currentIndex = 0;
            strListIncommingMsg = new List<string>();
            m_continue = false;
            SerialPort = new SerialPort();
        }
        public bool Init(COMSettings com)
        {
            return Init(com.PortName, com.BaudRate, com.Parity, com.DataBits, com.StopBits, com.Handshake);
        }
        bool Init(string portName, string baudRate, string parity, string dataBits, string stopBits, string handshake)
        {
            try
            {
                this.SerialPort.PortName = portName;
                this.SerialPort.BaudRate = int.Parse(baudRate);
                this.SerialPort.Parity = (Parity)Enum.Parse(typeof(Parity), parity);
                this.SerialPort.DataBits = int.Parse(dataBits);
                this.SerialPort.StopBits = (StopBits)Enum.Parse(typeof(StopBits), stopBits);
                this.SerialPort.Handshake = (Handshake)Enum.Parse(typeof(Handshake), handshake);
                this.SerialPort.ReadTimeout = 1000;
                return true;
            }
            catch (Exception ex)
            {
                PumpMessage("Init failed: " + ex.Message);
            }
            return false;
        }
        
        void PumpMessage(string msg)
        {
            if (OnNewMessage != null)
                OnNewMessage(msg);
        }
        public bool Open()
        {
            try
            {
                if (SerialPort.IsOpen) SerialPort.Close();
                SerialPort.Open();
                dispatchThread = new Thread(DispatchFunction);
                readThread = new Thread(ReadFunction);
                dispatchThread = new Thread(DispatchFunction);

                m_continue = true;
                dispatchThread.Start();
                readThread.Start();
            }
            catch (Exception ex)
            {
                PumpMessage("Open failed: " + ex.Message);
                return false;
            }

            return true;
        }
        public bool Close()
        {
            m_continue = false;
            lock (lockthis)
            {
                strListIncommingMsg.Clear();
            }
            try
            {
                readThread.Join(1000);
                dispatchThread.Join(1000);
            }
            catch { }
            return true;
        }

        public bool UserKeyInput(string msgStr)
        {
            lock (lockthis)
            {
                try
                {
                    if (SerialPort.IsOpen)
                    {
                        this.SerialPort.WriteLine(msgStr);
                        return true;
                    }
                    else
                    {
                        PumpMessage("Cannot send \""+msgStr+"\": Serial port not open");
                    }
                }
                catch (Exception ex) 
                {
                    PumpMessage(ex.Message);
                }
            }
            return false;
        }

        public void ReadFunction()
        {
            this.SerialPort.DiscardOutBuffer();
            this.SerialPort.DiscardInBuffer();
            while (m_continue)
            {
                try
                {
                    //if (strListIncommingMsg.Count == 0)
                    {
                        string msg = this.SerialPort.ReadLine();
                        lock (lockthis)
                        {
                            strListIncommingMsg.Add(msg);
                        }
                    }

                }
                catch (Exception ex)
                {
                    if (ex.GetType() != typeof(TimeoutException))
                    {
                        PumpMessage(ex.Message);
                    }
                    else
                    {
                    }
                }
            }
            lock (lockthis)
            {
                strListIncommingMsg.Clear();
            }

            SerialPort.Close();
        }

        public void DispatchFunction()
        {
            while (m_continue)
            {
                try
                {
                    string newMsg = null;
                    lock (lockthis)
                    {
                        if (strListIncommingMsg.Count > 0)
                        {
                            newMsg = strListIncommingMsg[0];
                            strListIncommingMsg.RemoveAt(0);
                        }
                    }
                    if (newMsg != null)
                    {
                        PumpMessage(newMsg);
                        Thread.Sleep(1);
                        continue; // flush fifo without delay
                    }
                }
                catch (TimeoutException ex)
                {
                    PumpMessage(ex.Message);
                }
                Thread.Sleep(10);
            }
        }

    }
}