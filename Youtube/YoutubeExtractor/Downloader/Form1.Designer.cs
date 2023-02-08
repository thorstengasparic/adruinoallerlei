namespace Downloader
{
    partial class Form1
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

        #region Vom Windows Form-Designer generierter Code

        /// <summary>
        /// Erforderliche Methode für die Designerunterstützung.
        /// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
        /// </summary>
        private void InitializeComponent()
        {
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.listBoxDownloads = new System.Windows.Forms.ListBox();
            this.buttonDelete = new System.Windows.Forms.Button();
            this.buttonAddUrl = new System.Windows.Forms.Button();
            this.textBoxNewURL = new System.Windows.Forms.TextBox();
            this.labelURL = new System.Windows.Forms.Label();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.checkBoxAutostartDownload = new System.Windows.Forms.CheckBox();
            this.checkBoxCheckClipboard = new System.Windows.Forms.CheckBox();
            this.textBoxPfad = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.checkBoxExtractMP3 = new System.Windows.Forms.CheckBox();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(723, 451);
            this.tabControl1.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.splitContainer1);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(715, 425);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Download";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(3, 3);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.listBoxDownloads);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.buttonDelete);
            this.splitContainer1.Panel2.Controls.Add(this.buttonAddUrl);
            this.splitContainer1.Panel2.Controls.Add(this.textBoxNewURL);
            this.splitContainer1.Panel2.Controls.Add(this.labelURL);
            this.splitContainer1.Size = new System.Drawing.Size(709, 419);
            this.splitContainer1.SplitterDistance = 291;
            this.splitContainer1.TabIndex = 0;
            // 
            // listBoxDownloads
            // 
            this.listBoxDownloads.Dock = System.Windows.Forms.DockStyle.Fill;
            this.listBoxDownloads.FormattingEnabled = true;
            this.listBoxDownloads.Location = new System.Drawing.Point(0, 0);
            this.listBoxDownloads.Name = "listBoxDownloads";
            this.listBoxDownloads.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended;
            this.listBoxDownloads.Size = new System.Drawing.Size(709, 291);
            this.listBoxDownloads.TabIndex = 0;
            this.listBoxDownloads.SelectedIndexChanged += new System.EventHandler(this.listBoxDownloads_SelectedIndexChanged);
            // 
            // buttonDelete
            // 
            this.buttonDelete.Location = new System.Drawing.Point(598, 36);
            this.buttonDelete.Name = "buttonDelete";
            this.buttonDelete.Size = new System.Drawing.Size(75, 23);
            this.buttonDelete.TabIndex = 3;
            this.buttonDelete.Text = "Löschen";
            this.buttonDelete.UseVisualStyleBackColor = true;
            this.buttonDelete.Click += new System.EventHandler(this.buttonDelete_Click);
            // 
            // buttonAddUrl
            // 
            this.buttonAddUrl.Location = new System.Drawing.Point(598, 7);
            this.buttonAddUrl.Name = "buttonAddUrl";
            this.buttonAddUrl.Size = new System.Drawing.Size(75, 23);
            this.buttonAddUrl.TabIndex = 2;
            this.buttonAddUrl.Text = "Hinzufügen";
            this.buttonAddUrl.UseVisualStyleBackColor = true;
            this.buttonAddUrl.Click += new System.EventHandler(this.buttonAddUrl_Click);
            // 
            // textBoxNewURL
            // 
            this.textBoxNewURL.Location = new System.Drawing.Point(54, 9);
            this.textBoxNewURL.Name = "textBoxNewURL";
            this.textBoxNewURL.Size = new System.Drawing.Size(538, 20);
            this.textBoxNewURL.TabIndex = 1;
            // 
            // labelURL
            // 
            this.labelURL.AutoSize = true;
            this.labelURL.Location = new System.Drawing.Point(19, 12);
            this.labelURL.Name = "labelURL";
            this.labelURL.Size = new System.Drawing.Size(29, 13);
            this.labelURL.TabIndex = 0;
            this.labelURL.Text = "URL";
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.checkBoxExtractMP3);
            this.tabPage2.Controls.Add(this.checkBoxAutostartDownload);
            this.tabPage2.Controls.Add(this.checkBoxCheckClipboard);
            this.tabPage2.Controls.Add(this.textBoxPfad);
            this.tabPage2.Controls.Add(this.label1);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(715, 425);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Einstellungen";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // checkBoxAutostartDownload
            // 
            this.checkBoxAutostartDownload.AutoSize = true;
            this.checkBoxAutostartDownload.Location = new System.Drawing.Point(63, 94);
            this.checkBoxAutostartDownload.Name = "checkBoxAutostartDownload";
            this.checkBoxAutostartDownload.Size = new System.Drawing.Size(138, 17);
            this.checkBoxAutostartDownload.TabIndex = 6;
            this.checkBoxAutostartDownload.Text = "Download sofort starten";
            this.checkBoxAutostartDownload.UseVisualStyleBackColor = true;
            this.checkBoxAutostartDownload.CheckedChanged += new System.EventHandler(this.checkBoxAutostartDownload_CheckedChanged);
            // 
            // checkBoxCheckClipboard
            // 
            this.checkBoxCheckClipboard.AutoSize = true;
            this.checkBoxCheckClipboard.Location = new System.Drawing.Point(63, 71);
            this.checkBoxCheckClipboard.Name = "checkBoxCheckClipboard";
            this.checkBoxCheckClipboard.Size = new System.Drawing.Size(132, 17);
            this.checkBoxCheckClipboard.TabIndex = 5;
            this.checkBoxCheckClipboard.Text = "Clipboard überwachen";
            this.checkBoxCheckClipboard.UseVisualStyleBackColor = true;
            this.checkBoxCheckClipboard.CheckedChanged += new System.EventHandler(this.checkBoxCheckClipboard_CheckedChanged);
            // 
            // textBoxPfad
            // 
            this.textBoxPfad.Location = new System.Drawing.Point(63, 28);
            this.textBoxPfad.Name = "textBoxPfad";
            this.textBoxPfad.Size = new System.Drawing.Size(350, 20);
            this.textBoxPfad.TabIndex = 1;
            this.textBoxPfad.TextChanged += new System.EventHandler(this.textBoxPfad_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(28, 31);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Pfad";
            // 
            // checkBoxExtractMP3
            // 
            this.checkBoxExtractMP3.AutoSize = true;
            this.checkBoxExtractMP3.Location = new System.Drawing.Point(63, 117);
            this.checkBoxExtractMP3.Name = "checkBoxExtractMP3";
            this.checkBoxExtractMP3.Size = new System.Drawing.Size(84, 17);
            this.checkBoxExtractMP3.TabIndex = 7;
            this.checkBoxExtractMP3.Text = "Extract MP3";
            this.checkBoxExtractMP3.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(723, 451);
            this.Controls.Add(this.tabControl1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.ListBox listBoxDownloads;
        private System.Windows.Forms.Button buttonAddUrl;
        private System.Windows.Forms.TextBox textBoxNewURL;
        private System.Windows.Forms.Label labelURL;
        private System.Windows.Forms.CheckBox checkBoxAutostartDownload;
        private System.Windows.Forms.CheckBox checkBoxCheckClipboard;
        private System.Windows.Forms.TextBox textBoxPfad;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button buttonDelete;
        private System.Windows.Forms.CheckBox checkBoxExtractMP3;
    }
}

