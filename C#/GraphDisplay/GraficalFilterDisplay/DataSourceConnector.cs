using Arduino.Serial;
using GraphLib;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GraficFilterDisplay
{

    class DataSourceSerialConnector
    {
        Dictionary<int, DataSource> dsDict = new Dictionary<int, DataSource>();
        COMSettings _com;
        
        public NewMessageReceived OnNewMessageDetected = null;
        public NewSampleDetected OnNewSampleDetected = null;

        SerialFIFO serial = new SerialFIFO();
        public DataSourceSerialConnector()
        {
            serial.OnNewMessage = OnNewMessageReceived;
        }

        public void Clear()
        {
            dsDict.Clear();
        }

        public void ComPort(COMSettings com)
        {
            _com = com;
            serial.Init(_com);
            //serial.OnNewMessage

        }

        public void Send(string msg)
        {
            serial.UserKeyInput(msg);
        }

        public void Add(DataSource src, int index)
        {
            dsDict[index] = src;
            dsDict[index].DataCursor = 0;
        }

        public void Stop()
        {
            serial.Close();
        }
        public void Start()
        {
            if (serial.IsRunnig())
                serial.Close();
            serial.Open();
        }

        public bool OnNewMessageReceived(string newMsg)
        {
            newMsg = newMsg.Replace("\r", "");
            
            string[] parameter = newMsg.Split('|');
            foreach (string param in parameter)
            {
                string[] kv = param.Split(':');
                if (kv.Length != 2)
                {
                    OnNewMessageDetected?.Invoke(param + "\r\n");
                    continue;
                }

                try
                {
                    int idx = Convert.ToInt32(kv[0]);
                    kv[1] = kv[1].Replace('.', ',');
                    double value = Convert.ToDouble(kv[1]);
                    OnNewSampleDetected?.Invoke(idx, value, false);
                }
                catch {
                    OnNewMessageDetected?.Invoke(newMsg + "\r\n");
                }
            }

            return true;
        }


    }
}
