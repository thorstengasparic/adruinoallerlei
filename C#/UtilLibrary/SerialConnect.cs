using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;

namespace Arduino.Serial
{
    public class COMSettings
    {
        public string PortName { get; set; }
        public string BaudRate { get; set; }
        public string Parity { get; set; }
        public string DataBits { get; set; }
        public string StopBits { get; set; }
        public string Handshake { get; set; }
        public COMSettings()
        {
            PortName = "COM3";
            BaudRate = "115200";
            Parity = "None";
            DataBits = "8";
            StopBits = "One";
            Handshake = "None";
        }
        public override string ToString()
        {
            return PortName + "," + BaudRate;
        }
    }

    public class SerialConfig
    {
        public static string[] Ports
        { 
            get{
                List<string> lst = new List<string>();
                foreach (string s in SerialPort.GetPortNames())
                {
                    lst.Add(s);
                }
                return lst.ToArray();
            }
            
        }
        public static string[] BaudRates
        {
            get
            {
                List<string> lst = new List<string>();
                lst.Add("300");
                lst.Add("1200");
                lst.Add("2400");
                lst.Add("9600");
                lst.Add("19200");
                lst.Add("38400");
                lst.Add("57600");
                lst.Add("74880");
                lst.Add("115200");
                lst.Add("230400");
                lst.Add("250000");
                lst.Add("500000");
                return lst.ToArray();
            }
        }

    }

    public delegate bool SerialNewMessageReceived(string newMsg);
    public class SerialFIFO : IMessageAdapter
    {

        SerialNewMessageReceived m_OnNewMessage;
        COMSettings _com = new COMSettings();
        bool m_continue;
        SerialPort serPort;
        static object lockthis = null;
        public List<string> strListIncommingMsg = null;
        Thread readThread = null;
        Thread dispatchThread = null;

        public SerialNewMessageReceived OnNewMessage
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
            strListIncommingMsg = new List<string>();
            m_continue = false;
            serPort = null;
        }

        public void Init(COMSettings com)
        {
            _com = com;
        }

        void PumpMessage(string msg)
        {
            OnNewMessage?.Invoke(msg);
        }
        public bool Open()
        {
            try
            {
                
                dispatchThread = new Thread(DispatchFunction);
                readThread = new Thread(ReadFunction);
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
        private void SerialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            // The event will also be fired for EofChar (byte 0x1A), ignore it
            if (e.EventType == SerialData.Eof)
                return;
            try {
                string indata = serPort.ReadLine();
                //PumpMessage(indata);
                lock (lockthis)
                {
                    strListIncommingMsg.Add(indata);
                    dataAvail.Set();
                }
            }
            catch (Exception ex)
            {
                PumpMessage(ex.Message);
            }
            
            return;
            
            //// Read the BytesToRead value, 
            //// don't assume it's exactly ReceivedBytesThreshold
            //byte[] buffer = new byte[serPort.BytesToRead];
            //serPort.Read(buffer, 0, buffer.Length);
            //string result = System.Text.Encoding.UTF8.GetString(buffer);
            //Console.Write(result);

            //// ... Process the buffer ...
            //        //Console.Write(serPort.ReadExisting());
            //PumpMessage(serPort.ReadLine());
            ////Console.WriteLine(serPort.ReadLine());
            ////string msg = serPort.ReadLine();


        }

        public bool Close()
        {
            m_continue = false;
            dataAvail.Set();
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

        string outstr = "";
        public bool UserKeyInput(string msgStr)
        {
            
            try
            {
                lock (lockthis)
                {
                    outstr = msgStr;
                }
                dataSend.Set();
            }
            catch (Exception ex)
            {
                PumpMessage(ex.Message);
            }
            return false;
        }

        static ManualResetEvent dataAvail = new ManualResetEvent(false);
        static ManualResetEvent dataSend = new ManualResetEvent(false);
        public void ReadFunction()
        {
            int buffersize = 1;
            if (this.serPort != null)
            {
                if (serPort.IsOpen) serPort.Close();
            }
            else {
                this.serPort = new SerialPort();
                serPort.DataReceived += SerialPort1_DataReceived;
            }
            this.serPort.PortName = _com.PortName;
            this.serPort.BaudRate = Convert.ToInt32(_com.BaudRate);
            // To be safe, set the buffer size as double the size you want to read once
            // This is for the case when the system is busy and delays the event processing
            this.serPort.ReadBufferSize = 1024;
            this.serPort.ReceivedBytesThreshold = 1;
            try
            {
                serPort.Open();
            }
            catch { serPort = null;  return; }

            this.serPort.DiscardOutBuffer();
            this.serPort.DiscardInBuffer();
            while (m_continue)
            {
                try
                {
                    dataSend.WaitOne();
                    lock (lockthis)
                    {
                        if (outstr.Length> 0)
                        {
                            this.serPort.Write(outstr);

                            outstr = "";
                        }
                    }
                }
                catch (Exception ex)
                {
                    if (ex.GetType() != typeof(TimeoutException))
                    {
                        PumpMessage(ex.Message);
                    }
                }
            }
            lock (lockthis)
            {
                strListIncommingMsg.Clear();
            }
            try
            {
                serPort.Close();
            }
            catch { }
        }

        public void DispatchFunction()
        {
            while (m_continue)
            {
                try
                {
                    string newMsg = null;
                    if (strListIncommingMsg.Count == 0) dataAvail.WaitOne();
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
                        //Thread.Sleep(1);
                        continue; // flush fifo without delay
                    }
                }
                catch (TimeoutException ex)
                {
                    PumpMessage(ex.Message);
                }
                
            }
        }

    }
}