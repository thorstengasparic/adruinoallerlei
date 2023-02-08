using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

using System;
using System.Runtime.Serialization;
using System.Xml;


using Arduino.Serial;
using GraphLib;
using GraficFilterDisplay;

namespace GraphicFilterDisplay
{

    public class PlotterGraphSetting
    {
        public PlotterGraphSetting()
        {
        }
        public string Name{ get; set; } = "Graph";
        public float GridDistY { get; set; } = 200;
        public float MaxY { get; set; } = 500;
        public float MinY { get; set; } = -500;
        public bool AutoScaleX { get; set; } = false;
        public bool AutoScaleY { get; set; } = false;

        //PlotterGraphPaneEx.LayoutMode LayoutMode { get; set; }
    }

    [DataContract]
    public class GuiConfig
    {
        const int MaxGraphs = 6;
        public GuiConfig()
        {
            CurrentCOM = new COMSettings();
            MaxSamples = 10000;
            NumGraphs = 4;
            GraphSetting = new PlotterGraphSetting[MaxGraphs];
            for (int i = 0; i < MaxGraphs; i++)
                GraphSetting[i] = new PlotterGraphSetting();
            ColorSchema = "GRAY";
            PanelLayout = PlotterGraphPaneEx.LayoutMode.NORMAL;
        }
        [DataMember]
        public PlotterGraphPaneEx.LayoutMode PanelLayout { get; set; }
        public string ColorSchema { get; set; }
        public PlotterGraphSetting[] GraphSetting { get; set; }
        public int NumGraphs { get; set; }
        public COMSettings CurrentCOM { get; set; }
        public int MaxSamples { get; set; }
        public SamplesDispatcher SamplesDisp = new SamplesDispatcher(MaxGraphs);
    }

}