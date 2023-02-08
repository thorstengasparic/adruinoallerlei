using System;
using System.IO;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using System.Windows;
using System.Windows.Media;

namespace ArduGui.View
{
    /// <summary>
    /// Mögliche Charttypen: Line Torte, Gantt.
    /// </summary>
    public enum RiZChartType { Line, Pie, Gantt };

    public enum Skalierung
    {
        Free = 0,
        Week = 1,
        Day = 2,
        Hour = 3,
        Month = 4,
        Year = 5
    }

    public enum Raster
    {
        sec1 = 1,
        sec10 = 10,
    }

    /// <summary>
    /// Repräsentiert die komplette Kofiguration einen RiZoneChart
    /// </summary>
    public class ChartConfiguration
    {
        private DiagrammConfiguration m_DiagrammCfg;
        private string m_Name;
        private string m_Description;
        private string SqlConnectionstring;
        /// <summary>
        /// Name des Diagramms
        /// </summary>

        public string Name { get { return m_Name; } set { m_Name = value; } }
        /// <summary>
        /// Diagramm Beschreibung
        /// </summary>
        public string Description { get { return m_Description; } set { m_Description = value; } }
        public DiagrammConfiguration Configuration { get { return m_DiagrammCfg; } set { m_DiagrammCfg = value; } }
        
        public bool Serialize(string filename)
        {
            string xml = Serialize();
            try
            {
                File.WriteAllText(filename, xml);
            }
            catch { return false; }
            return true;
        }
        public string Serialize()
        {
            XmlSerializer serializer = new XmlSerializer(typeof(ChartConfiguration));
            StringBuilder stringBuilder = new StringBuilder();
            StringWriter stringWriter = new StringWriter(stringBuilder);
            serializer.Serialize(stringWriter, this);
            return stringBuilder.ToString();
        }

        public static ChartConfiguration FromString(string xmlString)
        {

            ChartConfiguration data = null;
            try
            {
                XmlSerializer serializer = new XmlSerializer(typeof(ChartConfiguration));
                data = (ChartConfiguration)serializer.Deserialize(new StringReader(xmlString));
            }
            catch { }
            return data;
        }
        public ChartConfiguration()
        {
            m_DiagrammCfg = new DiagrammConfiguration();
            m_Name = "none";
            m_Description = "Default Chart";
            SqlConnectionstring = "";
        }
        public ChartConfiguration(string name, string Descr)
        {
            m_DiagrammCfg = new DiagrammConfiguration();
            this.Name = name;
            this.Description = Descr;
            SqlConnectionstring = "";
        }
        
    }

    /// <summary>
    /// Repräsentiert die Konfiguration die zum Aufbau der einzelnen Diagramme im Chart notwendig sind
    /// </summary>
    public class DiagrammConfiguration
    {
        private List<RiZDiagramm> diagramme;
        private RiZChartType chartType;
        private bool interpoliert;

        /// <summary>
        /// Eindeutige ID des Chart
        /// </summary>
        public Guid ID;

        /// <summary>
        /// ChartType für alle Diagramme im Chart. Default: Line
        /// </summary>
        public RiZChartType ChartType
        {
            get { return chartType; }
            set { chartType = value; }
        }

        /// <summary>
        /// Linien Typ im LineDiagramm. Linepunkte interpoliert oder stufig
        /// </summary>
        public bool Interpoliert
        {
            get { return interpoliert; }
            set { interpoliert = value; }
        }

        /// <summary>
        /// Die einzelnen Diagramme im Chart, bei Linie bis zu vier Diagramme, sonst nur ein Diagramm.
        /// </summary>
        public List<RiZDiagramm> Diagramme
        {
            get { return diagramme; }
            set { diagramme = value; }
        }

        /// <summary>
        /// Fügt ein einzelnes Diagramm einem Chart hinzu
        /// </summary>
        public void AddDiagramm(RiZDiagramm diagramm)
        {
            diagramm.interpoliert = this.interpoliert;
            diagramme.Add(diagramm);
        }

        /// <summary>
        /// Standard Konstruktor
        /// </summary>
        public DiagrammConfiguration()
        {
            ID = Guid.NewGuid();
            chartType = RiZChartType.Line;
            interpoliert = true;
            diagramme = new List<RiZDiagramm>();
        }

        /// <summary>
        /// Liefert alle VariablenIDs zurück, die dieses Chart anzeigt
        /// </summary>
        public IDictionary<uint, VariableType> GetVariables()
        {
            IDictionary<uint, VariableType> varList = new Dictionary<uint, VariableType>();
            foreach (RiZDiagramm diagr in Diagramme)
            {   // Über alle konfigurierten Diagramme im Chart laufen
                foreach (RiZGraph graph in diagr.Graphen)
                {
                    // Über alle Grafiken im jeweiligen Diagramm laufen
                    try
                    {
                        // die einzelnen Variablen der Grafen in das Dictionary eintragen
                        varList.Add(graph.Variable, graph.ValueType);
                    }
                    catch { /* doppelte Variablen ignorieren*/ }
                }
            }
            return varList;
        }
    }

    /// <summary>
    /// Repräsentiert die Konfiguration eines einzelnen Diagramm im Chart
    /// </summary>
    public class RiZDiagramm
    {
        public Guid ID ;  // DiagrammId innerhalb eines Chart
        private string name; // Name des Diagramms
        private string xAchsenbeschriftung; // 
        private List<RiZGraph> m_graphen = new List<RiZGraph>(); // die einelnen Kurve im Diagramme
        public bool interpoliert = true;
        private RiZChartType chartType;
        private int viewOption = 0;

        public int ViewOption
        {
            get { return viewOption; }
            set { viewOption = value; }
        }
        /// <summary>
        /// ChartType für alle Diagramme im Chart. Default: Line
        /// </summary>
        public RiZChartType ChartType
        {
            get { return chartType; }
            set { chartType = value; }
        }
        private Color m_CursorColor;
        /// <summary>
        /// Die Farbe des ZeitCursurs im Diagramm
        /// </summary>
        //[XmlIgnoreAttribute()]
        public Color CursorColor
        {
            get { return m_CursorColor; }
            set { m_CursorColor = value; }
        }
        /*
        [XmlElement("CursorColor")]
        public string CursorColorHtml
        {
            get { return ColorTranslator.ToHtml(m_CursorColor); }
            set { m_CursorColor = ColorTranslator.FromHtml(value); }
        }
        */
        /// <summary>
        /// Der Name des jeweiligen Diagramms im Chart
        /// </summary>
        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        /// <summary>
        /// XAchsenbeschriftung des Diagramms im Chart
        /// </summary>
        public string XAchsenbeschriftung
        {
            get { return xAchsenbeschriftung; }
            set { xAchsenbeschriftung = value; }
        }

        /// <summary>
        /// Zugriff auf alle Grafiken (Kurven) im Chart für die Serialisierung. 
        /// Nicht zum Hinzufügen einens Graphen(Kurve)!! (siehe AddGraph() )
        /// </summary>
        [XmlIgnoreAttribute()]
        public List<RiZGraph> Graphen
        {
            get
            { //nur eine Kopie zurückgeben.
                List<RiZGraph> grCopy = new List<RiZGraph>();
                grCopy.AddRange(m_graphen);
                return grCopy;
            }
            set { m_graphen = value; }
        }

        [XmlElement("Graphen")]
        public List<RiZGraph> XMLGraphen
        {
            get
            {   return m_graphen;
            }
            set 
            {   m_graphen = value; 
            }
        }

        /// <summary>
        /// Hinzufügen eines Graphen zum Diagramm
        /// </summary>
        public void AddGraph(RiZGraph graph)
        {
            m_graphen.Add(graph);

        }
        public void DelGraph(RiZGraph graph)
        {
            m_graphen.Remove(graph);
        }
        public System.Drawing.Color NextColor()
        {
            System.Windows.Media.Color col = Colors.Black;
            
            if (m_graphen.Count == 0) col = Colors.Red;
            if (m_graphen.Count == 1) col = Colors.Blue;
            if (m_graphen.Count == 2) col = Colors.Green;
            if (m_graphen.Count == 3) col = Colors.Orange;
            if (m_graphen.Count == 4) col = Colors.Orchid;
            if (m_graphen.Count == 5) col = Colors.Magenta;
            if (m_graphen.Count == 6) col = Colors.PeachPuff;
            return System.Drawing.Color.FromArgb(col.R, col.B, col.G);
        }
        public RiZDiagramm Clone(bool newId)
        {
            RiZDiagramm newDiagramm = new RiZDiagramm();
            if (!newId) newDiagramm.ID = ID;
            newDiagramm.name = name;
            newDiagramm.xAchsenbeschriftung = xAchsenbeschriftung; 
            
            newDiagramm.interpoliert = interpoliert;
            newDiagramm.chartType = chartType;
            newDiagramm.viewOption = viewOption;

            foreach(RiZGraph graph in m_graphen)
            {
                newDiagramm.AddGraph(graph.Clone(newId));
            }
            return newDiagramm;
        }
        /// <summary>
        /// stabdard Konstruktor
        /// </summary>
        public RiZDiagramm()
        {
            InitRiZDiagramm("");
        }

        /// <summary>
        /// Updatet das SphinxSymbol in der übergebenen Zeichnung
        /// </summary>
        /// <param name="ID">Nummer (ID) der Kurve im Diagramm</param>
        /// <param name="Name">Name der Kurve im Diagramm</param>
        
        public RiZDiagramm(string Name)
        {
               InitRiZDiagramm(Name);
        }

        public RiZDiagramm(int ID, string Name)
        {
               InitRiZDiagramm(Name);
        }

        public void InitRiZDiagramm(string Name)
        {
            ID = Guid.NewGuid();
            this.Name = Name;
            xAchsenbeschriftung = "Uhrzeit [t]";
            Graphen = new List<RiZGraph>();
            CursorColor = Colors.Red;
        }

        /// <summary>
        /// Liefert die Kurve (den Graphen) aus einem Diagramm, der die übergeben VariablenID anzeigt
        /// </summary>
        /// <param name="variable">Variablen ID die gesucht wird</param>
        public RiZGraph GetGraphic(string variable)
        {
            foreach (RiZGraph g in Graphen)
            {
                // in allen Graphen (Kurven die Variable suchen
                if (String.Compare(variable, g.Variable.ToString(), true) == 0) return g;
            }
            return null;
        }
    }

    /// <summary>
    /// Repräsentiert eine einzlene Kurve (Graph) im Diagramm
    /// </summary>
    public class RiZGraph
    {

        public Guid ID;
        /// <summary>
        /// optionale Beschreibung
        /// </summary>
        public string Decription = "";
        /// <summary>
        /// Componente des Treeviews, aus dem die Variable kommt
        /// </summary>
        public uint Componente = 0;
        /// <summary>
        /// Variablen ID die dargestellt werden soll
        /// </summary>
        public uint Variable = 0;
        /// <summary>
        /// Y-Achenbegrenzung nach unten (minimum)
        /// </summary>
        public double MinY = 0.0;
        /// <summary>
        /// Y-Achenbegrenzung nach oben (maximum)
        /// </summary>
        public double MaxY = 10.0;
        /// <summary>
        /// Faktor mit dem der Variablemwert vor der Anzeige multipliziert wird
        /// </summary>
        public double faktor = 1.0;
        /// <summary>
        /// Faktor mit dem der Variablemwert vor der Anzeige multipliziert wird
        /// </summary>
        /// /// <summary>
        /// Die SI Einheit in der die Variablenwerte angezeigt werden (y-Achsebeschriftung)
        /// </summary>
        public string Unit = "";
        /// /// <summary>
        /// Die ID der jeweiligen Y-Achse, um mehrere Y-Achsen zu generieren
        /// </summary>
        public string YAchsenID = "";
        /// /// <summary>
        /// Die ID der jeweiligen Y-Achse, um mehrere Y-Achsen zu generieren
        /// </summary>
        public string YAchsenIDintern = "";
        /// /// <summary>
        /// Beschriftung der jeweiligen Y-Achse
        /// </summary>
        public string YAxisText = "";
        /// /// <summary>
        /// Stringformat der Legendenwerte
        /// </summary>
        public string format = "";

        public VariableType ValueType = VariableType.Float;
        private Color m_Graphcolor = Colors.Black;
        /// /// <summary>
        /// Farbe der Kurve im Diagram
        /// </summary>
        public Color Graphcolor
        {
            get
            {
                return m_Graphcolor;
            }
            set
            {
                m_Graphcolor = value;
            }
        }
        /*
        [XmlElement("Graphcolor")]
        public string GraphcolorHtml
        {
            get
            {
                return
                    ColorTranslator.ToHtml(m_Graphcolor);
            }
            set
            {
                m_Graphcolor = ColorTranslator.FromHtml(value);
            }
        }
        */
        public RiZGraph() 
        {
            IntRiZGraph("New Graph", 0, 0, 1.0, 0, 0, "KW", "0", "Power", Colors.Blue, "{0,10:0,0.00}");
        }
        public RiZGraph(uint Componente , string Decription, uint Variable, double faktor, double MinY, double MaxY, string Unit, string YAchsenID, string YAxisText,
            System.Drawing.Color color, string strValFormat, VariableType type)
        {
            IntRiZGraph(Decription, Componente, Variable, faktor, MinY, MaxY, Unit, YAchsenID, YAxisText, Color.FromRgb(color.R, color.B, color.G), strValFormat);
        }
        public RiZGraph(string Decription, uint Variable, double faktor, double MinY, double MaxY, string Unit, string YAchsenID, string YAxisText,
            System.Drawing.Color color, string strValFormat, VariableType type)
        {
            IntRiZGraph(Decription, 0, Variable, faktor, MinY, MaxY, Unit, YAchsenID, YAxisText, Color.FromRgb(color.R, color.B, color.G), strValFormat);
        }

        public RiZGraph(string Decription, uint Componente, uint Variable, double faktor, double MinY, double MaxY, string Unit, string YAchsenID, string YAxisText,
            Color color, string strValFormat)
        {
            IntRiZGraph(Decription, Componente, Variable, faktor, MinY, MaxY, Unit, YAchsenID, YAxisText, color, strValFormat);
        }

        private void IntRiZGraph(string Decription, uint Componente, uint Variable, double faktor, double MinY, double MaxY, string Unit, string YAchsenID, string YAxisText,
            Color color, string strValFormat )
        {
            this.ID = Guid.NewGuid();
            this.Decription = Decription;
            this.Componente = Componente;
            this.Variable = Variable;
            this.MinY = MinY;
            this.MaxY = MaxY;
            this.Unit = Unit;
            this.faktor = faktor;
            this.YAxisText = YAxisText;
            this.Graphcolor = color;
            this.YAchsenID = YAchsenID;
            this.YAchsenIDintern = Unit + YAchsenID;
            this.format = strValFormat;
            this.ValueType = VariableType.AnalogInt;

            if (this.format.Length == 0) this.format = "{0,10:0,0.00}";
        }

        public RiZGraph Clone(bool newId)
        {
            RiZGraph gr = new RiZGraph();
            if (!newId) gr.ID = ID;
            gr.Decription = Decription;
            gr.Componente = Componente;
            gr.Variable = Variable;
            gr.MinY = MinY;
            gr.MaxY = MaxY;
            gr.Unit = Unit;
            gr.faktor = faktor;
            gr.YAxisText = YAxisText;
            gr.Graphcolor = Graphcolor;
            gr.YAchsenID = YAchsenID;
            gr.YAchsenIDintern = YAchsenIDintern;
            gr.ValueType = ValueType;
            gr.format=this.format;
            return gr;
        }

    }

}

