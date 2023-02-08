using ZedGraph;
using System.Drawing;

namespace ArduGui.View
{
    partial class ChartControlWinForm
    {
        /// <summary>
        /// Erforderliche Designervariable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Verwendete Ressourcen bereinigen.
        /// </summary>
        /// <param name="disposing">True, wenn verwaltete Ressourcen gelöscht werden sollen; andernfalls False.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }
        private void InitializeZedControls()
        {
            
            
            this.components = new System.ComponentModel.Container();
            this.Controls.Clear();

            zcontrols = new RiZedGraphControlBase[4];
            for (int i = 0; i < 4; i++)
            {
                RiZedGraphControlBase zcontrol = ZedControlFactory.Create(RiZChartType.Pie);
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
        #region Vom Komponenten-Designer generierter Code

        /// <summary>
        /// Erforderliche Methode für die Designerunterstützung. 
        /// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
        /// </summary>
        private void InitializeComponent()
        {
            this.SuspendLayout();
            // 
            // ChartControlWinForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlText;
            this.Name = "ChartControlWinForm";
            this.Size = new System.Drawing.Size(448, 333);
            this.Resize += new System.EventHandler(this.DataView_Resize);
            this.ResumeLayout(false);

        }

        #endregion

    }
}
