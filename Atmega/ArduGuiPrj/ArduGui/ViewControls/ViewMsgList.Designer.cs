namespace ArduGui.ViewControls
{
    partial class ViewMsgList 
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
            this.m_lb = new System.Windows.Forms.ListBox();
            this.checkBoxRawmode = new System.Windows.Forms.CheckBox();
            this.button2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.m_tb = new System.Windows.Forms.TextBox();
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.m_lb);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.checkBoxRawmode);
            this.splitContainer1.Panel2.Controls.Add(this.button2);
            this.splitContainer1.Panel2.Controls.Add(this.button1);
            this.splitContainer1.Panel2.Controls.Add(this.m_tb);
            this.splitContainer1.Size = new System.Drawing.Size(493, 409);
            this.splitContainer1.SplitterDistance = 352;
            this.splitContainer1.TabIndex = 0;
            // 
            // m_lb
            // 
            this.m_lb.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_lb.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_lb.FormattingEnabled = true;
            this.m_lb.ItemHeight = 14;
            this.m_lb.Location = new System.Drawing.Point(0, 0);
            this.m_lb.Name = "m_lb";
            this.m_lb.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended;
            this.m_lb.Size = new System.Drawing.Size(493, 340);
            this.m_lb.TabIndex = 5;
            // 
            // checkBoxRawmode
            // 
            this.checkBoxRawmode.AutoSize = true;
            this.checkBoxRawmode.Location = new System.Drawing.Point(165, 6);
            this.checkBoxRawmode.Name = "checkBoxRawmode";
            this.checkBoxRawmode.Size = new System.Drawing.Size(74, 17);
            this.checkBoxRawmode.TabIndex = 10;
            this.checkBoxRawmode.Text = "Rawmode";
            this.toolTip1.SetToolTip(this.checkBoxRawmode, "Show alle Messages or only Textmessages");
            this.checkBoxRawmode.UseVisualStyleBackColor = true;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(83, 3);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(76, 20);
            this.button2.TabIndex = 9;
            this.button2.Text = "To Last Line";
            this.toolTip1.SetToolTip(this.button2, "Jump to last Line in Listview");
            this.button2.UseVisualStyleBackColor = true;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(3, 3);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(76, 20);
            this.button1.TabIndex = 8;
            this.button1.Text = "Clear";
            this.toolTip1.SetToolTip(this.button1, "Clear Listview");
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // m_tb
            // 
            this.m_tb.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.m_tb.Font = new System.Drawing.Font("Courier New", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_tb.Location = new System.Drawing.Point(0, 27);
            this.m_tb.Name = "m_tb";
            this.m_tb.Size = new System.Drawing.Size(493, 26);
            this.m_tb.TabIndex = 6;
            this.m_tb.Text = "text";
            this.m_tb.KeyUp += new System.Windows.Forms.KeyEventHandler(this.m_tb_KeyUp);
            // 
            // ViewMsgList
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Controls.Add(this.splitContainer1);
            this.Name = "ViewMsgList";
            this.Size = new System.Drawing.Size(493, 409);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.Panel2.PerformLayout();
            this.splitContainer1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.ListBox m_lb;
        private System.Windows.Forms.TextBox m_tb;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.CheckBox checkBoxRawmode;
        private System.Windows.Forms.ToolTip toolTip1;

    }
}
