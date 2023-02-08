using System;
using System.Collections.Generic;

namespace ArduGui.Model
{
    
    public enum MessageType { Error, Information, Variable, Configuration, Unknown };
    public class MessageItem 
    {
        public MessageType Type;
        public DateTime Timestamp;
        public string uCTicks;
        public string Content;
        public string RawMessage;
    }

    public class MessageTranslater
    {
        static public DateTime SyncTimestamp = DateTime.Now;
        static public long Sync_uCTicks = 0;

        public static string MsgToString(MessageType type, string ticks, string Content)
        {
            string strT = "";
            switch (type)
            {
                case MessageType.Error: strT = "E"; break;
                case MessageType.Information: strT = "I"; break;
                case MessageType.Variable: strT = "V"; break;
                case MessageType.Configuration: strT = "C"; break;
            }
            return string.Format("{0}_{1}_{2}",strT, ticks, Content);
        }
        public static MessageItem StringToMsg(string Message)
        {
            //Messageformat type_ticks_varid_content
            MessageItem msg = new MessageItem();
            Message = Message.TrimEnd('\r');
            msg.RawMessage = Message;
            msg.Type = MessageType.Unknown;
            msg.Content = Message;

            string[] msgToken = Message.Split('_');
            if (msgToken.Length < 3) return msg;

            char t = msgToken[0][0];
            switch (t)
            {
                case 'E': msg.Type = MessageType.Error; break;
                case 'I': msg.Type = MessageType.Information; break;
                case 'V': msg.Type = MessageType.Variable; break;
                case 'C': msg.Type = MessageType.Configuration; break;
            }
            
            if (msg.Type == MessageType.Unknown)
                return msg;

            msg.uCTicks = msgToken[1];
            msg.Content = "";
            for (int i = 2; i < msgToken.Length; i++ )
            {
                if (msg.Content.Length > 0) msg.Content += "_";
                msg.Content += msgToken[i];
            }
            return msg;
        }
    }
}
