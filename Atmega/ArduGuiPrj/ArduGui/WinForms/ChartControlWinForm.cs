using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using ZedGraph;

namespace ArduGui.View
{
    public enum VariableType
    {
        None,
        AnalogInt,
        StatusInt,
        MultistateInt,
        Float,
        String,
        DigitalInt
    }

    public delegate void DiagrammChanged(int DiagrammNummer);
    public delegate void DateTimeChanged(DateTime startTime, DateTime endTime, DateTime cursorTime);
    public partial class ChartControlWinForm : UserControl
    {

        public bool SetConfigXML(string XmlString)
        {
            return true;
        }

        #region Events
            public DateTimeChanged OnDateTimeChaned;
            public DiagrammChanged OnDiagrammChanged;
        #endregion
        
        DateTime startTime;
        DateTime endTime;
        DateTime cursorTime;

        private Point dragStartPt;
        private Point dragEndPt;
        private bool isZooming;
        private int m_ControlCount;
        private ChartConfiguration m_Config = null;
        private RiZedGraphControlBase[] zcontrols;
        private GraphPane currentGraphPane;

        private IDictionary<uint, RiZGraphData> mstList;


        public ChartControlWinForm()
        {
            border = 1;
            gap = 1;
            InitializeComponent();

            m_ControlCount = 1;
            isZooming = false;
            OnDateTimeChaned = null;
            OnDiagrammChanged = null;
            m_Config = null;
            SetChartConfiguration(m_Config);
            DateTime ncursorTime = DateTimeHelper.ToRaster(DateTime.Now, 10);
            DateTime nstartTime = ncursorTime.AddMinutes(-10);
            DateTime nendTime = ncursorTime.AddMinutes(5);
            SetTime(nstartTime, nendTime, ncursorTime);
            DarstellungsIntervall(Skalierung.Free);
            OnDateTimeChaned += SetTime;
            FillDummyData();
        }
        public int border = 0;
        public int gap = 0;

        public void FillDummyData()
        {
            if (m_Config == null) return;
            
            mstList = new Dictionary<uint, RiZGraphData>();
            foreach (KeyValuePair<uint, VariableType> kvp in m_Config.Configuration.GetVariables())
            {
                uint vari =kvp.Key;
                RiZGraphData gr = new RiZGraphData(vari.ToString(), "test");
                gr.SetDummydata(0, 100);
                mstList.Add(vari, gr);
            }
            SetGraphData(ref mstList);
            ReDrawGraph();
        }
    
        public ChartConfiguration GetChartConfiguration()
        {
            return m_Config;
        }

        public void SetChartConfiguration(ChartConfiguration Config)
        {
        
            m_Config = Config;
            if (m_Config == null)
            {
                m_Config = new ChartConfiguration();
                m_Config.Configuration.AddDiagramm(new RiZDiagramm());
                m_Config.Configuration.AddDiagramm(new RiZDiagramm());
                m_Config.Configuration.AddDiagramm(new RiZDiagramm());
                m_Config.Configuration.AddDiagramm(new RiZDiagramm());
            }
            m_ControlCount = m_Config.Configuration.Diagramme.Count; ;
            InitializeZedControls(m_Config);
            for (int i = 0; i < m_ControlCount; i++)
            {
                zcontrols[i].Init(m_Config.Configuration.Diagramme[i]);
                zcontrols[i].SetMessdaten(ref mstList);
            }
            DataView_Resize(null, null);
        }
        RiZDiagramm GetDiagramCfg(ZedGraphControl control)
        {
            for (int i = 0; i < 4; i++)
            {
                if (Object.Equals(control, zcontrols[i]))
                {
                    if (m_Config.Configuration.Diagramme.Count <= i) return null;
                    return m_Config.Configuration.Diagramme[i];
                }
            }
            return null;
        }

        public void SetGraphData(ref IDictionary<uint, RiZGraphData> mstList)
        {
            this.mstList = mstList;
            for (int i = 0; i < m_ControlCount; i++)
            {
                zcontrols[i].SetMessdaten(ref mstList);
            }
        }
        
        public void SetTime(DateTime ncursorTime)
        {
            if (ncursorTime.Ticks == 0) return;

            this.cursorTime = new DateTime(ncursorTime.Ticks);
            
            DateTime newStart = new DateTime();
            DateTime newEnd = new DateTime();

            if ((startTime.Ticks > 0) && (endTime.Ticks > 0))
            {
                newStart = DateTimeHelper.GetStartTime(cursorTime, startTime, endTime, Raster.sec10, Skalierung.Free);
                newEnd = DateTimeHelper.GetEndTime(cursorTime, startTime, endTime, Raster.sec10, Skalierung.Free);
            }
            
            SetTime(newStart, newEnd, ncursorTime);
        }
        
        public void SetTime(DateTime startTime, DateTime endTime, DateTime ncursorTime)
        {
            if (startTime.Ticks > 0) this.startTime = startTime;
            if (endTime.Ticks > 0) this.endTime = endTime;
            if (ncursorTime.Ticks > 0) this.cursorTime = new DateTime(ncursorTime.Ticks);

            for (int i = 0; i < m_ControlCount; i++)
            {
                  zcontrols[i].SetTime(startTime, endTime, cursorTime);
                zcontrols[i].AxisChange();
                zcontrols[i].SetChartCursor();
            }
        }

        public void SetCursor(System.Windows.Forms.Cursor curCursor)
        {
            for (int i = 0; i < m_ControlCount; i++)
            {
                zcontrols[i].Cursor = curCursor;
            }
        }

        public void ReDrawGraph()
        {
            for (int i = 0; i < m_ControlCount; i++)
            {
                zcontrols[i].DrawGraph();
            }
        }

        private void HandleZoomDrag(ZedGraphControl control, Point mousePt)
        {
            // Hide the previous rectangle by calling the
            // DrawReversibleFrame method with the same parameters.
            Rectangle rect = CalcScreenRect(control, dragStartPt, dragEndPt);
            ControlPaint.DrawReversibleFrame(rect, this.BackColor, FrameStyle.Dashed);
        }
        
        private void zg1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            RiZDiagramm grD = GetDiagramCfg((sender as ZedGraphControl));
            if (grD == null) return;
            if (grD.ChartType != RiZChartType.Line) return;

            if (e.Button == MouseButtons.Left)
            {
                dragEndPt = new Point(e.X, e.Y);
                double pfEndX, pfEndY;
                (sender as ZedGraphControl).GraphPane.ReverseTransform(dragEndPt, out pfEndX, out pfEndY);
                XDate dt = new XDate(pfEndX);
                DateTime d = DateTimeHelper.ToRaster(dt.DateTime, 10);
                SetTime(d);
                if (OnDateTimeChaned != null) OnDateTimeChaned(startTime, endTime, cursorTime);
                if (OnDiagrammChanged != null) OnDiagrammChanged(Convert.ToInt32((sender as ZedGraphControl).Name));
            }
        }

        private void zg1_MouseWheelEvent(object sender, MouseEventArgs e)
        {
            int DeltaSec = 10;
            int Vorzeichen = 1;
            if (e.Delta < 0) Vorzeichen = -1;
            
            if (Control.ModifierKeys == Keys.Control) DeltaSec = 6 * 10;
            if (Control.ModifierKeys == Keys.Shift) DeltaSec = 6 * 60 * 10;
            DeltaSec *= Vorzeichen;
            cursorTime = cursorTime.AddSeconds(DeltaSec);
            DarstellungsIntervall(Skalierung.Free);

            return;
        }
        

        private bool zg1_MouseDownEvent(ZedGraphControl control, MouseEventArgs e)
        {
            currentGraphPane.Border.Color = Color.LightGray;
            currentGraphPane = control.GraphPane;
            currentGraphPane.Border.Color = Color.Black;

            RiZDiagramm grD = GetDiagramCfg(control);
            if (grD == null) return true;
            if (grD.ChartType != RiZChartType.Line) return true;

            isZooming = false;
            if (Control.ModifierKeys == Keys.Control)
            {
                isZooming = true;
                dragStartPt = new Point(e.X, e.Y);
                dragEndPt = dragStartPt;
                HandleZoomDrag(control, dragStartPt);
            }
           
            return true;
        }
        private bool zg1_MouseMoveEvent(ZedGraphControl control, MouseEventArgs e)
        {
            if (isZooming)
            {
                HandleZoomDrag(control, dragEndPt);
                dragEndPt = new Point(e.X, e.Y);
                HandleZoomDrag(control, new Point(e.X, e.Y));
            }
            return true;    
        }
        private bool zg1_MouseUpEvent(ZedGraphControl control, MouseEventArgs e)
        {
            if (isZooming)
            {
                isZooming = false;
                HandleZoomDrag(control, dragEndPt);
                dragEndPt = new Point(e.X, e.Y);

                double pfEndX, pfEndY;
                control.GraphPane.ReverseTransform(dragEndPt, out pfEndX, out pfEndY);

                double pfStartX, pfStartY;
                control.GraphPane.ReverseTransform(dragStartPt, out pfStartX, out pfStartY);

                if (pfStartX > pfEndX)
                {
                    double tmp = pfStartX;
                    pfStartX = pfEndX;
                    pfEndX = tmp;
                }


                TimeSpan ts = (new XDate(pfEndX)).DateTime.Subtract(new XDate(pfStartX).DateTime);
                if (ts.TotalSeconds < 60) return true;

                if (OnDateTimeChaned != null)
                {
                    OnDateTimeChaned(new XDate(pfStartX).DateTime, new XDate(pfEndX).DateTime, new XDate(pfStartX + (pfEndX - pfStartX) / 2).DateTime);
                }
                SetTime(new XDate(pfStartX).DateTime, new XDate(pfEndX).DateTime, new XDate(pfStartX + (pfEndX - pfStartX) / 2).DateTime);
            }
            else
            {
                SetTime(cursorTime);
                if (OnDiagrammChanged != null) OnDiagrammChanged(Convert.ToInt32(control.Name));
            }
            return true;
        }

        private Rectangle CalcScreenRect(ZedGraphControl control, Point mousePt1, Point mousePt2)
        {
            Point screenPt = control.PointToScreen(mousePt1);
            Size size = new Size(mousePt2.X - mousePt1.X, mousePt2.Y - mousePt1.Y);
            Rectangle rect = new Rectangle(screenPt, size);
            Rectangle chartRect = Rectangle.Round(control.GraphPane.Chart.Rect);
            Point chartPt = control.PointToScreen(chartRect.Location);
            Point FormPt = control.PointToScreen(control.Parent.Location);
            rect.Y = chartPt.Y;
            rect.Height = chartRect.Height + 1;
            return rect;
        }

        public void DarstellungsIntervall(Skalierung skal)
        {
            DateTime newStartTime = DateTimeHelper.GetStartTime(cursorTime, startTime, endTime, Raster.sec10, skal);
            DateTime newEndTime = DateTimeHelper.GetEndTime(cursorTime, startTime, endTime, Raster.sec10, skal);
            if (OnDateTimeChaned != null)  OnDateTimeChaned(newStartTime, newEndTime, cursorTime);
            //SetTime(newStartTime, newEndTime, cursorTime);
            
        }
        
        private void DataView_Resize(object sender, EventArgs e)
        {

            int topPos = border;
            Point loc = new Point();
            int width;
            int height;
            if (m_ControlCount == 1)
            {
                RiZedGraphControlBase zcontrol = zcontrols[0];
                
                loc.X = border;
                loc.Y = border;
                zcontrol.Location = loc;

                width = (this.Width) - border*2;
                height = (this.Height) - border*2;
                
                zcontrol.Width = width;
                zcontrol.Height = height;
                return;
            }
            if (m_ControlCount == 2)
            {
                RiZedGraphControlBase zcontrol = zcontrols[0];
                
                loc.X = border;
                loc.Y = border;
                zcontrol.Location = loc;
                width = (this.Width) / 2 - gap -border;
                height = (this.Height) - border * 2;
                zcontrol.Width = width;
                zcontrol.Height = height;
                
                zcontrol = zcontrols[1];
                loc.Y = border;
                loc.X = (this.Width) / 2 + gap;
                zcontrol.Location = loc;

                zcontrol.Width = width;
                zcontrol.Height = height;
                return;
            }


            if (m_ControlCount == 3)
            {
                RiZedGraphControlBase zcontrol = zcontrols[0];

                loc.X = border;
                loc.Y = border;
                zcontrol.Location = loc;
                width = (this.Width) / 2 - gap - border;
                height = (this.Height) / 2 - border - gap;
                zcontrol.Width = width;
                zcontrol.Height = height;

                zcontrol = zcontrols[1];
                loc.Y = border;
                loc.X = (this.Width) / 2 + gap;
                zcontrol.Location = loc;
                zcontrol.Width = width;
                zcontrol.Height = height;


                zcontrol = zcontrols[2];
                loc.Y = (this.Height) / 2 + gap;
                loc.X = border;
                zcontrol.Location = loc;
                zcontrol.Width = (this.Width) - border * 2;
                zcontrol.Height = height;
                return;
            }

            if (m_ControlCount == 4)
            {
                RiZedGraphControlBase zcontrol = zcontrols[0];

                loc.X = border;
                loc.Y = border;
                zcontrol.Location = loc;
                width = (this.Width) / 2 - gap - border;
                height = (this.Height) / 2 - border - gap;
                zcontrol.Width = width;
                zcontrol.Height = height;

                zcontrol = zcontrols[1];
                loc.Y = border;
                loc.X = (this.Width) / 2 + gap;
                zcontrol.Location = loc;
                zcontrol.Width = width;
                zcontrol.Height = height;
                
                zcontrol = zcontrols[2];
                loc.Y = (this.Height) / 2 + gap;
                loc.X = border;
                zcontrol.Location = loc;
                zcontrol.Width = width;
                zcontrol.Height = height;

                zcontrol = zcontrols[3];
                loc.Y = (this.Height) / 2 + gap;
                loc.X = (this.Width) / 2 + gap;
                zcontrol.Location = loc;
                zcontrol.Width = width;
                zcontrol.Height = height;

                return;
            }

        }
        private void InitializeZedControls(ChartConfiguration Config)
        {
            zcontrols = new RiZedGraphControlBase[4];
            this.components = new System.ComponentModel.Container();
            this.Controls.Clear();
            for (int i = 0; i < 4; i++)
            {
                RiZDiagramm diagr = new RiZDiagramm();
                if (Config != null)
                {
                    if (Config.Configuration.Diagramme != null)
                    {
                        if (Config.Configuration.Diagramme.Count > i)
                        {
                            diagr = Config.Configuration.Diagramme[i];
                        }
                    }
                }
                RiZedGraphControlBase zcontrol = ZedControlFactory.Create(diagr.ChartType);
                zcontrol.Location = new System.Drawing.Point(4, 4);
                zcontrol.Name = i.ToString(); ;
                zcontrol.ScrollGrace = 0;
                zcontrol.ScrollMaxX = 0;
                zcontrol.ScrollMaxY = 0;
                zcontrol.ScrollMaxY2 = 0;
                zcontrol.ScrollMinX = 0;
                zcontrol.ScrollMinY = 0;
                zcontrol.ScrollMinY2 = 0;
                zcontrol.Size = new System.Drawing.Size(183, 150);
                zcontrol.TabIndex = i;

                zcontrol.GraphPane.Title.Text = "";
                zcontrol.GraphPane.YAxis.Title.Text = "";
                zcontrol.ContextMenu = null;
                zcontrol.ContextMenuStrip = null;
                zcontrol.MouseDownEvent += new ZedGraphControl.ZedMouseEventHandler(zg1_MouseDownEvent);
                zcontrol.MouseUpEvent += new ZedGraphControl.ZedMouseEventHandler(zg1_MouseUpEvent);
                zcontrol.MouseMoveEvent += new ZedGraphControl.ZedMouseEventHandler(zg1_MouseMoveEvent);
                zcontrol.MouseWheel += new System.Windows.Forms.MouseEventHandler(zg1_MouseWheelEvent);
                zcontrol.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(zg1_MouseDoubleClick);
                zcontrol.IsEnableWheelZoom = false;
                zcontrol.IsEnableHZoom = true;
                zcontrol.IsEnableVZoom = false;
                zcontrol.IsEnableHPan = true;
                zcontrol.IsEnableVPan = false;
                zcontrol.IsShowPointValues = true;

                zcontrol.GraphPane.Chart.Fill = new Fill(Color.White, Color.LightGray, 45.0f);
                zcontrol.GraphPane.Fill = new Fill(Color.LightGray, Color.White, 45.0f);

                zcontrol.GraphPane.Margin.Top = 30;
                if (diagr.ChartType != RiZChartType.Line)
                {
                    zcontrol.GraphPane.Margin.Left = 3;
                    zcontrol.GraphPane.Margin.Right = 4;
                    zcontrol.GraphPane.Margin.Top = 4;
                    zcontrol.GraphPane.Margin.Bottom = 4;
                }
                    
                    
                zcontrol.GraphPane.Border.Width = 3;
                zcontrol.GraphPane.Border.Color = Color.LightGray;
                zcontrol.Init(null);
                zcontrol.SetMessdaten(ref mstList);
                this.Controls.Add(zcontrol);
                zcontrols[i] = zcontrol;
            }
            currentGraphPane = zcontrols[0].GraphPane;
            currentGraphPane.Border.Color = Color.Black;
            for (int i = 0; i < 4; i++)
            {
                zcontrols[i].Visible = (i < m_ControlCount);
            }
            this.ResumeLayout(false);
        }

        
     }
}
