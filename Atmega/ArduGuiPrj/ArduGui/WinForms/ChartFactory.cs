using System;
using System.IO;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using ZedGraph;
using ArduGui.Controller;
using ArduGui.Model;

namespace ArduGui.View
{

    public class RiZedGraphControlBase : ZedGraphControl
    {
        protected DateTime startTime;
        protected DateTime endTime;
        protected DateTime cursorTime;
        protected IDictionary<uint, RiZGraphData> mstList;
        public RiZDiagramm diagramm = null;
        
        public virtual bool Init(RiZDiagramm diagramm)
        {
            cursorTime = DateTimeHelper.ToRaster(DateTime.Now, 10);
            DateTime dtDummy = new DateTime();
            startTime = DateTimeHelper.GetStartTime(cursorTime, dtDummy, dtDummy, Raster.sec10, Skalierung.Hour);
            endTime = DateTimeHelper.GetEndTime(cursorTime, dtDummy, dtDummy, Raster.sec10, Skalierung.Hour);
            this.diagramm = diagramm;
            if (diagramm == null) return false;
            return true;
        }

        public virtual void SetMessdaten(ref IDictionary<uint, RiZGraphData> mstList)
        {
            this.mstList = mstList;
        }

        public virtual bool SetTime(DateTime startTime, DateTime endTime, DateTime cursorTime)
        {
            if (mstList == null) return false;

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
        public virtual bool SetXAxis()
        {
            return true;
        }


        public virtual bool SetChartCursor()
        {
            return false;
        }

        public virtual void DrawGraph()
        {
        }

        private void InitializeComponent()
        {
            this.SuspendLayout();
            // 
            // RiZedGraphControlBase
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.Name = "RiZedGraphControlBase";
            this.Size = new System.Drawing.Size(216, 171);
            this.ResumeLayout(false);

        }

    }
    
    public class ZedControlFactory
    {
        static public RiZedGraphControlBase Create(RiZChartType type)
        {
            //RiZedGraphControl nc1 = new RiZedGraphControl();
            //return (RiZedGraphControlBase)nc1;

            if (type == RiZChartType.Line)
            {
                RiZedGraphControl nc = new RiZedGraphControl();
                return (RiZedGraphControlBase)nc;
            }
            if (type == RiZChartType.Pie)
            {
                ZedPieControl nc = new ZedPieControl();
                return (RiZedGraphControlBase)nc;
            }
            return new RiZedGraphControlBase();
        }
    }
}
