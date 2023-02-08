namespace ArduGui
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.loadToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.optionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.serialSettingsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.toolStripButton1 = new System.Windows.Forms.ToolStripButton();
            this.tabControlViews = new System.Windows.Forms.TabControl();
            this.tabPageVarView = new System.Windows.Forms.TabPage();
            this.splitContainer3 = new System.Windows.Forms.SplitContainer();
            this.splitContainer4 = new System.Windows.Forms.SplitContainer();
            this.viewSlider9 = new ArdoGui.ViewControls.ViewSlider();
            this.viewSlider8 = new ArdoGui.ViewControls.ViewSlider();
            this.viewSlider7 = new ArdoGui.ViewControls.ViewSlider();
            this.viewSlider6 = new ArdoGui.ViewControls.ViewSlider();
            this.viewSlider5 = new ArdoGui.ViewControls.ViewSlider();
            this.viewSlider4 = new ArdoGui.ViewControls.ViewSlider();
            this.viewSlider3 = new ArdoGui.ViewControls.ViewSlider();
            this.viewSlider2 = new ArdoGui.ViewControls.ViewSlider();
            this.viewSlider1 = new ArdoGui.ViewControls.ViewSlider();
            this.viewMsgListVar = new ArduGui.ViewControls.ViewMsgList();
            this.splitContainer5 = new System.Windows.Forms.SplitContainer();
            this.viewTextBox12 = new ArdoGui.ViewControls.ViewTextBox();
            this.viewTextBox11 = new ArdoGui.ViewControls.ViewTextBox();
            this.viewTextBox10 = new ArdoGui.ViewControls.ViewTextBox();
            this.viewTextBox9 = new ArdoGui.ViewControls.ViewTextBox();
            this.viewTextBox8 = new ArdoGui.ViewControls.ViewTextBox();
            this.viewTextBox7 = new ArdoGui.ViewControls.ViewTextBox();
            this.viewTextBox6 = new ArdoGui.ViewControls.ViewTextBox();
            this.viewTextBox5 = new ArdoGui.ViewControls.ViewTextBox();
            this.viewTextBox4 = new ArdoGui.ViewControls.ViewTextBox();
            this.viewTextBox3 = new ArdoGui.ViewControls.ViewTextBox();
            this.viewTextBox2 = new ArdoGui.ViewControls.ViewTextBox();
            this.viewTextBox1 = new ArdoGui.ViewControls.ViewTextBox();
            this.userChartControl1 = new ArdoGui.ViewControls.UserChartControl();
            this.tabPageRawView = new System.Windows.Forms.TabPage();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.menuStrip1.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.tabControlViews.SuspendLayout();
            this.tabPageVarView.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer3)).BeginInit();
            this.splitContainer3.Panel1.SuspendLayout();
            this.splitContainer3.Panel2.SuspendLayout();
            this.splitContainer3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer4)).BeginInit();
            this.splitContainer4.Panel1.SuspendLayout();
            this.splitContainer4.Panel2.SuspendLayout();
            this.splitContainer4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer5)).BeginInit();
            this.splitContainer5.Panel1.SuspendLayout();
            this.splitContainer5.Panel2.SuspendLayout();
            this.splitContainer5.SuspendLayout();
            this.tabPageRawView.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem1,
            this.optionToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1130, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.loadToolStripMenuItem,
            this.saveToolStripMenuItem});
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(37, 20);
            this.toolStripMenuItem1.Text = "File";
            // 
            // loadToolStripMenuItem
            // 
            this.loadToolStripMenuItem.Name = "loadToolStripMenuItem";
            this.loadToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.loadToolStripMenuItem.Text = "Load";
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.saveToolStripMenuItem.Text = "Save";
            // 
            // optionToolStripMenuItem
            // 
            this.optionToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.serialSettingsToolStripMenuItem});
            this.optionToolStripMenuItem.Name = "optionToolStripMenuItem";
            this.optionToolStripMenuItem.Size = new System.Drawing.Size(56, 20);
            this.optionToolStripMenuItem.Text = "Option";
            // 
            // serialSettingsToolStripMenuItem
            // 
            this.serialSettingsToolStripMenuItem.Name = "serialSettingsToolStripMenuItem";
            this.serialSettingsToolStripMenuItem.Size = new System.Drawing.Size(144, 22);
            this.serialSettingsToolStripMenuItem.Text = "SerialSettings";
            this.serialSettingsToolStripMenuItem.Click += new System.EventHandler(this.serialSettingsToolStripMenuItem_Click);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Location = new System.Drawing.Point(0, 675);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(1130, 22);
            this.statusStrip1.TabIndex = 1;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton1});
            this.toolStrip1.Location = new System.Drawing.Point(0, 24);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(1130, 25);
            this.toolStrip1.TabIndex = 2;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // toolStripButton1
            // 
            this.toolStripButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton1.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton1.Image")));
            this.toolStripButton1.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton1.Name = "toolStripButton1";
            this.toolStripButton1.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton1.Text = "toolStripButton1";
            this.toolStripButton1.ToolTipText = "Serial Connect / Disconnect";
            this.toolStripButton1.Click += new System.EventHandler(this.toolStripButton1_Click);
            // 
            // tabControlViews
            // 
            this.tabControlViews.Controls.Add(this.tabPageVarView);
            this.tabControlViews.Controls.Add(this.tabPageRawView);
            this.tabControlViews.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControlViews.Location = new System.Drawing.Point(0, 49);
            this.tabControlViews.Name = "tabControlViews";
            this.tabControlViews.SelectedIndex = 0;
            this.tabControlViews.Size = new System.Drawing.Size(1130, 626);
            this.tabControlViews.TabIndex = 3;
            // 
            // tabPageVarView
            // 
            this.tabPageVarView.Controls.Add(this.splitContainer3);
            this.tabPageVarView.Location = new System.Drawing.Point(4, 22);
            this.tabPageVarView.Name = "tabPageVarView";
            this.tabPageVarView.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageVarView.Size = new System.Drawing.Size(1122, 600);
            this.tabPageVarView.TabIndex = 0;
            this.tabPageVarView.Text = "View Values";
            this.tabPageVarView.UseVisualStyleBackColor = true;
            // 
            // splitContainer3
            // 
            this.splitContainer3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.splitContainer3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer3.Location = new System.Drawing.Point(3, 3);
            this.splitContainer3.Name = "splitContainer3";
            // 
            // splitContainer3.Panel1
            // 
            this.splitContainer3.Panel1.Controls.Add(this.splitContainer4);
            // 
            // splitContainer3.Panel2
            // 
            this.splitContainer3.Panel2.Controls.Add(this.splitContainer5);
            this.splitContainer3.Size = new System.Drawing.Size(1116, 594);
            this.splitContainer3.SplitterDistance = 302;
            this.splitContainer3.TabIndex = 0;
            // 
            // splitContainer4
            // 
            this.splitContainer4.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.splitContainer4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer4.Location = new System.Drawing.Point(0, 0);
            this.splitContainer4.Name = "splitContainer4";
            this.splitContainer4.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer4.Panel1
            // 
            this.splitContainer4.Panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.splitContainer4.Panel1.Controls.Add(this.viewSlider9);
            this.splitContainer4.Panel1.Controls.Add(this.viewSlider8);
            this.splitContainer4.Panel1.Controls.Add(this.viewSlider7);
            this.splitContainer4.Panel1.Controls.Add(this.viewSlider6);
            this.splitContainer4.Panel1.Controls.Add(this.viewSlider5);
            this.splitContainer4.Panel1.Controls.Add(this.viewSlider4);
            this.splitContainer4.Panel1.Controls.Add(this.viewSlider3);
            this.splitContainer4.Panel1.Controls.Add(this.viewSlider2);
            this.splitContainer4.Panel1.Controls.Add(this.viewSlider1);
            // 
            // splitContainer4.Panel2
            // 
            this.splitContainer4.Panel2.Controls.Add(this.viewMsgListVar);
            this.splitContainer4.Size = new System.Drawing.Size(302, 594);
            this.splitContainer4.SplitterDistance = 317;
            this.splitContainer4.TabIndex = 0;
            // 
            // viewSlider9
            // 
            this.viewSlider9.BackColor = System.Drawing.Color.Silver;
            this.viewSlider9.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.viewSlider9.dataContainer = null;
            this.viewSlider9.Dock = System.Windows.Forms.DockStyle.Left;
            this.viewSlider9.Id = "";
            this.viewSlider9.LoadDBData = null;
            this.viewSlider9.Location = new System.Drawing.Point(250, 117);
            this.viewSlider9.Name = "viewSlider9";
            this.viewSlider9.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.viewSlider9.Size = new System.Drawing.Size(50, 196);
            this.viewSlider9.TabIndex = 8;
            // 
            // viewSlider8
            // 
            this.viewSlider8.BackColor = System.Drawing.Color.Silver;
            this.viewSlider8.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.viewSlider8.dataContainer = null;
            this.viewSlider8.Dock = System.Windows.Forms.DockStyle.Left;
            this.viewSlider8.Id = "";
            this.viewSlider8.LoadDBData = null;
            this.viewSlider8.Location = new System.Drawing.Point(200, 117);
            this.viewSlider8.Name = "viewSlider8";
            this.viewSlider8.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.viewSlider8.Size = new System.Drawing.Size(50, 196);
            this.viewSlider8.TabIndex = 7;
            // 
            // viewSlider7
            // 
            this.viewSlider7.BackColor = System.Drawing.Color.Silver;
            this.viewSlider7.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.viewSlider7.dataContainer = null;
            this.viewSlider7.Dock = System.Windows.Forms.DockStyle.Left;
            this.viewSlider7.Id = "";
            this.viewSlider7.LoadDBData = null;
            this.viewSlider7.Location = new System.Drawing.Point(150, 117);
            this.viewSlider7.Name = "viewSlider7";
            this.viewSlider7.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.viewSlider7.Size = new System.Drawing.Size(50, 196);
            this.viewSlider7.TabIndex = 6;
            // 
            // viewSlider6
            // 
            this.viewSlider6.BackColor = System.Drawing.Color.Silver;
            this.viewSlider6.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.viewSlider6.dataContainer = null;
            this.viewSlider6.Dock = System.Windows.Forms.DockStyle.Left;
            this.viewSlider6.Id = "";
            this.viewSlider6.LoadDBData = null;
            this.viewSlider6.Location = new System.Drawing.Point(100, 117);
            this.viewSlider6.Name = "viewSlider6";
            this.viewSlider6.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.viewSlider6.Size = new System.Drawing.Size(50, 196);
            this.viewSlider6.TabIndex = 5;
            // 
            // viewSlider5
            // 
            this.viewSlider5.BackColor = System.Drawing.Color.Silver;
            this.viewSlider5.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.viewSlider5.dataContainer = null;
            this.viewSlider5.Dock = System.Windows.Forms.DockStyle.Left;
            this.viewSlider5.Id = "";
            this.viewSlider5.LoadDBData = null;
            this.viewSlider5.Location = new System.Drawing.Point(50, 117);
            this.viewSlider5.Name = "viewSlider5";
            this.viewSlider5.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.viewSlider5.Size = new System.Drawing.Size(50, 196);
            this.viewSlider5.TabIndex = 4;
            // 
            // viewSlider4
            // 
            this.viewSlider4.BackColor = System.Drawing.Color.Silver;
            this.viewSlider4.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.viewSlider4.dataContainer = null;
            this.viewSlider4.Dock = System.Windows.Forms.DockStyle.Left;
            this.viewSlider4.Id = "";
            this.viewSlider4.LoadDBData = null;
            this.viewSlider4.Location = new System.Drawing.Point(0, 117);
            this.viewSlider4.Name = "viewSlider4";
            this.viewSlider4.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.viewSlider4.Size = new System.Drawing.Size(50, 196);
            this.viewSlider4.TabIndex = 3;
            // 
            // viewSlider3
            // 
            this.viewSlider3.BackColor = System.Drawing.Color.Silver;
            this.viewSlider3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.viewSlider3.dataContainer = null;
            this.viewSlider3.Dock = System.Windows.Forms.DockStyle.Top;
            this.viewSlider3.Id = "";
            this.viewSlider3.LoadDBData = null;
            this.viewSlider3.Location = new System.Drawing.Point(0, 78);
            this.viewSlider3.Name = "viewSlider3";
            this.viewSlider3.Orientation = System.Windows.Forms.Orientation.Horizontal;
            this.viewSlider3.Size = new System.Drawing.Size(298, 39);
            this.viewSlider3.TabIndex = 2;
            // 
            // viewSlider2
            // 
            this.viewSlider2.BackColor = System.Drawing.Color.Silver;
            this.viewSlider2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.viewSlider2.dataContainer = null;
            this.viewSlider2.Dock = System.Windows.Forms.DockStyle.Top;
            this.viewSlider2.Id = "";
            this.viewSlider2.LoadDBData = null;
            this.viewSlider2.Location = new System.Drawing.Point(0, 39);
            this.viewSlider2.Name = "viewSlider2";
            this.viewSlider2.Orientation = System.Windows.Forms.Orientation.Horizontal;
            this.viewSlider2.Size = new System.Drawing.Size(298, 39);
            this.viewSlider2.TabIndex = 1;
            // 
            // viewSlider1
            // 
            this.viewSlider1.BackColor = System.Drawing.Color.Silver;
            this.viewSlider1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.viewSlider1.dataContainer = null;
            this.viewSlider1.Dock = System.Windows.Forms.DockStyle.Top;
            this.viewSlider1.Id = "";
            this.viewSlider1.LoadDBData = null;
            this.viewSlider1.Location = new System.Drawing.Point(0, 0);
            this.viewSlider1.Name = "viewSlider1";
            this.viewSlider1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            this.viewSlider1.Size = new System.Drawing.Size(298, 39);
            this.viewSlider1.TabIndex = 0;
            // 
            // viewMsgListVar
            // 
            this.viewMsgListVar.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.viewMsgListVar.dataContainer = null;
            this.viewMsgListVar.Dock = System.Windows.Forms.DockStyle.Fill;
            this.viewMsgListVar.Id = "";
            this.viewMsgListVar.LoadDBData = null;
            this.viewMsgListVar.Location = new System.Drawing.Point(0, 0);
            this.viewMsgListVar.Name = "viewMsgListVar";
            this.viewMsgListVar.Size = new System.Drawing.Size(298, 269);
            this.viewMsgListVar.TabIndex = 1;
            // 
            // splitContainer5
            // 
            this.splitContainer5.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.splitContainer5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer5.Location = new System.Drawing.Point(0, 0);
            this.splitContainer5.Name = "splitContainer5";
            this.splitContainer5.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer5.Panel1
            // 
            this.splitContainer5.Panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.splitContainer5.Panel1.Controls.Add(this.viewTextBox12);
            this.splitContainer5.Panel1.Controls.Add(this.viewTextBox11);
            this.splitContainer5.Panel1.Controls.Add(this.viewTextBox10);
            this.splitContainer5.Panel1.Controls.Add(this.viewTextBox9);
            this.splitContainer5.Panel1.Controls.Add(this.viewTextBox8);
            this.splitContainer5.Panel1.Controls.Add(this.viewTextBox7);
            this.splitContainer5.Panel1.Controls.Add(this.viewTextBox6);
            this.splitContainer5.Panel1.Controls.Add(this.viewTextBox5);
            this.splitContainer5.Panel1.Controls.Add(this.viewTextBox4);
            this.splitContainer5.Panel1.Controls.Add(this.viewTextBox3);
            this.splitContainer5.Panel1.Controls.Add(this.viewTextBox2);
            this.splitContainer5.Panel1.Controls.Add(this.viewTextBox1);
            // 
            // splitContainer5.Panel2
            // 
            this.splitContainer5.Panel2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.splitContainer5.Panel2.Controls.Add(this.userChartControl1);
            this.splitContainer5.Size = new System.Drawing.Size(810, 594);
            this.splitContainer5.SplitterDistance = 233;
            this.splitContainer5.TabIndex = 0;
            // 
            // viewTextBox12
            // 
            this.viewTextBox12.BackColor = System.Drawing.Color.Transparent;
            this.viewTextBox12.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.viewTextBox12.dataContainer = null;
            this.viewTextBox12.Id = "";
            this.viewTextBox12.LoadDBData = null;
            this.viewTextBox12.Location = new System.Drawing.Point(557, 153);
            this.viewTextBox12.Name = "viewTextBox12";
            this.viewTextBox12.Size = new System.Drawing.Size(174, 64);
            this.viewTextBox12.TabIndex = 11;
            // 
            // viewTextBox11
            // 
            this.viewTextBox11.BackColor = System.Drawing.Color.Transparent;
            this.viewTextBox11.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.viewTextBox11.dataContainer = null;
            this.viewTextBox11.Id = "";
            this.viewTextBox11.LoadDBData = null;
            this.viewTextBox11.Location = new System.Drawing.Point(377, 153);
            this.viewTextBox11.Name = "viewTextBox11";
            this.viewTextBox11.Size = new System.Drawing.Size(174, 64);
            this.viewTextBox11.TabIndex = 10;
            // 
            // viewTextBox10
            // 
            this.viewTextBox10.BackColor = System.Drawing.Color.Transparent;
            this.viewTextBox10.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.viewTextBox10.dataContainer = null;
            this.viewTextBox10.Id = "";
            this.viewTextBox10.LoadDBData = null;
            this.viewTextBox10.Location = new System.Drawing.Point(197, 153);
            this.viewTextBox10.Name = "viewTextBox10";
            this.viewTextBox10.Size = new System.Drawing.Size(174, 64);
            this.viewTextBox10.TabIndex = 9;
            // 
            // viewTextBox9
            // 
            this.viewTextBox9.BackColor = System.Drawing.Color.Transparent;
            this.viewTextBox9.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.viewTextBox9.dataContainer = null;
            this.viewTextBox9.Id = "";
            this.viewTextBox9.LoadDBData = null;
            this.viewTextBox9.Location = new System.Drawing.Point(17, 153);
            this.viewTextBox9.Name = "viewTextBox9";
            this.viewTextBox9.Size = new System.Drawing.Size(174, 64);
            this.viewTextBox9.TabIndex = 8;
            // 
            // viewTextBox8
            // 
            this.viewTextBox8.BackColor = System.Drawing.Color.Transparent;
            this.viewTextBox8.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.viewTextBox8.dataContainer = null;
            this.viewTextBox8.Id = "";
            this.viewTextBox8.LoadDBData = null;
            this.viewTextBox8.Location = new System.Drawing.Point(557, 83);
            this.viewTextBox8.Name = "viewTextBox8";
            this.viewTextBox8.Size = new System.Drawing.Size(174, 64);
            this.viewTextBox8.TabIndex = 7;
            // 
            // viewTextBox7
            // 
            this.viewTextBox7.BackColor = System.Drawing.Color.Transparent;
            this.viewTextBox7.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.viewTextBox7.dataContainer = null;
            this.viewTextBox7.Id = "";
            this.viewTextBox7.LoadDBData = null;
            this.viewTextBox7.Location = new System.Drawing.Point(377, 83);
            this.viewTextBox7.Name = "viewTextBox7";
            this.viewTextBox7.Size = new System.Drawing.Size(174, 64);
            this.viewTextBox7.TabIndex = 6;
            // 
            // viewTextBox6
            // 
            this.viewTextBox6.BackColor = System.Drawing.Color.Transparent;
            this.viewTextBox6.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.viewTextBox6.dataContainer = null;
            this.viewTextBox6.Id = "";
            this.viewTextBox6.LoadDBData = null;
            this.viewTextBox6.Location = new System.Drawing.Point(197, 83);
            this.viewTextBox6.Name = "viewTextBox6";
            this.viewTextBox6.Size = new System.Drawing.Size(174, 64);
            this.viewTextBox6.TabIndex = 5;
            // 
            // viewTextBox5
            // 
            this.viewTextBox5.BackColor = System.Drawing.Color.Transparent;
            this.viewTextBox5.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.viewTextBox5.dataContainer = null;
            this.viewTextBox5.Id = "";
            this.viewTextBox5.LoadDBData = null;
            this.viewTextBox5.Location = new System.Drawing.Point(17, 83);
            this.viewTextBox5.Name = "viewTextBox5";
            this.viewTextBox5.Size = new System.Drawing.Size(174, 64);
            this.viewTextBox5.TabIndex = 4;
            // 
            // viewTextBox4
            // 
            this.viewTextBox4.BackColor = System.Drawing.Color.Transparent;
            this.viewTextBox4.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.viewTextBox4.dataContainer = null;
            this.viewTextBox4.Id = "";
            this.viewTextBox4.LoadDBData = null;
            this.viewTextBox4.Location = new System.Drawing.Point(557, 13);
            this.viewTextBox4.Name = "viewTextBox4";
            this.viewTextBox4.Size = new System.Drawing.Size(174, 64);
            this.viewTextBox4.TabIndex = 3;
            // 
            // viewTextBox3
            // 
            this.viewTextBox3.BackColor = System.Drawing.Color.Transparent;
            this.viewTextBox3.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.viewTextBox3.dataContainer = null;
            this.viewTextBox3.Id = "";
            this.viewTextBox3.LoadDBData = null;
            this.viewTextBox3.Location = new System.Drawing.Point(377, 13);
            this.viewTextBox3.Name = "viewTextBox3";
            this.viewTextBox3.Size = new System.Drawing.Size(174, 64);
            this.viewTextBox3.TabIndex = 2;
            // 
            // viewTextBox2
            // 
            this.viewTextBox2.BackColor = System.Drawing.Color.Transparent;
            this.viewTextBox2.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.viewTextBox2.dataContainer = null;
            this.viewTextBox2.Id = "";
            this.viewTextBox2.LoadDBData = null;
            this.viewTextBox2.Location = new System.Drawing.Point(197, 13);
            this.viewTextBox2.Name = "viewTextBox2";
            this.viewTextBox2.Size = new System.Drawing.Size(174, 64);
            this.viewTextBox2.TabIndex = 1;
            // 
            // viewTextBox1
            // 
            this.viewTextBox1.BackColor = System.Drawing.Color.Transparent;
            this.viewTextBox1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.viewTextBox1.dataContainer = null;
            this.viewTextBox1.Id = "";
            this.viewTextBox1.LoadDBData = null;
            this.viewTextBox1.Location = new System.Drawing.Point(17, 13);
            this.viewTextBox1.Name = "viewTextBox1";
            this.viewTextBox1.Size = new System.Drawing.Size(174, 64);
            this.viewTextBox1.TabIndex = 0;
            // 
            // userChartControl1
            // 
            this.userChartControl1.dataContainer = null;
            this.userChartControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.userChartControl1.Id = "";
            this.userChartControl1.LoadDBData = null;
            this.userChartControl1.Location = new System.Drawing.Point(0, 0);
            this.userChartControl1.Name = "userChartControl1";
            this.userChartControl1.Size = new System.Drawing.Size(806, 353);
            this.userChartControl1.TabIndex = 0;
            // 
            // tabPageRawView
            // 
            this.tabPageRawView.Controls.Add(this.splitContainer1);
            this.tabPageRawView.Location = new System.Drawing.Point(4, 22);
            this.tabPageRawView.Name = "tabPageRawView";
            this.tabPageRawView.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageRawView.Size = new System.Drawing.Size(1122, 600);
            this.tabPageRawView.TabIndex = 1;
            this.tabPageRawView.Text = "Raw View";
            this.tabPageRawView.UseVisualStyleBackColor = true;
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer1.IsSplitterFixed = true;
            this.splitContainer1.Location = new System.Drawing.Point(3, 3);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.BackColor = System.Drawing.Color.Transparent;
            this.splitContainer1.Size = new System.Drawing.Size(1116, 594);
            this.splitContainer1.SplitterDistance = 174;
            this.splitContainer1.TabIndex = 0;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.AliceBlue;
            this.ClientSize = new System.Drawing.Size(1130, 697);
            this.Controls.Add(this.tabControlViews);
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "Form1";
            this.WindowState = System.Windows.Forms.FormWindowState.Minimized;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.Form1_MouseMove);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.tabControlViews.ResumeLayout(false);
            this.tabPageVarView.ResumeLayout(false);
            this.splitContainer3.Panel1.ResumeLayout(false);
            this.splitContainer3.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer3)).EndInit();
            this.splitContainer3.ResumeLayout(false);
            this.splitContainer4.Panel1.ResumeLayout(false);
            this.splitContainer4.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer4)).EndInit();
            this.splitContainer4.ResumeLayout(false);
            this.splitContainer5.Panel1.ResumeLayout(false);
            this.splitContainer5.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer5)).EndInit();
            this.splitContainer5.ResumeLayout(false);
            this.tabPageRawView.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem loadToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem optionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem serialSettingsToolStripMenuItem;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton toolStripButton1;
        private System.Windows.Forms.TabControl tabControlViews;
        private System.Windows.Forms.TabPage tabPageVarView;
        private System.Windows.Forms.TabPage tabPageRawView;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.ToolTip toolTip1;
        private System.Windows.Forms.SplitContainer splitContainer3;
        private System.Windows.Forms.SplitContainer splitContainer4;
        private System.Windows.Forms.SplitContainer splitContainer5;
        private ArduGui.ViewControls.ViewMsgList viewMsgListVar;
        private ArdoGui.ViewControls.ViewTextBox viewTextBox12;
        private ArdoGui.ViewControls.ViewTextBox viewTextBox11;
        private ArdoGui.ViewControls.ViewTextBox viewTextBox10;
        private ArdoGui.ViewControls.ViewTextBox viewTextBox9;
        private ArdoGui.ViewControls.ViewTextBox viewTextBox8;
        private ArdoGui.ViewControls.ViewTextBox viewTextBox6;
        private ArdoGui.ViewControls.ViewTextBox viewTextBox5;
        private ArdoGui.ViewControls.ViewTextBox viewTextBox3;
        private ArdoGui.ViewControls.ViewTextBox viewTextBox2;
        private ArdoGui.ViewControls.ViewTextBox viewTextBox1;
        private ArdoGui.ViewControls.ViewTextBox viewTextBox4;
        private ArdoGui.ViewControls.ViewTextBox viewTextBox7;
        private ArdoGui.ViewControls.ViewSlider viewSlider1;
        private ArdoGui.ViewControls.ViewSlider viewSlider2;
        private ArdoGui.ViewControls.ViewSlider viewSlider3;
        private ArdoGui.ViewControls.ViewSlider viewSlider6;
        private ArdoGui.ViewControls.ViewSlider viewSlider5;
        private ArdoGui.ViewControls.ViewSlider viewSlider4;
        private ArdoGui.ViewControls.ViewSlider viewSlider9;
        private ArdoGui.ViewControls.ViewSlider viewSlider8;
        private ArdoGui.ViewControls.ViewSlider viewSlider7;
        private ArdoGui.ViewControls.UserChartControl userChartControl1;

    }
}

