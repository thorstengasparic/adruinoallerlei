using System;
using System.Collections.Generic;

namespace ArduGui.Model
{
    public enum GuiCommand { Unknown, InitProject, Reset, TimeSync, InitTextbox,InitCharts, InitSliderBar };
    public class GuiConfigCommands
    {
        #region Common
        public static GuiCommand GetGuiCommandType(string Command)
        {
            if (Command.ToUpper().Equals("RESET")) return GuiCommand.Reset;
            if (Command.ToUpper().Equals("SYNC")) return GuiCommand.TimeSync;
            string[] cmdArr = Command.Split('_');
            if (cmdArr[0].Equals("00")) return GuiCommand.InitProject;
            if (cmdArr[0].Equals("01")) return GuiCommand.InitTextbox;
            if (cmdArr[0].Equals("02")) return GuiCommand.InitSliderBar;
            if (cmdArr[0].Equals("03")) return GuiCommand.InitCharts;
            return GuiCommand.Unknown;
        }
        #endregion
        #region CmdReset
        public static string CmdReset()
        {
            return "RESET";
        }
        #endregion
        #region CmdInitProject
        public static string CmdInitProject(string Name, string Description)
        {
            return string.Format("00_{0}_{1}", Name, Description);
        }
        public static bool ExtractInitProjectCmd(string msg, out string Name, out string Description)
        {
            Name = "";
            Description = "";
            string[] cmdArr = msg.Split('_');
            if (cmdArr.Length != 3) return false;
            Name = cmdArr[1];
            Description = cmdArr[2];
            return true;
        }
        #endregion
        #region CmdInitTextBox
        public static string CmdInitTextBox(string BoxNumber, string HeaderText, string UnitText, string VarId)
        {
            return string.Format("01_{0}_{1}_{2}_{3}", BoxNumber, HeaderText, UnitText, VarId);
        }
        public static bool ExtractTextBoxCmd(string msg, out string BoxNumber, out string HeaderText, out string UnitText, out string VarId)
        {
            BoxNumber = ""; 
            HeaderText = "";            
            UnitText = "";            
            VarId = "";

            string[] cmdArr = msg.Split('_');
            if (cmdArr.Length != 5) return false;

            BoxNumber =cmdArr[1];
            HeaderText=cmdArr[2];
            UnitText=cmdArr[3];
            VarId = cmdArr[4];
            return true;
        }
        #endregion
        #region CmdInitSlider
        public static string CmdInitSlider(string BoxNumber, string HeaderText, string UnitText, string VarId, double min, double max)
        {
            return string.Format("02_{0}_{1}_{2}_{3}_{4}_{5}", BoxNumber, HeaderText, UnitText, VarId, min, max);
        }
        public static bool ExtractSliderCmd(string msg, out string BoxNumber, out string HeaderText, out string UnitText, out string VarId, out double min, out double max)
        {
            BoxNumber = "";
            HeaderText = "";
            UnitText = "";
            VarId = "";
            min = 0;
            max = 0;

            string[] cmdArr = msg.Split('_');
            if (cmdArr.Length != 7) return false;

            BoxNumber = cmdArr[1];
            HeaderText = cmdArr[2];
            UnitText = cmdArr[3];
            VarId = cmdArr[4];
            min = Convert.ToDouble(cmdArr[5]);
            max = Convert.ToDouble(cmdArr[6]);

            return true;
        }
        #endregion
        #region CmdInitCharts
        public static string CmdInitCharts(int chartNo, int varID, string GraphName, string UnitText, double min, double max)
        {
            return string.Format("03_{0}_{1}_{2}_{3}_{4}_{5}", chartNo.ToString(), varID.ToString(), GraphName, UnitText, min.ToString(), max.ToString());
        }
        public static bool ExtractChartCmd(string msg, out int chartNo, out int varId, out string GraphName, out string UnitText, out double min, out double max)
        {
            chartNo = 0;
            GraphName = "";
            UnitText = "";
            varId = -1;
            min = 0;
            max = 0;

            string[] cmdArr = msg.Split('_');
            if (cmdArr.Length != 7) return false;

            chartNo = Convert.ToInt32(cmdArr[1]);
            varId = Convert.ToInt32(cmdArr[2]);
            GraphName = cmdArr[3];
            UnitText = cmdArr[4];
            
            min = Convert.ToDouble(cmdArr[5]);
            max = Convert.ToDouble(cmdArr[6]);

            return true;
        }
        #endregion
    }
}