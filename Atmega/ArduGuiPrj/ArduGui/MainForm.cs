using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Xml.Serialization;
using System.Windows.Media;

using ArduGui.Settings;
using ArduGui.Controller;
using ArduGui.Model;
using ArduGui.View;
using ArdoGui.ViewControls;

namespace ArduGui
{
    public partial class Form1 : BaseViewForm
    {
        AppSettings appSetting = null;
        IMessageAdapter msgAdapter = null;
        SimpleDispatch Dispatcher = null;

        ViewTextBox[] ViewTextBoxArr = null;
        ViewSlider[] ViewSliderArr = null;
        GuiDBAccess guiDB = new GuiDBAccess();

        string m_prjName = "default.xml";

        int Count = 0;
        public Form1()
        {
            #region InitializeComponents
            InitializeComponent();
            ViewTextBoxArr = new ViewTextBox[12];
            ViewTextBoxArr[0] = viewTextBox1;
            ViewTextBoxArr[1] = viewTextBox2;
            ViewTextBoxArr[2] = viewTextBox3;
            ViewTextBoxArr[3] = viewTextBox4;
            ViewTextBoxArr[4] = viewTextBox5;
            ViewTextBoxArr[5] = viewTextBox6;
            ViewTextBoxArr[6] = viewTextBox7;
            ViewTextBoxArr[7] = viewTextBox8;
            ViewTextBoxArr[8] = viewTextBox9;
            ViewTextBoxArr[9] = viewTextBox10;
            ViewTextBoxArr[10] = viewTextBox11;
            ViewTextBoxArr[11] = viewTextBox12;

            ViewSliderArr = new ViewSlider[9];
            ViewSliderArr[0] = viewSlider1;
            ViewSliderArr[1] = viewSlider2;
            ViewSliderArr[2] = viewSlider3;
            ViewSliderArr[3] = viewSlider4;
            ViewSliderArr[4] = viewSlider5;
            ViewSliderArr[5] = viewSlider6;
            ViewSliderArr[6] = viewSlider7;
            ViewSliderArr[7] = viewSlider8;
            ViewSliderArr[8] = viewSlider9;

            
            
            guiDB.StoreValueInDB(1, DateTime.Now, 100.0);
            
            //viewTextBox1.Parent = splitContainer1.Panel1;
            //viewMsgListVar.Parent = splitContainer1.Panel2;
            #endregion
            Dispatcher = new SimpleDispatch();
            Dispatcher.OnKeyInput += UserKeyInput;
            Dispatcher.AddObserver(this);
            Dispatcher.AddObserver(viewMsgListVar);
            appSetting = new AppSettings();
            Dispatcher.AddObserver(guiDB);
            
            msgAdapter = MessageAdapterFactory.Create(appSetting.COMParmas, ThreadSaveMsgSink);
            //timer1.Enabled = true;
        }
        public bool UserKeyInput(string ch)
        {
            msgAdapter.UserKeyInput(ch);
            return true;
        }
        void TestSetup()
        {
            string Content = GuiConfigCommands.CmdReset();
            string msg = MessageTranslater.MsgToString(MessageType.Configuration, "0", Content);
            ThreadSaveMsgSink(msg);

            Content = GuiConfigCommands.CmdInitProject("testprj2.xml", "Testdescription");
            msg = MessageTranslater.MsgToString(MessageType.Configuration, "0", Content);
            ThreadSaveMsgSink(msg);

            Content = GuiConfigCommands.CmdInitCharts(0, 10, "TempSHT", "°C", -20, 50);
            msg = MessageTranslater.MsgToString(MessageType.Configuration, "0", Content);
            ThreadSaveMsgSink(msg);

            Content = GuiConfigCommands.CmdInitCharts(0, 11, "Feuchte", "%", 0, 100);
            msg = MessageTranslater.MsgToString(MessageType.Configuration, "0", Content);
            ThreadSaveMsgSink(msg);

            Content = GuiConfigCommands.CmdInitCharts(1, 10, "Dew", "°C", -20, 50);
            msg = MessageTranslater.MsgToString(MessageType.Configuration, "0", Content);
            ThreadSaveMsgSink(msg);

            Content = ValueCommand.CmdDoubleValue("10", 10.0);
            msg = MessageTranslater.MsgToString(MessageType.Variable, DateTime.Now.AddSeconds(-5).Ticks.ToString(), Content);
            ThreadSaveMsgSink(msg);


            return;

            Content = GuiConfigCommands.CmdInitTextBox("0", "TestVar", "°C", "01");
            msg = MessageTranslater.MsgToString(MessageType.Configuration, "0", Content);
            ThreadSaveMsgSink(msg);

            Content = GuiConfigCommands.CmdInitTextBox("1", "TestVar", "U/Min", "02");
            msg = MessageTranslater.MsgToString(MessageType.Configuration, "0", Content);
            ThreadSaveMsgSink(msg);

            Content = GuiConfigCommands.CmdInitTextBox("2", "TestVar", "°C", "03");
            msg = MessageTranslater.MsgToString(MessageType.Configuration, "0", Content);
            ThreadSaveMsgSink(msg);

            Content = GuiConfigCommands.CmdInitTextBox("3", "TestVar", "°C", "04");
            msg = MessageTranslater.MsgToString(MessageType.Configuration, "0", Content);
            ThreadSaveMsgSink(msg);

            Content = GuiConfigCommands.CmdInitSlider("6", "Test1", "°C", "01", 0, 100);
            msg = MessageTranslater.MsgToString(MessageType.Configuration, "0", Content);
            ThreadSaveMsgSink(msg);

            Content = GuiConfigCommands.CmdInitSlider("8", "Test2", "°C", "02", 0, 100);
            msg = MessageTranslater.MsgToString(MessageType.Configuration, "0", Content);
            ThreadSaveMsgSink(msg);

            Content = GuiConfigCommands.CmdInitSlider("4", "Test3", "°C", "04", 0, 100);
            msg = MessageTranslater.MsgToString(MessageType.Configuration, "0", Content);
            ThreadSaveMsgSink(msg);

            Content = GuiConfigCommands.CmdInitSlider("5", "Test4", "°C", "03", 0, 100);
            msg = MessageTranslater.MsgToString(MessageType.Configuration, "0", Content);
            ThreadSaveMsgSink(msg);

            Content = GuiConfigCommands.CmdInitSlider("7", "Test5", "°C", "07", 0, 100);
            msg = MessageTranslater.MsgToString(MessageType.Configuration, "0", Content);
            ThreadSaveMsgSink(msg);

            msg = MessageTranslater.MsgToString(MessageType.Information, "0", "Init, not connected...");
            ThreadSaveMsgSink(msg);


            Content = ValueCommand.CmdStringValue("01", "1");
            msg = MessageTranslater.MsgToString(MessageType.Variable, "0", Content);
            ThreadSaveMsgSink(msg);

        }

        bool MainFormSetting(FormSettings cfg)
        {
            if (cfg.MainFormState == FormWindowState.Normal)
            {
                this.Size = cfg.MainFormSize;
                //this.Location = cfg.MainFormLocation;
            }
            this.WindowState = cfg.MainFormState;

            splitContainer3.SplitterDistance = cfg.SplitterDistance3;
            splitContainer4.SplitterDistance = cfg.SplitterDistance4;
            splitContainer5.SplitterDistance = cfg.SplitterDistance5;

            return true;
        }
        bool LoadProject(string name, bool executeCmds)
        {
            guiDB.Connect(name, @"Data Source=localhost\SQLEXPRESS2008;Integrated Security=SSPI;");
            appSetting = AppSettings.FromFile(name);
            List<string> guiCfg = appSetting.guiConfig;
            appSetting.guiConfig = new List<string>();

            MainFormSetting(appSetting.mainForm);
            m_prjName = Path.GetFileName(name);

            Text = string.Format("{0} ({1})", appSetting.m_description, m_prjName);
            if (executeCmds)
            {
                foreach (string cmd in guiCfg)
                {
                    ThreadSaveMsgSink(cmd);
                }
            }

            return true;
        }
        bool ThreadSaveMsgSink(string msg)
        {
            if (this.IsDisposed) return false;
            if (this.InvokeRequired)
            {
                try
                {
                    NewMessageReceived d = new NewMessageReceived(ThreadSaveMsgSink);
                    this.Invoke(d, new object[] { msg });
                }
                catch { }
            }
            else
            {
                Dispatcher.MessageReceiver(msg);
            }
            return true;
        }

        public override bool NotifyChanges(MessageItem message) 
        {
            if ((message.Type == MessageType.Variable) && (ValueCommand.GetCommandType(message.Content) != ValueCommandType.Float))
            {
                string VarId;
                double content;
                ValueCommand.ExtractDouble(message.Content, out VarId, out content);
                guiDB.StoreValueInDB(Convert.ToInt32(VarId), message.Timestamp, content);

            }

            if (message.Type != MessageType.Configuration) return true;
            appSetting.guiConfig.Add(message.RawMessage);
            
            GuiCommand currentGuiCommand = GuiConfigCommands.GetGuiCommandType(message.Content);
            
            #region NotifyCmdInitProject
            // Command Init Project received ?
            if (currentGuiCommand == GuiCommand.InitProject)
            {
                string prjName;
                string prjDescription;
                bool erg = GuiConfigCommands.ExtractInitProjectCmd(message.Content, out prjName, out prjDescription);
                if (!erg) return false;
                if (m_prjName != prjName)
                {
                    m_prjName = prjName;
                    if (File.Exists(m_prjName))
                        LoadProject(m_prjName, false);
                }
                m_prjName = prjName;
                appSetting.m_description = prjDescription;
                Text = string.Format("{0} ({1})",prjDescription, prjName);
                return true;
            }
            #endregion
            #region NotifyCmdReset
            // Command Reset received ?
            if (currentGuiCommand == GuiCommand.Reset)
            {
                int cnt = 0;
                foreach (ViewTextBox vtb in ViewTextBoxArr) vtb.Reset(string.Format("TB{0}",cnt++), true);
                
                cnt = 0;
                foreach (ViewSlider vsl in ViewSliderArr) vsl.Reset(string.Format("SL{0}", cnt++), true);

                ChartConfiguration chart = new ChartConfiguration();
                chart.Configuration.AddDiagramm(new RiZDiagramm());
                userChartControl1.SetChartConfiguration(chart);
                
                appSetting.guiConfig.Clear();
                appSetting.guiConfig.Add(message.RawMessage);
                return true;
            }
            #endregion
            #region NotifyInitTextBox
            if (currentGuiCommand == GuiCommand.InitTextbox)
            {
                string BoxNumber;
                string HeaderText;
                string UnitText;
                string VarId;
                bool erg = GuiConfigCommands.ExtractTextBoxCmd(message.Content, out BoxNumber, out HeaderText, out UnitText, out VarId);
                if (!erg) return false;
                int BoxNr = 0;
                try
                {
                    BoxNr = Convert.ToInt32(BoxNumber);
                    if ((BoxNr < 0) || (BoxNr > 11)) return false;
                    ViewTextBoxArr[BoxNr].Init(HeaderText, UnitText, VarId);
                    Dispatcher.AddObserver(ViewTextBoxArr[BoxNr]);
                }
                catch { return false; }

            }
            #endregion
            #region NotifyInitChart
            if (currentGuiCommand == GuiCommand.InitCharts)
            {
                int chartNo;
                string GraphName;
                string UnitText;
                int varId;
                double min;
                double max;
                try
                {
                    userChartControl1.LoadDBData -= guiDB.LoadDataFromDB;
                }
                catch { }
                userChartControl1.LoadDBData += guiDB.LoadDataFromDB;
                bool erg = GuiConfigCommands.ExtractChartCmd(message.Content, out chartNo, out varId, out GraphName, out UnitText, out min, out max);
                if (!erg) return false;
                try
                {
                    ChartConfiguration chart = userChartControl1.GetChartConfiguration();
                    while (chart.Configuration.Diagramme.Count <= chartNo)
                    {
                        if (chart.Configuration.Diagramme.Count >= 4) break;
                        chart.Configuration.AddDiagramm(new RiZDiagramm());
                    }
                    RiZDiagramm diagramm = chart.Configuration.Diagramme[chartNo];
                    RiZGraph gr = new RiZGraph( 0, GraphName, (uint)varId, 1.0, min, max, UnitText, "0", "", diagramm.NextColor(), "", VariableType.Float);
                    diagramm.AddGraph(gr);
                    
                    userChartControl1.SetChartConfiguration(chart);
                    
                    Dispatcher.AddObserver(userChartControl1);
                    userChartControl1.ReloadData();
                    //Dispatcher.AddObserver(ViewTextBoxArr[BoxNr]);
                }
                catch { return false; }

            }
            #endregion
            #region NotifyInitSliderbar
            if (currentGuiCommand == GuiCommand.InitSliderBar)
            {
                string BoxNumber;
                string HeaderText;
                string UnitText;
                string VarId;
                double min;
                double max;
                bool erg = GuiConfigCommands.ExtractSliderCmd(message.Content, out BoxNumber, out HeaderText, out UnitText, out VarId, out min, out max);
                if (!erg) return false;
                int BoxNr = 0;
                try
                {
                    BoxNr = Convert.ToInt32(BoxNumber);
                    if ((BoxNr < 0) || (BoxNr > 8)) return false;
                    ViewSliderArr[BoxNr].Init(HeaderText, UnitText, VarId, min, max);
                    Dispatcher.AddObserver(ViewSliderArr[BoxNr]);
                }
                catch { return false; }

            }
            return false;
            #endregion
        }
        
        private void serialSettingsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            COMSetup comDlg = new COMSetup();
            comDlg.ComSetting = appSetting.COMParmas;

            if (comDlg.ShowDialog() == DialogResult.OK)
            {
                appSetting.COMParmas = comDlg.ComSetting;
                msgAdapter.Close();
                msgAdapter = MessageAdapterFactory.Create(appSetting.COMParmas, ThreadSaveMsgSink);
            }
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            string msg = "";
            if (msgAdapter.IsRunnig())
            {
                msg = MessageTranslater.MsgToString(MessageType.Information, "0", "Serial Disconnect...");
                msgAdapter.Close();
            }
            else
            {
                msg = MessageTranslater.MsgToString(MessageType.Information, "0", "Serial Connect...");
                msgAdapter.Open();
            }
            
            ThreadSaveMsgSink(msg);
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (msgAdapter.IsRunnig()) msgAdapter.Close();
            
            appSetting.mainForm.MainFormSize = this.Size;
            appSetting.mainForm.MainFormLocation = this.Location;
            appSetting.mainForm.MainFormState = this.WindowState;
            appSetting.mainForm.SplitterDistance3 = splitContainer3.SplitterDistance;
            appSetting.mainForm.SplitterDistance4 = splitContainer4.SplitterDistance;
            appSetting.mainForm.SplitterDistance5 = splitContainer5.SplitterDistance;
            appSetting.SaveToFile(m_prjName);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            //TestSetup();
            /*
            string msg = MessageTranslater.ToText(MessageType.Error, "0",  "test_" + Count.ToString());
            ThreadSaveMsgSink(msg);
            Count++;
             */
        }

        private void Form1_MouseMove(object sender, MouseEventArgs e)
        {
            //Text = e.X.ToString();
            //LoadProject(m_prjName);
        }


    }
}
