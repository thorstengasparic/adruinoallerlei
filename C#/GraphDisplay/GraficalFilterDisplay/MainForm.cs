using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using Arduino.Serial;
using Infotek.Tools;

/* Copyright (c) 2008-2014 DI Zimmermann Stephan (stefan.zimmermann@tele2.at)
 *   
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
 * sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software. 
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 */

namespace GraficDisplay
{
    using GraficFilterDisplay;
    using GraphicFilterDisplay;
    using GraphLib;
    using System.IO;

    public partial class MainForm : Form
    {
        //int cfg.MaxSamples = 5800;


        string currentfilname = "";        
        private PrecisionTimer.Timer mTimer = null;
        private DateTime lastTimerTick = DateTime.Now;

        GuiConfig cfg = new GuiConfig();
        DataSourceSerialConnector connector = new DataSourceSerialConnector();
        public string CurExample { get; set; } = "VERTICAL_ALIGNED_AUTO";

        public MainForm()
        {
            double deltaS = 0.004;
            double laenge = 0.4;         // [m]
            double breite = 0.28;        // [m]
            double masse = 1;          // [kg]

            double g = 9.81;            // [kg*m/s^2]
            double luftdichte = 1.204;   // [kg/m^3]

            double umfang = breite * 2 + laenge * 2;
            double flaeche = breite * laenge;
            double spalt = deltaS * umfang;

            double leistung = deltaS * Math.Pow(umfang, 2) * Math.Sqrt((2 / luftdichte) * Math.Pow(masse * g / flaeche, 3));

            InitializeComponent();


        }

        protected override void OnClosed(EventArgs e)
        {
            mTimer.Stop();
            mTimer.Dispose();
            base.OnClosed(e);
        }
        private void OnTimerTick(object sender, EventArgs e)
        {
            if (CurExample == "ANIMATED_AUTO" )
            {
                    try
                    {
                        TimeSpan dt = DateTime.Now - lastTimerTick;

                        for (int j = 0; j < cfg.NumGraphs; j++)
                        {
                            
                            CalcSinusFunction_3(display.DataSources[j], j, (float)dt.TotalMilliseconds);
                            
                        }
                   
                        this.Invoke(new MethodInvoker(RefreshGraph));
                    }
                    catch (ObjectDisposedException ex)
                    {
                        // we get this on closing of form
                    }
                    catch (Exception ex)
                    {
                        Console.Write("exception invoking refreshgraph(): " + ex.Message);
                    }
                 
                
            }
            try
            {
                if (updatecount > 1)
                {
                    if (isactive) this.Invoke(new MethodInvoker(RefreshGraph));
                    updatecount = 0;
                }
                updatecount++;
            }
            catch { }
        }
        int updatecount = 0;
        private void RefreshGraph()
        {                             
            display.Refresh();             
        }

        
        #region SinusFuctions
        protected void CalcSinusFunction_0(DataSource src, int idx)
        {
            for (int i = 0; i < src.Length; i++)
            {
                src.Samples[i].x = i;
                src.Samples[i].y = 0;
                //src.Samples[i].y = (float)(((float)200 * Math.Sin((idx + 1) *(i + 1.0) * 48 / src.Length)));
            }            
        }

        protected void CalcSinusFunction_1(DataSource src, int idx)
        {
            for (int i = 0; i < src.Length; i++)
            {
                src.Samples[i].x = i;
                src.Samples[i].y = 0;
                /*
                src.Samples[i].y = (float)(((float)20 *
                                            Math.Sin(20 * (idx + 1) * (i + 1) * Math.PI / src.Length)) *
                                            Math.Sin(40 * (idx + 1) * (i + 1) * Math.PI / src.Length)) +
                                            (float)(((float)200 *
                                            Math.Sin(200 * (idx + 1) * (i + 1) * Math.PI / src.Length)));
                                            */
            }
            src.OnRenderYAxisLabel = RenderYLabel;
        }

        protected void CalcSinusFunction_2(DataSource src, int idx)
        {
            for (int i = 0; i < src.Length; i++)
            {
                src.Samples[i].x = i;
                src.Samples[i].y = 0;
                /*
                src.Samples[i].y = (float)(((float)20 *
                                            Math.Sin(40 * (idx + 1) * (i + 1) * Math.PI / src.Length)) *
                                            Math.Sin(160 * (idx + 1) * (i + 1) * Math.PI / src.Length)) +
                                            (float)(((float)200 *
                                            Math.Sin(4 * (idx + 1) * (i + 1) * Math.PI / src.Length)));
                                            */
            }
            src.OnRenderYAxisLabel = RenderYLabel;
        }

        protected void CalcSinusFunction_3(DataSource ds, int idx,float time)
        {
            cPoint[] src = ds.Samples;
            for (int i = 0; i < src.Length; i++)
            {
                src[i].x = i;
                src[i].y = 0;
                /*
                src[i].y = 200 + (float)((200 * Math.Sin((idx + 1) * (time + i * 100) / 8000.0)))+
                                +(float)((40  * Math.Sin((idx + 1) * (time + i * 200) / 2000.0)));
                */
                /**
                            (float)( 4* Math.Sin( ((time + (i+8) * 100) / 900.0)))+
                            (float)(28 * Math.Sin(((time + (i + 8) * 100) / 290.0))); */
            }
            
        }
        #endregion


        protected void CalcDataGraphs( )
        {

            this.SuspendLayout();
           
            display.DataSources.Clear();
            connector.Clear();
            display.SetDisplayRangeX(0, cfg.MaxSamples);
            display.PanelLayout = cfg.PanelLayout;
            display.SetGridDistanceX(250);

            for (int j = 0; j < cfg.NumGraphs; j++)
            {
                display.DataSources.Add(new DataSource());
                connector.Add(display.DataSources[j], j);

                display.DataSources[j].Name = cfg.GraphSetting[j].Name;
                display.DataSources[j].OnRenderXAxisLabel += RenderXLabel;
                
                display.DataSources[j].Length = cfg.MaxSamples;
                display.DataSources[j].AutoScaleY = cfg.GraphSetting[j].AutoScaleY;
                display.DataSources[j].AutoScaleX = cfg.GraphSetting[j].AutoScaleX;
                
                display.DataSources[j].YD0 = cfg.GraphSetting[j].MinY;
                display.DataSources[j].YD1 = cfg.GraphSetting[j].MaxY;
                display.DataSources[j].GridDistanceY = cfg.GraphSetting[j].GridDistY;
                display.DataSources[j].OnRenderYAxisLabel = RenderYLabel;
                
                switch (CurExample)
                {
                    case  "NORMAL":
                        display.PanelLayout = PlotterGraphPaneEx.LayoutMode.NORMAL;
                        display.DataSources[j].AutoScaleY = false;
                        break;

                    case "NORMAL_AUTO":
                        display.PanelLayout = PlotterGraphPaneEx.LayoutMode.NORMAL;
                        display.DataSources[j].AutoScaleY = true;
                        break;

                    case "STACKED":
                        display.PanelLayout = PlotterGraphPaneEx.LayoutMode.STACKED;
                        display.DataSources[j].AutoScaleY = false;
                        break;

                    case "VERTICAL_ALIGNED":
                        display.PanelLayout = PlotterGraphPaneEx.LayoutMode.VERTICAL_ARRANGED;
                        display.DataSources[j].AutoScaleY = false;
                        break;

                    case "VERTICAL_ALIGNED_AUTO":
                        display.PanelLayout = PlotterGraphPaneEx.LayoutMode.VERTICAL_ARRANGED;
                        display.DataSources[j].AutoScaleY = false;
                        break;

                    case "TILED_VERTICAL":
                        display.PanelLayout = PlotterGraphPaneEx.LayoutMode.TILES_VER;
                        display.DataSources[j].AutoScaleY = false;
                        break;

                    case "TILED_VERTICAL_AUTO":
                        display.PanelLayout = PlotterGraphPaneEx.LayoutMode.TILES_VER;
                        display.DataSources[j].AutoScaleY = true;
                        break;

                    case "TILED_HORIZONTAL":
                        display.PanelLayout = PlotterGraphPaneEx.LayoutMode.TILES_HOR;
                        display.DataSources[j].AutoScaleY = false;
                        break;

                    case "TILED_HORIZONTAL_AUTO":
                        display.PanelLayout = PlotterGraphPaneEx.LayoutMode.TILES_HOR;
                        display.DataSources[j].AutoScaleY = true;
                        
                        break;

                    case "ANIMATED_AUTO":
                        display.PanelLayout = PlotterGraphPaneEx.LayoutMode.TILES_HOR;
                        display.DataSources[j].AutoScaleY = false;
                        display.DataSources[j].AutoScaleX = true;
                        display.DataSources[j].XAutoScaleOffset = 50;
                        break;
                }             
            }
            
            ApplyColorSchema();

            this.ResumeLayout();
            display.Refresh();
           
        }

        private String RenderXLabel(DataSource s, int idx)
        {
            if (s.AutoScaleX)
            {
                //if (idx % 2 == 0)
                {
                    int Value = (int)(s.Samples[idx].x );
                    return "" + Value;
                }
                return "";
            }
            else
            {
                int Value = (int)(s.Samples[idx].x / 250);
                String Label = "" + Value +"";
                return Label;
            }
        }

        private String RenderYLabel(DataSource s, float  value)
        {             
            return String.Format("x{0:0.0}", value);
        }

        #region     GraphMenu
        private void ApplyColorSchema()
        {
            switch (cfg.ColorSchema)
            {
                case "DARK_GREEN":
                    {
                        Color[] cols = { Color.FromArgb(0,255,0),
                                         Color.FromArgb(0,255,0),
                                         Color.FromArgb(0,255,0),
                                         Color.FromArgb(0,255,0),
                                         Color.FromArgb(0,255,0) ,
                                         Color.FromArgb(0,255,0),
                                         Color.FromArgb(0,255,0) };

                        for (int j = 0; j < cfg.NumGraphs; j++)
                        {
                            display.DataSources[j].GraphColor = cols[j % 7];
                        }

                        display.BackgroundColorTop = Color.FromArgb(0, 64, 0);
                        display.BackgroundColorBot = Color.FromArgb(0, 64, 0);
                        display.SolidGridColor = Color.FromArgb(0, 128, 0);
                        display.DashedGridColor = Color.FromArgb(0, 128, 0);
                    }
                    break;
                case "WHITE":
                    {
                        Color[] cols = { Color.DarkRed,
                                         Color.DarkSlateGray,
                                         Color.DarkCyan,
                                         Color.DarkGreen,
                                         Color.DarkBlue ,
                                         Color.DarkMagenta,
                                         Color.DeepPink };

                        for (int j = 0; j < cfg.NumGraphs; j++)
                        {
                            display.DataSources[j].GraphColor = cols[j % 7];
                        }

                        display.BackgroundColorTop = Color.White;
                        display.BackgroundColorBot = Color.White;
                        display.SolidGridColor = Color.LightGray;
                        display.DashedGridColor = Color.LightGray;
                    }
                    break;

                case "BLUE":
                    {
                        Color[] cols = { Color.Red,
                                         Color.Orange,
                                         Color.Yellow,
                                         Color.LightGreen,
                                         Color.Blue ,
                                         Color.DarkSalmon,
                                         Color.LightPink };

                        for (int j = 0; j < cfg.NumGraphs; j++)
                        {
                            display.DataSources[j].GraphColor = cols[j % 7];
                        }

                        display.BackgroundColorTop = Color.Navy;
                        display.BackgroundColorBot = Color.FromArgb(0, 0, 64);
                        display.SolidGridColor = Color.Blue;
                        display.DashedGridColor = Color.Blue;
                    }
                    break;

                case "GRAY":
                    {
                        Color[] cols = { Color.DarkRed,
                                         Color.DarkSlateGray,
                                         Color.DarkCyan,
                                         Color.DarkGreen,
                                         Color.DarkBlue ,
                                         Color.DarkMagenta,
                                         Color.DeepPink };

                        for (int j = 0; j < cfg.NumGraphs; j++)
                        {
                            display.DataSources[j].GraphColor = cols[j % 7];
                        }

                        display.BackgroundColorTop = Color.White;
                        display.BackgroundColorBot = Color.LightGray;
                        display.SolidGridColor = Color.LightGray;
                        display.DashedGridColor = Color.LightGray;
                    }
                    break;

                case "RED":
                    {
                        Color[] cols = { Color.DarkCyan,
                                         Color.Yellow,
                                         Color.DarkCyan,
                                         Color.DarkGreen,
                                         Color.DarkBlue ,
                                         Color.DarkMagenta,
                                         Color.DeepPink };

                        for (int j = 0; j < cfg.NumGraphs; j++)
                        {
                            display.DataSources[j].GraphColor = cols[j % 7];
                        }

                        display.BackgroundColorTop = Color.DarkRed;
                        display.BackgroundColorBot = Color.Black;
                        display.SolidGridColor = Color.Red;
                        display.DashedGridColor = Color.Red;
                    }
                    break;

                case "LIGHT_BLUE":
                    {
                        Color[] cols = { Color.DarkRed,
                                         Color.DarkSlateGray,
                                         Color.DarkCyan,
                                         Color.DarkGreen,
                                         Color.DarkBlue ,
                                         Color.DarkMagenta,
                                         Color.DeepPink };

                        for (int j = 0; j < cfg.NumGraphs; j++)
                        {
                            display.DataSources[j].GraphColor = cols[j % 7];
                        }

                        display.BackgroundColorTop = Color.White;
                        display.BackgroundColorBot = Color.FromArgb(183, 183, 255);
                        display.SolidGridColor = Color.Blue;
                        display.DashedGridColor = Color.Blue;
                    }
                    break;

                case "BLACK":
                    {
                        Color[] cols = { Color.FromArgb(255,0,0),
                                         Color.FromArgb(0,255,0),
                                         Color.FromArgb(255,255,0),
                                         Color.FromArgb(64,64,255),
                                         Color.FromArgb(0,255,255) ,
                                         Color.FromArgb(255,0,255),
                                         Color.FromArgb(255,128,0) };

                        for (int j = 0; j < cfg.NumGraphs; j++)
                        {
                            display.DataSources[j].GraphColor = cols[j % 7];
                        }

                        display.BackgroundColorTop = Color.Black;
                        display.BackgroundColorBot = Color.Black;
                        display.SolidGridColor = Color.DarkGray;
                        display.DashedGridColor = Color.DarkGray;
                    }
                    break;
            }

        }
        protected override void OnClosing(CancelEventArgs e)
        {
            display.Dispose();

            base.OnClosing(e);
        }

        private void stackedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            display.PanelLayout = PlotterGraphPaneEx.LayoutMode.NORMAL;
        }

        private void verticalALignedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            display.PanelLayout = PlotterGraphPaneEx.LayoutMode.VERTICAL_ARRANGED;
        }

        private void tiledVerticallyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            display.PanelLayout = PlotterGraphPaneEx.LayoutMode.TILES_VER;
        }

        private void tiledHorizontalyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            display.PanelLayout = PlotterGraphPaneEx.LayoutMode.TILES_HOR;
        }
                
        private void noneToolStripMenuItem_Click(object sender, EventArgs e)
        {
            display.Smoothing = System.Drawing.Drawing2D.SmoothingMode.None;
        }

        private void antiAliasedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            display.Smoothing = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
        }

        private void highSpeedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            display.Smoothing = System.Drawing.Drawing2D.SmoothingMode.HighQuality;
        }

        private void highQualityToolStripMenuItem_Click(object sender, EventArgs e)
        {
            display.Smoothing = System.Drawing.Drawing2D.SmoothingMode.HighSpeed;
        }

        private void normalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CurExample = "NORMAL";
            CalcDataGraphs();
        }

        private void normalAutoscaledToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CurExample = "NORMAL_AUTO";
            CalcDataGraphs();
        }

        private void stackedToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            CurExample = "STACKED";
            CalcDataGraphs();
        }

        private void verticallyAlignedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CurExample = "VERTICAL_ALIGNED";
            CalcDataGraphs();
        }
        private void verticallyAlignedAutoscaledToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CurExample = "VERTICAL_ALIGNED_AUTO";
            CalcDataGraphs();
        }

        private void tiledVerticalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CurExample = "TILED_VERTICAL";
            CalcDataGraphs();
        }
        private void tiledVerticalAutoscaledToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CurExample = "TILED_VERTICAL_AUTO";
            CalcDataGraphs();
        }

        private void tiledHorizontalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CurExample = "TILED_HORIZONTAL";
            CalcDataGraphs();
        }

        private void tiledHorizontalAutoscaledToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CurExample = "TILED_HORIZONTAL_AUTO";
            CalcDataGraphs();
        }

        private void animatedGraphDemoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CurExample = "ANIMATED_AUTO";
            CalcDataGraphs();
        }
   

        private void blueToolStripMenuItem_Click(object sender, EventArgs e)
        {
            cfg.ColorSchema = "BLUE";
            CalcDataGraphs();
            UpdateColorSchemaMenu();
        }

        private void whiteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            cfg.ColorSchema = "WHITE";
            CalcDataGraphs();
            UpdateColorSchemaMenu();
        }

        private void grayToolStripMenuItem_Click(object sender, EventArgs e)
        {
            cfg.ColorSchema = "GRAY";
            CalcDataGraphs();
            UpdateColorSchemaMenu();
        }

         private void lightBlueToolStripMenuItem_Click(object sender, EventArgs e)
        {
            cfg.ColorSchema = "LIGHT_BLUE";
            CalcDataGraphs();
            UpdateColorSchemaMenu();
            
        }

        private void blackToolStripMenuItem_Click(object sender, EventArgs e)
        {
            cfg.ColorSchema = "BLACK";
            CalcDataGraphs();
            UpdateColorSchemaMenu();
        }

        private void redToolStripMenuItem_Click(object sender, EventArgs e)
        {
            cfg.ColorSchema = "RED";
            CalcDataGraphs();
            UpdateColorSchemaMenu();
        }

          private void greenToolStripMenuItem_Click(object sender, EventArgs e)
        {
            cfg.ColorSchema = "DARK_GREEN";
            CalcDataGraphs();
            UpdateColorSchemaMenu();
           
        }

        private void UpdateColorSchemaMenu()
        {
            blueToolStripMenuItem.Checked = false;
            whiteToolStripMenuItem.Checked = false;
            grayToolStripMenuItem.Checked = false;
            lightBlueToolStripMenuItem.Checked = false;
            blackToolStripMenuItem.Checked = false;
            redToolStripMenuItem.Checked = false;

            if (cfg.ColorSchema == "WHITE") whiteToolStripMenuItem.Checked = true;
            if (cfg.ColorSchema == "BLUE") blueToolStripMenuItem.Checked = true;
            if (cfg.ColorSchema == "GRAY") grayToolStripMenuItem.Checked = true;
            if (cfg.ColorSchema == "LIGHT_BLUE") lightBlueToolStripMenuItem.Checked = true;
            if (cfg.ColorSchema == "BLACK") blackToolStripMenuItem.Checked = true;
            if (cfg.ColorSchema == "RED") redToolStripMenuItem.Checked = true;
            if (cfg.ColorSchema == "DARK_GREEN") greenToolStripMenuItem.Checked = true;
        }

        private void UpdateGraphCountMenu()
        {
            toolStripMenuItem2.Checked = false;
            toolStripMenuItem3.Checked = false;
            toolStripMenuItem4.Checked = false;
            toolStripMenuItem5.Checked = false;
            toolStripMenuItem6.Checked = false;
            toolStripMenuItem7.Checked = false;

            switch (cfg.NumGraphs)
            {
                case 1: toolStripMenuItem2.Checked = true; break;
                case 2: toolStripMenuItem3.Checked = true; break;
                case 3: toolStripMenuItem4.Checked = true; break;
                case 4: toolStripMenuItem5.Checked = true; break;
                case 5: toolStripMenuItem6.Checked = true; break;
                case 6: toolStripMenuItem7.Checked = true; break;
                
            }
        }
#endregion

        private void toolStripMenuItem2_Click(object sender, EventArgs e)
        {
            cfg.NumGraphs = 1;
            CalcDataGraphs();
            UpdateGraphCountMenu();
        }

        private void toolStripMenuItem3_Click(object sender, EventArgs e)
        {
            cfg.NumGraphs = 2;
            CalcDataGraphs();
            UpdateGraphCountMenu();
        }

        private void toolStripMenuItem4_Click(object sender, EventArgs e)
        {
            cfg.NumGraphs = 3;
            CalcDataGraphs();
            UpdateGraphCountMenu();
        }

        private void toolStripMenuItem5_Click(object sender, EventArgs e)
        {
            cfg.NumGraphs = 4;
            CalcDataGraphs();
            UpdateGraphCountMenu();
        }

        private void toolStripMenuItem6_Click(object sender, EventArgs e)
        {
            cfg.NumGraphs = 5;
            CalcDataGraphs();
            UpdateGraphCountMenu();
        }

        private void toolStripMenuItem7_Click(object sender, EventArgs e)
        {
            cfg.NumGraphs = 6;
            CalcDataGraphs();
            UpdateGraphCountMenu();
        }

        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {

        }
                
        private void toolStripMenuItem8_MouseEnter(object sender, EventArgs e)
        {
            toolStripComboBoxComPort.Items.Clear();
            toolStripComboBoxComPort.Text = "";
            toolStripComboBoxComPort.Items.AddRange(SerialConfig.Ports);
            
            int idx = toolStripComboBoxComPort.Items.IndexOf(cfg.CurrentCOM.PortName);
            
            try
            {
                toolStripComboBoxComPort.SelectedIndex = idx;
            }
            catch (Exception ex)
            {
            }

            toolStripComboBoxBaudrate.Items.Clear();
            toolStripComboBoxBaudrate.Items.AddRange(SerialConfig.BaudRates);
            toolStripComboBoxBaudrate.Text = "";
            try
            {
                toolStripComboBoxBaudrate.SelectedItem = cfg.CurrentCOM.BaudRate;
            }
            catch (Exception ex)
            {
            }

            toolStripTextBoxMaxSamples.Text = cfg.MaxSamples.ToString();

        }

        private void toolStripComboBoxComPort_SelectedIndexChanged(object sender, EventArgs e)
        {
            cfg.CurrentCOM.PortName = toolStripComboBoxComPort.SelectedItem.ToString();
            cfg.CurrentCOM.BaudRate = toolStripComboBoxBaudrate.SelectedItem.ToString();
            toolStripMenuItem8.GetCurrentParent().Focus();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            string path = GernericSerializer.UserApplPathName("default.cfg", true);
            cfg = (GuiConfig)GernericSerializer.DeSerialize(path, cfg.GetType());
            if (cfg == null) cfg = new GuiConfig();

            display.Smoothing = System.Drawing.Drawing2D.SmoothingMode.None;

            connector.OnNewMessageDetected = OnNewMessageReceived;
            connector.OnNewSampleDetected = OnNewSampleDetected;
            CalcDataGraphs();

            display.Refresh();

            UpdateGraphCountMenu();

            UpdateColorSchemaMenu();


            mTimer = new PrecisionTimer.Timer();
            mTimer.Period = 40;                         // 20 fps
            mTimer.Tick += new EventHandler(OnTimerTick);
            lastTimerTick = DateTime.Now;
            mTimer.Start();

        }
        
        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            connector.Stop();
            StoreConfig("default.cfg");


        }

        private void toolStripTextBoxMaxSamples_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == 13)
                try
                {
                    int ms1 = Convert.ToInt32(toolStripTextBoxMaxSamples.Text);
                    if (ms1 != cfg.MaxSamples)
                    {
                        cfg.MaxSamples = ms1;
                        e.Handled = true;
                        toolStripMenuItem1.GetCurrentParent().Focus();
                        CalcDataGraphs();

                    }
                }
                catch { }
        }
        bool isactive = false;
        private void buttonStart_Click(object sender, EventArgs e)
        {
            if (isactive)
            { 
                connector.Stop();
                buttonStart.Text = "Start";
                Text = cfg.CurrentCOM.ToString();
            }
            else
            {
                connector.ComPort(cfg.CurrentCOM);
                connector.Start();
                buttonStart.Text = "Stop";
            }
            isactive = !isactive;
        }
 
        private void textBoxIn_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == 13)
            {
                connector.Send(textBoxIn.Text);
                textBoxIn.Text = "";
            }
        }

        
        void StoreConfig(string name)
        {
            for (int j = 0; j < cfg.NumGraphs; j++)
            {
                cfg.GraphSetting[j].Name = display.DataSources[j].Name;
                cfg.GraphSetting[j].MinY = display.DataSources[j].YD0;
                cfg.GraphSetting[j].MaxY = display.DataSources[j].YD1;
                cfg.GraphSetting[j].GridDistY = display.DataSources[j].GridDistanceY;
                cfg.GraphSetting[j].AutoScaleY = display.DataSources[j].AutoScaleY;
                cfg.GraphSetting[j].AutoScaleX = display.DataSources[j].AutoScaleX;
            }
            cfg.PanelLayout = display.PanelLayout;

            string path = name;
            if (path == "default.cfg")
                path = GernericSerializer.UserApplPathName(name, true);

            GernericSerializer.Serialize(path, cfg);
        }
        private void loadToolStripMenuItem_Click(object sender, EventArgs e)
        {
            openFileDialog1.InitialDirectory = GernericSerializer.UserApplPathName("", true);
            openFileDialog1.Multiselect = false;
            openFileDialog1.FileName = "";
            openFileDialog1.Filter = "cfg files (*.cfg)|*.cfg";
            if (openFileDialog1.ShowDialog() != DialogResult.OK)
                return;

            cfg = (GuiConfig)GernericSerializer.DeSerialize(openFileDialog1.FileName, cfg.GetType());
            if (cfg == null) return;
            
            string fname = Path.GetFileName(openFileDialog1.FileName);

            currentfilname = openFileDialog1.FileName;
            this.Text = currentfilname;
            CalcDataGraphs();
            display.Refresh();

            UpdateGraphCountMenu();

            UpdateColorSchemaMenu();
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (currentfilname == "")
            {
                saveAsToolStripMenuItem_Click(sender, e);
                return;
            }
            StoreConfig(currentfilname);
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            saveFileDialog1.FileName = Path.GetFileNameWithoutExtension(currentfilname);
            saveFileDialog1.InitialDirectory = GernericSerializer.UserApplPathName("", true);
            saveFileDialog1.Filter = "cfg files (*.cfg)|*.cfg";
            if (saveFileDialog1.ShowDialog() != DialogResult.OK)
                return;
            currentfilname = saveFileDialog1.FileName;
            StoreConfig(currentfilname);
        }


        public bool OnNewMessageReceived(string newMsg)
        {
            try
            {
                this.Invoke(new MethodInvoker(
                    delegate
                    {
                        textBoxOutput.AppendText(newMsg);
                    }
                    ));

            }
            catch { }

            return true;
        }


        public bool OnNewSampleDetected(int index, double value, bool resetCursor)
        {
            int[] outGraphs = cfg.SamplesDisp.Disp(index);
            
            if (outGraphs.Length > 0)
            {
                if (resetCursor)
                {
                    display.DataSources[outGraphs[0]].DataCursor = -1;
                }

                long currentDataCursor = display.DataSources[outGraphs[0]].DataCursor; // synch all graphs
                currentDataCursor++;
                if (currentDataCursor >= display.DataSources[outGraphs[0]].Length)
                    currentDataCursor = 0;
                
                foreach (int outGraphIndex in outGraphs)
                {
                    if (outGraphIndex >= cfg.NumGraphs) continue;
                    display.DataSources[outGraphIndex].Samples[currentDataCursor].y = (float)value;
                    display.DataSources[outGraphIndex].Samples[currentDataCursor].x = currentDataCursor;
                    display.DataSources[outGraphIndex].DataCursor = currentDataCursor;
                }
            }

            
            return true;
        }

        private void propertiesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FormGraphAssigment dlg = new FormGraphAssigment();
            dlg.SamplesDisp = cfg.SamplesDisp;
            if (dlg.ShowDialog() != DialogResult.OK) return;
            cfg.SamplesDisp = dlg.SamplesDisp;
        }

        private void filterToolStripMenuItem1_Click(object sender, EventArgs e)
        {

            FormFilter dlg = new FormFilter();
            dlg.OnNewSampleDetected = OnNewSampleDetected;
            dlg.MaxSamples = cfg.MaxSamples;
            dlg.display = display;
            dlg.Show();
        }
    }
}