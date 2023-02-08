using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace Arduino.Serial
{
    public interface IMessageAdapter
    {
        SerialNewMessageReceived OnNewMessage { get; set; }
        bool IsRunnig();
        bool Open();
        bool Close();
        bool UserKeyInput(string msgStr);
    }

    public class MessageAdapterFactory
    {
        public static IMessageAdapter Create(COMSettings settings, SerialNewMessageReceived MsgSink)
        {
            SerialFIFO serIO = new SerialFIFO();
            serIO.OnNewMessage = MsgSink;
            serIO.Init(settings);
            return serIO;
        }
    }
    class SerialMessages
    {
    }
}