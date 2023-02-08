using System;
using System.IO;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using ZedGraph;

namespace ArduGui.View
{
    class RiZedGraphControl : RiZedGraphControlBase
    {
        List<YSkalierung> YSkalierungen;
        /*
        DateTime startTime;
        DateTime endTime;
        DateTime cursorTime;
        
        private IDictionary<uint, RiZGraphData> mstList;
         * */
        /*
        public override bool SetTime(DateTime startTime, DateTime endTime, DateTime cursorTime)
        {
            lock (mstList)
            {
                bool SetXAchse = false;
                if ((endTime.Ticks > 0) && (startTime.Ticks > 0))
                {
                    //if ((this.startTime.Ticks != startTime.Ticks) || (this.endTime.Ticks != endTime.Ticks))
                    {
                        SetXAchse = true;
                    }
                    this.startTime = startTime;
                    this.endTime = endTime;
                }

                this.cursorTime = cursorTime;
                if (SetXAchse) SetXAxis();

                SetChartCursor();
            }
            Invalidate();
            return true;
        }
        */
        
        public override bool Init(RiZDiagramm diagramm)
        {
            /*
            cursorTime = DateTimeHelper.ToRaster(DateTime.Now, 10);
            DateTime dtDummy = new DateTime();
            startTime = DateTimeHelper.GetStartTime(cursorTime, dtDummy, dtDummy, Raster.sec10, Skalierung.Stunde);
            endTime = DateTimeHelper.GetEndTime(cursorTime, dtDummy, dtDummy, Raster.sec10, Skalierung.Stunde);
            
            this.diagramm = diagramm;
            if (diagramm == null) return true;
             * */
            if (!base.Init(diagramm)) return true;

            SetXAxis();
            SetYAxis();
            SetChartCursor();
            return true;
        
        }

        public override bool SetChartCursor()
        {
            foreach (CurveItem curve in GraphPane.CurveList)
            {
                if ((int)curve.Tag == 42)
                {
                    GraphPane.CurveList.Remove(curve);
                    break;
                }
            }

            PointPairList list = new PointPairList();
            double time = new XDate(cursorTime);
            double min = GraphPane.YAxis.Scale.Min;
            double max = GraphPane.YAxis.Scale.Max;

            RectangleF chartRect = GraphPane.Chart.Rect;
            PointF ptfMin = new PointF(chartRect.Left, chartRect.Bottom);
            PointF ptfMax = new PointF(chartRect.Right, chartRect.Top);
            double x, y;
            GraphPane.ReverseTransform(ptfMax, out x, out y);
            list.Add(time, min);
            list.Add(time, max);
            LineItem myCurve = GraphPane.AddCurve("", list, Color.Red, SymbolType.None);
            myCurve.YAxisIndex = 0;
            myCurve.IsY2Axis = false;
            myCurve.Tag = 42;
            GraphPane.YAxis.Scale.Min = min;
            GraphPane.YAxis.Scale.Max = max;
            try
            {
                AxisChange();
            }
            catch { }

            return true;
        }


        public bool SetYAxis()
        {
            GraphPane.CurveList.Clear();
            
            GraphPane.YAxis.MajorTic.IsOpposite = false;
            GraphPane.YAxis.MinorTic.IsOpposite = false;
            // Align the Y axis labels so they are flush to the axis
            GraphPane.YAxis.Scale.Align = AlignP.Inside;
            GraphPane.YAxis.MajorGrid.IsVisible = true;

            // Inforamtionen über Skalierung der y-Achse sammeln
            YSkalierungen = new List<YSkalierung>();
            foreach (RiZGraph grafik in diagramm.Graphen)
            {
                bool found = false;
                foreach (YSkalierung ySkal in YSkalierungen)
                {
                    // habe ich schon Skalierungen, dann bei den gleichen Einheiten die absoluten Min/Max Werte ermitteln
                    if (String.Compare(ySkal.YSkalierungID, grafik.YAchsenIDintern) == 0)
                    {
                        ySkal.AddVariable(grafik.Variable.ToString());
                        ySkal.AddGrafik(grafik.ID);
                        found = true;
                        if (grafik.MaxY != grafik.MinY)
                        {
                            if (ySkal.max < grafik.MaxY) ySkal.max = grafik.MaxY;
                            if (ySkal.min > grafik.MinY) ySkal.min = grafik.MinY;
                        }
                    }
                }
                if (!found)
                {
                    // Keine doppelte YSkalierungen gefunden, neuen eintrag für die akt. Grafik erzeugen
                    YSkalierung yScale = new YSkalierung(grafik.YAchsenIDintern, grafik.YAxisText, grafik.Unit, grafik.MinY, grafik.MaxY);
                    yScale.AddVariable(grafik.Variable.ToString());
                    yScale.AddGrafik(grafik.ID);
                    YSkalierungen.Add(yScale);
                }
            }

            int FontSpecSize = 10;

            for (int curSkal = 0; curSkal < YSkalierungen.Count; curSkal++)
            {
                if (curSkal == 0)
                {
                    GraphPane.YAxis.Title.FontSpec.Size = FontSpecSize;
                    GraphPane.YAxis.Title.Text = YSkalierungen[curSkal].Text;
                    if (YSkalierungen[curSkal].min != YSkalierungen[curSkal].max)
                    {
                        GraphPane.YAxis.Scale.Min = YSkalierungen[curSkal].min;
                        GraphPane.YAxis.Scale.Max = YSkalierungen[curSkal].max;
                    }
                    else
                    {
                        GraphPane.YAxis.Scale.MaxAuto = true;
                    }
                    YSkalierungen[curSkal].yAxis = GraphPane.YAxis;
                    YSkalierungen[curSkal].y2Axis = null;
                    YSkalierungen[curSkal].yAxisIndex = curSkal;
                }

                if (curSkal == 1)
                {
                    GraphPane.Y2Axis.Title.FontSpec.Size = FontSpecSize;
                    GraphPane.Y2Axis.Title.Text = YSkalierungen[curSkal].Text;

                    if (YSkalierungen[curSkal].min != YSkalierungen[curSkal].max)
                    {
                        GraphPane.Y2Axis.Scale.Min = YSkalierungen[curSkal].min;
                        GraphPane.Y2Axis.Scale.Max = YSkalierungen[curSkal].max;
                    }
                    else
                    {
                        GraphPane.Y2Axis.Scale.MaxAuto = true;
                    }

                    GraphPane.Y2Axis.IsVisible = true;
                    GraphPane.Y2Axis.MajorTic.IsOpposite = false;
                    GraphPane.Y2Axis.MinorTic.IsOpposite = false;
                    GraphPane.Y2Axis.MajorGrid.IsZeroLine = false;
                    GraphPane.YAxis.MajorGrid.IsZeroLine = false;
                    YSkalierungen[curSkal].yAxis = null;
                    YSkalierungen[curSkal].y2Axis = GraphPane.Y2Axis;
                    YSkalierungen[curSkal].yAxisIndex = curSkal-1;
                }

                if (curSkal > 1)
                {
                    YAxis yAxis3 = new YAxis(YSkalierungen[curSkal].Text);
                    GraphPane.YAxisList.Add(yAxis3);
                    yAxis3.MajorTic.IsInside = false;
                    yAxis3.MinorTic.IsInside = false;
                    yAxis3.MajorTic.IsOpposite = false;
                    yAxis3.MinorTic.IsOpposite = false;
                    // Align the Y2 axis labels so they are flush to the axis
                    yAxis3.Scale.Align = AlignP.Inside;

                    yAxis3.Title.FontSpec.Size = FontSpecSize;
                    yAxis3.Title.Text = YSkalierungen[curSkal].Text;
                    if (YSkalierungen[curSkal].min != YSkalierungen[curSkal].max)
                    {
                        yAxis3.Scale.Min = YSkalierungen[curSkal].min;
                        yAxis3.Scale.Max = YSkalierungen[curSkal].max;
                    }
                    else 
                    {
                        yAxis3.Scale.MaxAuto = true;
                    }

                    YSkalierungen[curSkal].yAxis = yAxis3;
                    YSkalierungen[curSkal].yAxisIndex = curSkal-1;
                }
            }

            AxisChange();
            return true;
        }

        public override bool SetXAxis()
        {
            GraphPane.XAxis.Type = AxisType.Date;
            GraphPane.XAxis.MajorGrid.IsVisible = true;
            GraphPane.XAxis.MajorTic.IsOpposite = false;    
            GraphPane.XAxis.MinorTic.IsOpposite = false;
            GraphPane.XAxis.Scale.FontSpec.Size = 10;

            TimeSpan ts = new TimeSpan();
            ts = endTime - startTime;

            int darstellung = 0;                                // Minutendarstellung
            if (ts.TotalMinutes > 60.0 * 5.0) darstellung = 1;  // Stundendarstellung
            if (ts.TotalDays > 3.0) darstellung = 2;            // Tagesdarstellung

            if (darstellung == 0)
            {   // Minutendarstellung
                GraphPane.XAxis.Scale.Min = (double)new XDate(startTime.AddSeconds(-10));
                GraphPane.XAxis.Scale.Max = (double)new XDate(endTime);
                
                GraphPane.XAxis.Scale.MajorUnit = DateUnit.Minute;
                
                if (ts.TotalMinutes > 20)
                    GraphPane.XAxis.Scale.MajorStep = 5;
                else
                    GraphPane.XAxis.Scale.MajorStep = 2;

                GraphPane.XAxis.Scale.MinorUnit = DateUnit.Minute;
                GraphPane.XAxis.Scale.MinorStep = 1;
                GraphPane.XAxis.Scale.Format = "HH:mm:ss";
                if (diagramm != null)
                GraphPane.XAxis.Title.Text = "Stunde/Minute";//"diagramm.xAchsenbeschriftung;
            }

            if (darstellung == 1)
            {   // Stundendarstellung
                GraphPane.XAxis.Scale.Min = (double)new XDate(startTime.AddSeconds(-10));
                GraphPane.XAxis.Scale.Max = (double)new XDate(endTime);

                GraphPane.XAxis.Scale.MajorUnit = DateUnit.Hour;
                GraphPane.XAxis.Scale.MajorStep = 3;

                GraphPane.XAxis.Scale.MinorUnit = DateUnit.Hour;
                GraphPane.XAxis.Scale.MinorStep = 1;
                GraphPane.XAxis.Scale.Format = "HH:mm";
                if (diagramm != null)
                GraphPane.XAxis.Title.Text = "Stunden";//"diagramm.xAchsenbeschriftung;
            }

            if (darstellung == 2)
            {   // Tagesdarstellung

                GraphPane.XAxis.Scale.Min = (double)new XDate(startTime.AddSeconds(-10));
                GraphPane.XAxis.Scale.Max = (double)new XDate(endTime);

                GraphPane.XAxis.Scale.MajorUnit = DateUnit.Day;
                GraphPane.XAxis.Scale.MajorStep = 1;
                GraphPane.XAxis.Scale.Format = "dd";

                GraphPane.XAxis.Scale.MinorUnit = DateUnit.Hour;
                GraphPane.XAxis.Scale.MinorStep = 6;

                if (diagramm != null)
                    GraphPane.XAxis.Title.Text = "Tag";// diagramm.xAchsenbeschriftung;
            }
            
            AxisChange();
            Invalidate();
            return true;
        }
        
        public void DrawGraph_()
        {
            lock (mstList)
            {
                GraphPane.CurveList.Clear();
                if (mstList != null)
                {
                    foreach (YSkalierung yScal in YSkalierungen)
                    {

                        foreach (uint id in mstList.Keys)
                        {
                            RiZGraphData mst = mstList[id];
                            if (!yScal.VariableBelongsToAxis(id.ToString())) continue;
                            RiZGraph curGr = diagramm.GetGraphic(id.ToString());
                            if (curGr == null) continue;

                            FilteredPointList fList = new FilteredPointList(mst.X, mst.Y);
                            fList.SetBounds(-100000000, 100000000, 50000);

                            LineItem myCurve = GraphPane.AddCurve("", fList, System.Drawing.Color.FromArgb(curGr.Graphcolor.R,curGr.Graphcolor.B,curGr.Graphcolor.G) , SymbolType.None);

                            myCurve.IsY2Axis = false;
                            if (yScal.y2Axis != null)
                                myCurve.IsY2Axis = true;
                            myCurve.Line.IsOptimizedDraw = true;
                            if (!diagramm.interpoliert)
                            {
                                myCurve.Line.StepType = StepType.ForwardStep;
                            }
                            /*
                            if (curGr.GraphDispType == 2)
                            {
                                myCurve.Line.StepType = StepType.RearwardStep;
                            }
                            if (curGr.GraphDispType == 3)
                            {
                                myCurve.Line.StepType = StepType.ForwardSegment;
                            }
                            if (curGr.GraphDispType == 4)
                            {
                                myCurve.Line.IsSmooth = true;
                            }
                             * */
                            myCurve.IsSelectable = true;
                            myCurve.YAxisIndex = yScal.yAxisIndex;
                            myCurve.Tag = 0;
                            if (yScal.min == yScal.max)
                                myCurve.GetYAxis(GraphPane).Scale.MaxAuto = true;
                        }
                    }
                    SetChartCursor();
                    AxisChange();
                }
            }
            Invalidate();
        }


        public override void DrawGraph()
        {
            lock (mstList)
            {
                GraphPane.CurveList.Clear();
                if (mstList != null)
                {
                    foreach (YSkalierung yScal in YSkalierungen)
                    {

                        foreach (RiZGraph curGr in diagramm.Graphen)
                        {
                            if (!yScal.GrafikBelongsToAxis(curGr.ID)) continue;
                            if (!mstList.ContainsKey(curGr.Variable)) continue;
                            RiZGraphData mst = mstList[curGr.Variable];
                            FilteredPointList fList = null;
                            if (curGr.faktor == 1.0)
                            {
                                fList = new FilteredPointList(mst.X, mst.Y);
                            }
                            else
                            {
                                double[] fY = (double[])mst.Y.Clone();
                                for (int i = 0; i < fY.Length; i++) fY[i] *= curGr.faktor;
                                fList = new FilteredPointList(mst.X, fY);
                            }
                            fList.SetBounds(-100000000, 100000000, 50000);

                            LineItem myCurve = GraphPane.AddCurve("", fList, System.Drawing.Color.FromArgb(curGr.Graphcolor.R, curGr.Graphcolor.G, curGr.Graphcolor.B), SymbolType.None);

                            myCurve.IsY2Axis = false;
                            if (yScal.y2Axis != null)
                                myCurve.IsY2Axis = true;
                            myCurve.Line.IsOptimizedDraw = true;
                            if (!diagramm.interpoliert)
                            {
                                myCurve.Line.StepType = StepType.ForwardStep;
                            }
                            /*
                            if (curGr.GraphDispType == 2)
                            {
                                myCurve.Line.StepType = StepType.RearwardStep;
                            }
                            if (curGr.GraphDispType == 3)
                            {
                                myCurve.Line.StepType = StepType.ForwardSegment;
                            }
                            if (curGr.GraphDispType == 4)
                            {
                                myCurve.Line.IsSmooth = true;
                            }*/
                            myCurve.IsSelectable = true;
                            myCurve.YAxisIndex = yScal.yAxisIndex;
                            myCurve.Tag = 0;
                            if (yScal.min == yScal.max)
                                myCurve.GetYAxis(GraphPane).Scale.MaxAuto = true;
                        }
                    }
                    SetChartCursor();
                    try
                    {
                        AxisChange();
                    }
                    catch { };
                }
            }

            Invalidate();
        }

        private void InitializeComponent()
        {
            this.SuspendLayout();
            // 
            // RiZedGraphControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.Name = "RiZedGraphControl";
            this.Size = new System.Drawing.Size(363, 257);
            this.ResumeLayout(false);

        }
    }
   

    public class DateTimeHelper
    {
        static public DateTime ToRaster(DateTime indate, int rasterSec)
        {
            DateTime date = new DateTime(indate.Ticks);

            if (date.Millisecond >= 500)
            {
                date = date.AddMilliseconds(1000 - date.Millisecond);
            }
            else
            {
                date = date.AddMilliseconds(date.Millisecond * (-1));
            }

            int rest = date.Second % rasterSec;
            if (rest > 4)
                rest = 10 - rest;
            else
                rest = rest * (-1);

            date = date.AddSeconds(rest);
            
            return date;
        }

        static public DateTime GetStartTime(DateTime dtCurrentTime, DateTime StartTime, DateTime EndTime, Raster raster, Skalierung skalierung)
        {
            DateTime dtTime;
            int RasterSec = (int)raster;
            switch (skalierung)
            {
                case Skalierung.Week:
                    int days = (int)dtCurrentTime.DayOfWeek;
                    if (days == 0) days = 7;
                    dtTime = new DateTime(dtCurrentTime.Year, dtCurrentTime.Month, dtCurrentTime.Day, 0, 0, RasterSec).AddDays(days * (-1) + 1);
                    break;

                case Skalierung.Day:
                    dtTime = new DateTime(dtCurrentTime.Year, dtCurrentTime.Month, dtCurrentTime.Day, 0, 0, RasterSec);
                    break;

                case Skalierung.Hour:
                    dtTime = new DateTime(dtCurrentTime.Year, dtCurrentTime.Month, dtCurrentTime.Day, dtCurrentTime.Hour, 0, RasterSec);
                    break;

                case Skalierung.Month:
                    dtTime = new DateTime(dtCurrentTime.Year, dtCurrentTime.Month, 1, 0, 0, RasterSec);
                    break;

                default:

                    if (StartTime.Ticks > EndTime.Ticks)
                    {
                        DateTime tmpDT = new DateTime(StartTime.Ticks);
                        StartTime = EndTime;
                        EndTime = tmpDT;
                    }
                    TimeSpan ts = EndTime.Subtract(StartTime);
                    
                    while (dtCurrentTime.Ticks > EndTime.Ticks)
                    {
                        EndTime = EndTime.Add(ts);
                        StartTime = StartTime.Add(ts);
                        if (ts.Ticks == 0) return EndTime;
                    }

                    while (dtCurrentTime.Ticks < StartTime.Ticks)
                    {
                        EndTime = EndTime.Subtract(ts);
                        StartTime = StartTime.Subtract(ts);
                        if (ts.Ticks == 0) return EndTime;
                    }
                    dtTime = StartTime;
                    break;
            }
            return dtTime;
        }
        static public DateTime GetEndTime(DateTime dtCurrentTime, DateTime StartTime, DateTime EndTime, Raster raster, Skalierung skalierung)
        {
            DateTime dtTime;
            int RasterSec = (int)raster;

            switch (skalierung)
            {
                case Skalierung.Week:
                    int days = (int)dtCurrentTime.DayOfWeek;
                    if (days == 0) days = 7;
                    dtTime = new DateTime(dtCurrentTime.Year, dtCurrentTime.Month, dtCurrentTime.Day, 0, 0, 0).AddDays(7 - days + 1);
                    break;

                case Skalierung.Day:
                    dtTime = new DateTime(dtCurrentTime.Year, dtCurrentTime.Month, dtCurrentTime.Day, 0, 0, 0).AddDays(1);
                    break;

                case Skalierung.Hour:
                    dtTime = new DateTime(dtCurrentTime.Year, dtCurrentTime.Month, dtCurrentTime.Day, dtCurrentTime.Hour, 0, 0).AddHours(1);
                    break;

                case Skalierung.Month:
                    dtTime = new DateTime(dtCurrentTime.Year, dtCurrentTime.Month, 1, 0, 0, 0);
                    dtTime = dtTime.AddMonths(1);
                    dtTime = dtTime.AddDays(-1);
                    break;
                default:
                    if (StartTime.Ticks > EndTime.Ticks)
                    {
                        DateTime tmpDT = new DateTime(StartTime.Ticks);
                        StartTime = EndTime;
                        EndTime = tmpDT;
                    }
                    TimeSpan ts = EndTime.Subtract(StartTime);

                    while (dtCurrentTime.Ticks > EndTime.Ticks)
                    {
                        EndTime = EndTime.Add(ts);
                        StartTime = StartTime.Add(ts);
                    }

                    while (dtCurrentTime.Ticks < StartTime.Ticks)
                    {
                        EndTime = EndTime.Subtract(ts);
                        StartTime = StartTime.Subtract(ts);
                    }
                    dtTime = EndTime;
                    break;
            }
            return dtTime;
        }

        static public ulong MilliTimeStamp(DateTime TheDate, int GMT)
        {
            DateTime d1 = new DateTime(1970, 1, 1);
            DateTime d2 = TheDate.ToUniversalTime();
            TimeSpan ts = new TimeSpan(d2.Ticks - d1.Ticks);

            return Convert.ToUInt64(ts.TotalSeconds) * 1000;
        }
        static public DateTime DateTimeStamp(long MilliTimeStamp, int GMT)
        {
            DateTime d1 = new DateTime(1970, 1, 1);
            DateTime d2 = d1.AddMilliseconds(MilliTimeStamp + (3600 * GMT) * 1000);
            return d2;
        }
    }

    class YSkalierung
    {
        public string YSkalierungID = "";
        public string Text = "";
        public string Unit = "";
        public double min;
        public double max;
        public int yAxisIndex;
        public YAxis yAxis;
        public Y2Axis y2Axis;

        private List<String> Variables = null;
        private List<Guid> Grafiken = null;

        public YSkalierung(string YSkalierungID, string Beschriftung, string Unit, double min, double max)
        {
            this.YSkalierungID = YSkalierungID;
            this.Text = Beschriftung + " [" + Unit + "]";
            this.Unit = Unit;
            this.min = min;
            this.max = max;

            Variables = new List<string>();
            Grafiken = new List<Guid>();
            yAxis = null;
            y2Axis = null;
            yAxisIndex = -1;
        }
        public bool AddVariable(string variable)
        {
            Variables.Add(variable);
            return true;
        }
        
        public bool AddGrafik(Guid variable)
        {
            Grafiken.Add(variable);
            return true;
        }
        
        public bool VariableBelongsToAxis(string variable)
        {
            return Variables.Contains(variable);
        }
        
        public bool GrafikBelongsToAxis(Guid id)
        {
            return Grafiken.Contains(id);
        }
    }
    public class RiZGraphData
    {

        public string variable = "";
        public string decription = "";
        public double[] X;
        public double[] Y;

        public bool GetValueAktZeitpunkt(DateTime time, bool interpoliert, out double value)
        {
            value = 0.0;
            if (GetValue(time, interpoliert, out value))
            {
                if (DateTime.Now.Ticks < time.Ticks)
                {
                    // liegt der Zeitpunkt des Wertes mehr als 10 Sekunden in der Zukunft, diese ignorieren 
                    TimeSpan ts = DateTime.Now.Subtract(time);
                    if (ts.TotalSeconds > 10) return false;
                }
                return true;
            }
            else
            {
                // Wert konnte nicht ermittelt werden.
                if (DateTime.Now.Ticks < time.Ticks)
                {
                    TimeSpan ts = DateTime.Now.Subtract(time);
                    // liegt der gesuchte Wert in der Nähe der aktuellen Uhrzeit (10 Sekunde)
                    // wird der letzte Wert als gültiger Wert eingesetzt
                    if ((ts.TotalSeconds < 10) && (ts.TotalSeconds > -10))
                    {
                        value = Y[Y.Length - 1];
                        return true;
                    }
                }
                return false;
            }
            return false;
        }
        public bool GetValue(DateTime time, bool interpoliert, out double value)
        {
            value = 0.0;
            if (X.Length == 0) return false;
            XDate t = new XDate(time);
            if (X[0] > t.XLDate) return false;
            if (X[X.Length - 1] < t.XLDate) return false;
            
            // todo BinarySearch()
            int i;
            for (i = 0; i < X.Length; i++)
            {
                if (t.XLDate < X[i]) break;
            }
            if ((i - 1) < 0) return false;
            value = Y[i-1];
            if (!interpoliert) return true;

            if (i >= X.Length) return true;
            if (t.XLDate == X[i - 1]) return true;
            double x1 = X[i - 1];
            double x2 = X[i];
            double y1 = Y[i - 1];
            double y2 = Y[i];
            if ((y2-y1) == 0.0) return true;

            value = (y2 - y1) / (x2 - x1) * t.XLDate + y1 - (y2 - y1) / (x2 - x1) * x1;
            //value = (X[i] - X[i - 1]) / (t.XLDate - X[i - 1]) * (Y[i-1] - Y[i]) + Y[i];

            return true;
        }

        public RiZGraphData(string variable, string decription)
        {
            this.variable = variable;
            this.decription = decription;
            X = new double[0];
            Y = new double[0];
        }

        public void SetDummydata(double min, double max)
        {
            DateTime cursorTime = DateTime.Now;
            DateTime startTime = cursorTime.AddMinutes(-20);
            DateTime endTime = cursorTime.AddMinutes(10);

            List<double> x = new List<double>();
            List<double> y = new List<double>();


            
            double val = 0.0;
            double cnt = 0.0;
            double vari = Convert.ToDouble(variable);
            Random rd = new Random(cursorTime.Millisecond);
            while (true)
            {
                val = Math.Sin((cnt + vari / 100) + vari);
                val *= max / 2.0;
                val += max / 2.0;
                
                x.Add(new XDate(startTime));
                y.Add(val);

                startTime = startTime.AddSeconds(5);
                if (startTime.Ticks > endTime.Ticks) break;
                cnt += 50;

            }

            X = x.ToArray();
            Y = y.ToArray();
        }
    }
    

}