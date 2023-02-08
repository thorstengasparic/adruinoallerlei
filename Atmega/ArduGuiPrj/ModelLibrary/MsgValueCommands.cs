using System;
using System.Collections.Generic;

namespace ArduGui.Model
{
    public enum ValueCommandType { Unknown, Text, Float};
    public class ValueCommand
    {
        #region Common
        public static ValueCommandType GetCommandType(string Command)
        {
            string[] cmdArr = Command.Split('_');
            if (cmdArr[0].Equals("00")) return ValueCommandType.Text;
            if (cmdArr[0].Equals("01")) return ValueCommandType.Float;
            return ValueCommandType.Unknown;
        }
        #endregion

        #region StringCmd
        public static string CmdStringValue(string ViewID, string content)
        {
            return string.Format("00_{0}_{1}", ViewID, content);
        }
        #endregion

        #region DoubleCmd
        public static string CmdDoubleValue(string ViewID, double content)
        {
            return string.Format("01_{0}_{1}", ViewID, content.ToString());
        }
        public static bool ExtractDouble(string msg, out string ViewID, out double content)
        {
            ViewID = "";
            content = 0.0f;
            string[] cmdArr = msg.Split('_');
            if (cmdArr.Length < 3) return false;
            ViewID = cmdArr[1];
            content = Convert.ToDouble(cmdArr[2].Replace(".", ","));
            return true;
        }
        #endregion

        #region InitProjectCmd
        public static bool ExtractInitProjectCmd(string msg, out string ViewID, out string content)
        {
            ViewID = "";
            content = "";
            string[] cmdArr = msg.Split('_');
            if (cmdArr.Length < 3) return false;
            ViewID = cmdArr[1];
            content = cmdArr[2];
            return true;
        }
        #endregion
    }
}
