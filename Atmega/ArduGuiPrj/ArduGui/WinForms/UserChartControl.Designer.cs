namespace ArdoGui.ViewControls
{
    partial class UserChartControl
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

        #region Vom Komponenten-Designer generierter Code

        /// <summary> 
        /// Erforderliche Methode für die Designerunterstützung. 
        /// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.chartControlWinForm1 = new ArduGui.View.ChartControlWinForm();
            this.buttonTag = new System.Windows.Forms.Button();
            this.buttonStunde = new System.Windows.Forms.Button();
            this.buttonMonat = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.chartControlWinForm1);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.buttonTag);
            this.splitContainer1.Panel2.Controls.Add(this.buttonStunde);
            this.splitContainer1.Panel2.Controls.Add(this.buttonMonat);
            this.splitContainer1.Size = new System.Drawing.Size(541, 339);
            this.splitContainer1.SplitterDistance = 283;
            this.splitContainer1.TabIndex = 0;
            // 
            // chartControlWinForm1
            // 
            this.chartControlWinForm1.BackColor = System.Drawing.SystemColors.ControlText;
            this.chartControlWinForm1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.chartControlWinForm1.Location = new System.Drawing.Point(0, 0);
            this.chartControlWinForm1.Name = "chartControlWinForm1";
            this.chartControlWinForm1.Size = new System.Drawing.Size(541, 283);
            this.chartControlWinForm1.TabIndex = 0;
            // 
            // buttonTag
            // 
            this.buttonTag.Location = new System.Drawing.Point(85, 2);
            this.buttonTag.Name = "buttonTag";
            this.buttonTag.Size = new System.Drawing.Size(76, 24);
            this.buttonTag.TabIndex = 2;
            this.buttonTag.Text = "Tag";
            this.buttonTag.UseVisualStyleBackColor = true;
            this.buttonTag.Click += new System.EventHandler(this.buttonTag_Click);
            // 
            // buttonStunde
            // 
            this.buttonStunde.Location = new System.Drawing.Point(167, 3);
            this.buttonStunde.Name = "buttonStunde";
            this.buttonStunde.Size = new System.Drawing.Size(76, 24);
            this.buttonStunde.TabIndex = 1;
            this.buttonStunde.Text = "Stunde";
            this.buttonStunde.UseVisualStyleBackColor = true;
            this.buttonStunde.Click += new System.EventHandler(this.buttonStunde_Click);
            // 
            // buttonMonat
            // 
            this.buttonMonat.Location = new System.Drawing.Point(3, 3);
            this.buttonMonat.Name = "buttonMonat";
            this.buttonMonat.Size = new System.Drawing.Size(76, 24);
            this.buttonMonat.TabIndex = 0;
            this.buttonMonat.Text = "Monat";
            this.buttonMonat.UseVisualStyleBackColor = true;
            this.buttonMonat.Click += new System.EventHandler(this.buttonMonat_Click);
            // 
            // UserChartControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.splitContainer1);
            this.Name = "UserChartControl";
            this.Size = new System.Drawing.Size(541, 339);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private ArduGui.View.ChartControlWinForm chartControlWinForm1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button buttonTag;
        private System.Windows.Forms.Button buttonStunde;
        private System.Windows.Forms.Button buttonMonat;
    }
}
