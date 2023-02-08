using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ArduGui.View;
using System.Threading;
using ArduGui.Model;

namespace ArdoGui.ViewControls
{
    public partial class UserChartControl : ArduGui.View.BaseViewControl
    {
        /// <summary>Aktuelle Zeit des ChartCursors</summary>    
        private DateTime cursorTime;
        /// <summary>StartZeit der Darstellung</summary>    
        DateTime startTime;
        /// <summary>EndeZeit der Darstellung</summary>    
        DateTime endTime;
        /// <summary>Steuert, ob die CursorZeit automatisch aktuallisiert wird</summary>    
        bool AutoCursorTime = true;
        /// <summary>der Timer, der die CursorZeit automatisch aktuallisiert</summary>    

        /// <summary>Für jede Variable wird eine Liste mit den Rohdaten gespeichert und verwaltet</summary>    
        IDictionary<uint, List<Value>> graphVars = null;
        /// <summary>Für jede Variable wird eine Liste mit den Werten zur Darstellung gespeichert und verwaltet, diese wird aus graphVars erstellt</summary>    
        IDictionary<uint, RiZGraphData> graphDataList = null;
        
        
        public UserChartControl()
        {
            InitializeComponent();
            graphVars = new Dictionary<uint, List<Value>>();

            graphDataList = new Dictionary<uint, RiZGraphData>();
            chartControlWinForm1.SetGraphData(ref graphDataList);
            chartControlWinForm1.OnDateTimeChaned += SetTime;
            
            AutoCursorTime = true;

            timer1.Interval = 5000;
            timer1.Tick += new EventHandler(dt_Tick);
            timer1.Enabled = false;
        }
        
        public void SetChartConfiguration(ChartConfiguration chart)
        {
            lock (graphDataList)
            {
                // alte Daten löschen
                graphVars.Clear();
                graphDataList.Clear();
            }
            chartControlWinForm1.SetChartConfiguration(chart);

            cursorTime = DateTime.Now;
            startTime = DateTime.Now.AddMinutes(-1);
            endTime = DateTime.Now.AddMinutes(60*1);

            chartControlWinForm1.SetTime(startTime, endTime, cursorTime);
        }

        public ChartConfiguration GetChartConfiguration()
        {
            return chartControlWinForm1.GetChartConfiguration();
        }
        /// <summary>Speichert die Werte zur ID in einer ValuesArrayListe</summary>
        /// <param name="id">Id der Komponente zu der die Daten gehören</param>
        /// <param name="values">Array von Daten zur Anzeige</param>
        public void GraphValues(uint id, Value[] values)
        {
            if (values == null) return;
            lock (graphDataList)
            {
                graphVars.Remove(id);
                graphVars.Add(id, values.ToList());
            }
        }

        /// <summary>Errechnet aus der graphVars Liste eine Liste von Werten, die von dem Chart dargestellt werden kann</summary>
        /// <param name="id">Id der Komponente zu der die Daten gehören</param>
        /// <param name="tLeft">AnfangsZeitpunkt für die Berechnung</param>
        /// <param name="tRight">EndeZeitpunkt für die Berechnung</param>
        bool ValueArrayToGraphData(uint id, DateTime tLeft, DateTime tRight)
        {
            lock (graphDataList)
            {
                //if (graphDataList.ContainsKey(id)) return true;

                //alte Werte löschen und mit den neuen initalisieren
                graphDataList.Remove(id);
                if (graphVars == null) return true;
                List<Value> values = null;
                try
                {
                    values = graphVars[id];
                }
                catch
                {   // ID nicht bekannt
                    return false;
                }
                if (values == null) return true; // ID nicht bekannt
                if (values.Count < 2) return true; // keine Daten

                List<double> X = new List<double>();
                List<double> Y = new List<double>();
                try
                {
                    // Values umkopieren: Werte in Y, Timestamp in X
                    for (int i = 0; i < values.Count; i++)
                    {
                        if ((i + 1) < values.Count)
                        {
                            if (values[i + 1].Timestamp < tLeft)
                            {
                                // Value liegt VOR dem angefordertem Zeitintervall, ignorieren
                                continue;
                            }
                        }
                        if (tRight.Ticks != 0)
                        {
                            if (values[i].Timestamp > tRight)
                            {
                                // Value liegt NACH dem angefordertem Zeitintervall, ignorieren
                                continue;
                            }
                        }
                        if (values[i].Val.Equals("-"))
                        {
                            // Value = "-" nach 0.0 mappen
                            X.Add((new ZedGraph.XDate(values[i].Timestamp)).XLDate);
                            Y.Add(0.0);
                        }
                        else
                        {
                            X.Add((new ZedGraph.XDate(values[i].Timestamp)).XLDate);
                            //Y.Add(Convert.ToDouble(values[i].Val));
                            Y.Add(values[i].Val);
                        }
                    }
                }
                catch { }
                if (Y.Count == 0) return true; // leere Liste

                // Die linke Intervallgrenze auf den letzten Wert setzen
                // Dient der optische Anpassung des Chart, falls hier durch nicht synchone 
                // Uhren ein Lücke sein sollte.
                if (tRight.Ticks != 0)
                {
                    double LastVal = Y[Y.Count - 1];
                    X.Add((new ZedGraph.XDate(tRight)).XLDate);
                    Y.Add(LastVal);
                }

                // das neue Object in die Liste zur Darstellung hängen
                RiZGraphData gData = new RiZGraphData(id.ToString(), "");
                gData.X = X.ToArray();
                gData.Y = Y.ToArray();
                graphDataList.Add(id, gData);
            }

            return true;
        }
        public void FillDummyData()
        {
            chartControlWinForm1.FillDummyData();
        }
        /// <summary>Fügt der VariablenListe (Rohdaten) einen Wert hinzu, falls die Variable im Chart angezeigt wird</summary>
        /// <param name="id">Id der Komponente zu der die Daten gehören</param>
        /// <param name="val">Neuer Wert</param>
        public bool VariableChanged(uint id, Value val)
        {
            if (chartControlWinForm1 == null) return false;
            if (chartControlWinForm1.GetChartConfiguration() == null) return false;
            if (!chartControlWinForm1.GetChartConfiguration().Configuration.GetVariables().ContainsKey(id)) return false;
            try
            {
                lock (graphDataList)
                {
                    if (!graphVars.Keys.Contains(id))
                        graphVars.Add(id, new List<Value>());
                    List<Value> vals = graphVars[id];
                    vals.Add(val);
                }
            }
            catch
            {
                return false;
            }
            return true;
        }

        /// <summary>Berrechnet für alle VariablenListen die Darstellungsdaten vom DarstellungsStartZeitpunkt bis zum aktuellen Zeitpunkt. Dadurch werden Punkte die in der Zukunft liegen (nicht synchrone Uhren!!) nicht dargestellt. Die Chart werden neu gezeichnet</summary>
        public void UpdateAllData()
        {
            DateTime from = startTime;
            //DateTime to = DateTimeHelper.ToRaster(DateTime.Now, 10);
            DateTime to = new DateTime();
            if (chartControlWinForm1.GetChartConfiguration() == null) return;
            foreach (KeyValuePair<uint, VariableType> kvp in chartControlWinForm1.GetChartConfiguration().Configuration.GetVariables())
            {
                ValueArrayToGraphData(kvp.Key, from, to);
            }
            chartControlWinForm1.ReDrawGraph();
        }
        /// <summary>Setzt das Anzeigeintervall um die neue CursorTime. Die Dauer des angezeigten Intervall wird durch skal festgelegt</summary>
        /// <param name="ncursorTime">Die neue Zeit des Cursors</param>
        /// <param name="skal">Gibt den Zeitraum um die neuen Cursozeit vor, skal.frei übernimmt die aktuelle Intervaldauer und berechnet nur Start und Ende</param>
        public void SetTime(DateTime ncursorTime, Skalierung skal)
        {
            cursorTime = new DateTime(ncursorTime.Ticks); // setze Cursor
            //SetDateTimePickerDate(cursorTime);
            //dtP.Value = new DateTime(cursorTime.Ticks); // setze DateTime Picker
            chartControlWinForm1.DarstellungsIntervall(skal);
        }
        /// <summary>Setzt das Anzeigeintervall um die neue CursorTime. Start und End ewird vorgegeben</summary>
        /// <param name="ncursorTime">Die neue Zeit des Cursors</param>
        public void SetTime(DateTime nstartTime, DateTime nendTime, DateTime ncursorTime)
        {
            SetTime(nstartTime, nendTime, ncursorTime, false);
        }
        public void ReloadData()
        {
            bool oldAutoCursorTime = AutoCursorTime;
            SetTime(startTime, endTime, cursorTime, true);
            AutoCursorTime = oldAutoCursorTime;
        }
        public void SetTime(DateTime nstartTime, DateTime nendTime, DateTime ncursorTime, bool ForceLoadData)
        {
            AutoCursorTime = false;
            cursorTime = new DateTime(ncursorTime.Ticks);
            if (((this.startTime.Ticks - nstartTime.Ticks) != 0) || ((this.endTime.Ticks - nendTime.Ticks) != 0) || ForceLoadData)
            {
                // wenn sich das Anzeige intervall geändert hat, daten nachladen
                this.startTime = nstartTime;
                this.endTime = nendTime;
                LoadData();
            }

            //SetDateTimePickerDate(cursorTime);
            if (chartControlWinForm1.GetChartConfiguration() != null)
                //SetLegend(cursorTime, chartControlWinForm1.GetChartConfiguration().Configuration.Interpoliert);
            chartControlWinForm1.SetTime(startTime, endTime, cursorTime);
        }
        /// <summary>Fordert DAten aus dem Kern an</summary>
        void LoadData()
        {
            if (chartControlWinForm1.GetChartConfiguration() != null)
            {
                this.Cursor = Cursors.WaitCursor;
                chartControlWinForm1.SetCursor(System.Windows.Forms.Cursors.WaitCursor);
                foreach (int id in chartControlWinForm1.GetChartConfiguration().Configuration.GetVariables().Keys)
                {
                    Value[] val = LoadDBData(id, this.startTime, this.endTime, false);
                    lock (graphDataList)
                    {
                        if (graphVars.Keys.Contains((uint)id))
                        {
                            graphVars.Remove((uint)id);
                            graphVars.Add((uint)id, val.ToList());
                        }
                    }
                }
                this.Cursor = Cursors.Arrow;
                chartControlWinForm1.SetCursor(System.Windows.Forms.Cursors.Arrow);
            }
        }
        /// <summary>Zeigt 15 Minuten um die aktuelle Uhrzeit an und startet den AutoUpdateTimer</summary>
        public void btnReset_Click(object sender, EventArgs e)
        {
            bool LastTimerState = timer1.Enabled;
            timer1.Enabled = false;

            DateTime ncursorTime = DateTimeHelper.ToRaster(DateTime.Now, 10);
            DateTime nstartTime = ncursorTime.AddMinutes(-10);
            DateTime nendTime = ncursorTime.AddMinutes(5);
            SetTime(nstartTime, nendTime, ncursorTime, false);
            chartControlWinForm1.SetTime(cursorTime);
            chartControlWinForm1.DarstellungsIntervall(Skalierung.Free);
            UpdateAllData();
            AutoCursorTime = true;
            timer1.Enabled = true;
        }

        private void SelectIntervall(Skalierung intervall)
        {
            bool LastTimerState = timer1.Enabled;
            timer1.Enabled = false;
            chartControlWinForm1.DarstellungsIntervall(intervall);
            ReloadData();
            UpdateAllData();
            timer1.Enabled = LastTimerState;
        }

        private void btnWoche_Click(object sender, EventArgs e)
        {
            SelectIntervall(Skalierung.Week);
        }

        private void btnTag_Click(object sender, EventArgs e)
        {
            SelectIntervall(Skalierung.Day);
        }

        private void btnStunde_Click(object sender, EventArgs e)
        {
            SelectIntervall(Skalierung.Hour);
        }

        private void btnMonat_Click(object sender, EventArgs e)
        {
            SelectIntervall(Skalierung.Month);
        }

        private void btnJahr_Click(object sender, EventArgs e)
        {
            SelectIntervall(Skalierung.Year);
        }


        /// <summary>Timer für AutoUpdate</summary>
        void dt_Tick(object sender, EventArgs e)
        {
            lock (graphDataList)
            {
                if (AutoCursorTime)
                {
                    // Cursor auf aktuelle Uhrzeit setzen
                    cursorTime = DateTimeHelper.ToRaster(DateTime.Now, 10);
                    //dtP.Value = new DateTime(cursorTime.Ticks);
                    //SetDateTimePickerDate(cursorTime);
                    if (cursorTime.Ticks > endTime.Ticks) // bei einem Überlauf einen Reset auslösen
                        btnReset_Click(null, null);
                    chartControlWinForm1.SetTime(cursorTime);
                    AutoCursorTime = true;
                }
                //SetLegend(cursorTime, chartControlWinForm1.GetChartConfiguration().Configuration.Interpoliert);
                UpdateAllData();
            }
        }

        public override bool NotifyChanges(MessageItem message) 
        {
            lock (graphDataList)
            {
                if (message.Type != MessageType.Variable) return false;
                if (ValueCommand.GetCommandType(message.Content) != ValueCommandType.Float) return false;

                string VarId;
                double content;
                ValueCommand.ExtractDouble(message.Content, out VarId, out content);
                Value val = new Value(content, message.Timestamp);
                VariableChanged(Convert.ToUInt32(VarId), val);
                UpdateAllData();
                return true;
            }
        }

        private void buttonMonat_Click(object sender, EventArgs e)
        {
            SelectIntervall(Skalierung.Month);
        }

        private void buttonTag_Click(object sender, EventArgs e)
        {
            SelectIntervall(Skalierung.Day);
        }

        private void buttonStunde_Click(object sender, EventArgs e)
        {
            SelectIntervall(Skalierung.Hour);
        }
    }
}
