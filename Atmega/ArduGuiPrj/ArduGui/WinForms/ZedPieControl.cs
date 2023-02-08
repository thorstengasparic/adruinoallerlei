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
    public partial class ZedPieControl : RiZedGraphControlBase
    {
        GraphPane myPane = null;
        
        public ZedPieControl()
        {
            InitializeComponent();
            myPane = GraphPane;
            // Set the GraphPane title
            myPane.Title.Text = "2004 ZedGraph Sales by Region\n($M)";
            myPane.Title.FontSpec.IsItalic = true;
            myPane.Title.FontSpec.Size = 24f;
            myPane.Title.FontSpec.Family = "Times New Roman";

            // Fill the pane background with a color gradient
            myPane.Fill = new Fill(Color.White, Color.Goldenrod, 45.0f);
            // No fill for the axis background
            //myPane.Chart.Fill.Type = FillType.None;
            /*
            // Set the legend to an arbitrary location
            myPane.Legend.Position = LegendPos.Float;
            myPane.Legend.Location = new ZedGraph.Location(0.95f, 0.15f, CoordType.PaneFraction, AlignH.Right, AlignV.Top);
            myPane.Legend.FontSpec.Size = 10f;
            myPane.Legend.IsHStack = false;
            */
            // Add some pie slices
            PieItem segment1 = myPane.AddPieSlice(20, Color.Navy, Color.White, 45f, 0, "North");
            PieItem segment3 = myPane.AddPieSlice(30, Color.Purple, Color.White, 45f, .0, "East");
            PieItem segment4 = myPane.AddPieSlice(10.21, Color.LimeGreen, Color.White, 45f, 0, "West");
            PieItem segment2 = myPane.AddPieSlice(40, Color.SandyBrown, Color.White, 45f, 0.2, "South");
            PieItem segment6 = myPane.AddPieSlice(250, Color.Red, Color.White, 45f, 0, "Europe");
            PieItem segment7 = myPane.AddPieSlice(50, Color.Blue, Color.White, 45f, 0.2, "Pac Rim");
            PieItem segment8 = myPane.AddPieSlice(400, Color.Green, Color.White, 45f, 0, "South America");
            PieItem segment9 = myPane.AddPieSlice(50, Color.Yellow, Color.White, 45f, 0.2, "Africa");
            
            base.AxisChange();
        }

        public override bool SetChartCursor()
        {
            if (diagramm == null) return true;
            if (diagramm.Graphen == null) return true;

            myPane.GraphObjList.Clear();
            myPane.CurveList.Clear();
            myPane.Title.Text = "";
            // Fill the pane background with a color gradient
            //myPane.Fill = new Fill(Color.White, Color.Goldenrod, 45.0f);
            // No fill for the axis background
            //myPane.Chart.Fill.Type = FillType.None;
            myPane.Legend.IsVisible = false;
            /*
            // Set the legend to an arbitrary location
            myPane.Legend.Position = LegendPos.Float;
            myPane.Legend.Location = new ZedGraph.Location(0.95f, 0.15f, CoordType.PaneFraction,AlignH.Right, AlignV.Top);
            myPane.Legend.FontSpec.Size = 10f;
            myPane.Legend.IsHStack = false;
            */
            // Add some pie slices

            //GraphPane.Chart.Fill = new Fill(Color.White, Color.LightGray, 45.0f);
            //GraphPane.Fill = new Fill(Color.LightGray, Color.White, 45.0f);

            //GraphPane.Margin.Top = 3;
            //GraphPane.Margin.Left = 3;
            //GraphPane.Margin.Right = 3;
            //GraphPane.Margin.Bottom = 3;

            //GraphPane.Border.Width = 3;
            ///GraphPane.Border.Color = Color.LightGray;
            double total = 0;
            int segmentOK = 0;
            foreach (RiZGraph curGr in diagramm.Graphen)
            {
                if (!mstList.ContainsKey(curGr.Variable)) continue;
                RiZGraphData mst = mstList[curGr.Variable];
                double val = 0;
                segmentOK++;
                bool erg = mst.GetValueAktZeitpunkt(cursorTime, diagramm.interpoliert, out val);
                total += val;
                PieItem segment1 = myPane.AddPieSlice(val, System.Drawing.Color.FromArgb(curGr.Graphcolor.R, curGr.Graphcolor.G, curGr.Graphcolor.B), Color.White, 45f, 0, curGr.Decription);
                segment1.LabelType = PieLabelType.None;
                segment1.ValueDecimalDigits = 2;
                if (!erg)
                {
                    segmentOK--;
                    segment1.Border.Color = Color.Red;
                    segment1.Border.Width = 10;
                    segment1.Label.Text += ": no Data";
                    segment1.Value = 0.0000001;
                    segment1.LabelType = PieLabelType.Name;
                    segment1.Displacement = 0.03;
                    segment1.Fill = new Fill(Color.Red);
                    
                }                
                else
                {
                    if (diagramm.ViewOption == 1) segment1.LabelType = PieLabelType.Name_Value_Percent;
                    if (diagramm.ViewOption == 2) segment1.LabelType = PieLabelType.Name_Value;
                }
            }
            if (segmentOK==0)
            {
                // Make a text label to highlight the total value
                
                TextObj text = new TextObj("No Data", 0.18F, 0.40F, CoordType.PaneFraction);
                text.Location.AlignH = AlignH.Right;
                text.Location.AlignV = AlignV.Bottom;
                text.FontSpec.Border.IsVisible = false;
                text.FontSpec.Fill = new Fill(Color.White, Color.FromArgb(255, 100, 100), 45F);
                text.FontSpec.StringAlignment = StringAlignment.Center;
                myPane.GraphObjList.Add(text);
                return true;
            }

            if (diagramm.ViewOption == 1)
            {
                // Make a text label to highlight the total value
                string strVal = String.Format(diagramm.Graphen[0].format + " {1}", total, diagramm.Graphen[0].Unit);
                TextObj text = new TextObj("Total:" + strVal, 0.18F, 0.40F, CoordType.PaneFraction);
                text.Location.AlignH = AlignH.Right;
                text.Location.AlignV = AlignV.Bottom;
                text.FontSpec.Border.IsVisible = false;
                text.FontSpec.Fill = new Fill(Color.White, Color.FromArgb(255, 100, 100), 45F);
                text.FontSpec.StringAlignment = StringAlignment.Center;
                myPane.GraphObjList.Add(text);

                // Create a drop shadow for the total value text item
                TextObj text2 = new TextObj(text);
                text2.FontSpec.Fill = new Fill(Color.Black);
                text2.Location.X += 0.008f;
                text2.Location.Y += 0.01f;
                myPane.GraphObjList.Add(text2);
            }

            return true;
        }

        public override void DrawGraph()
        {
        }

        
    }
}
