namespace GraficFilterDisplay
{
    partial class FormFilter
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.buttonCreate = new System.Windows.Forms.Button();
            this.textBoxSenderID = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxAmplitude = new System.Windows.Forms.TextBox();
            this.labelAmplitude = new System.Windows.Forms.Label();
            this.textBoxSamplerate = new System.Windows.Forms.TextBox();
            this.labelSamplerate = new System.Windows.Forms.Label();
            this.textBoxFrequency = new System.Windows.Forms.TextBox();
            this.labelFrequency = new System.Windows.Forms.Label();
            this.radioButton1 = new System.Windows.Forms.RadioButton();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.buttonCalc = new System.Windows.Forms.Button();
            this.textBoxCalcLPCoeff = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.textBoxCalcRate = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.textBoxCalcFreq = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.labelCalcDT = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.buttonCreate);
            this.groupBox1.Controls.Add(this.textBoxSenderID);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.textBoxAmplitude);
            this.groupBox1.Controls.Add(this.labelAmplitude);
            this.groupBox1.Controls.Add(this.textBoxSamplerate);
            this.groupBox1.Controls.Add(this.labelSamplerate);
            this.groupBox1.Controls.Add(this.textBoxFrequency);
            this.groupBox1.Controls.Add(this.labelFrequency);
            this.groupBox1.Controls.Add(this.radioButton1);
            this.groupBox1.Location = new System.Drawing.Point(23, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(230, 133);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Function Generator";
            // 
            // buttonCreate
            // 
            this.buttonCreate.Location = new System.Drawing.Point(176, 94);
            this.buttonCreate.Name = "buttonCreate";
            this.buttonCreate.Size = new System.Drawing.Size(34, 23);
            this.buttonCreate.TabIndex = 1;
            this.buttonCreate.Text = "Set";
            this.buttonCreate.UseVisualStyleBackColor = true;
            this.buttonCreate.Click += new System.EventHandler(this.buttonCreate_Click);
            // 
            // textBoxSenderID
            // 
            this.textBoxSenderID.Location = new System.Drawing.Point(138, 96);
            this.textBoxSenderID.Name = "textBoxSenderID";
            this.textBoxSenderID.Size = new System.Drawing.Size(32, 20);
            this.textBoxSenderID.TabIndex = 8;
            this.textBoxSenderID.Text = "0";
            this.textBoxSenderID.TextChanged += new System.EventHandler(this.textBoxFrequency_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(79, 99);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(52, 13);
            this.label1.TabIndex = 7;
            this.label1.Text = "SenderID";
            // 
            // textBoxAmplitude
            // 
            this.textBoxAmplitude.Location = new System.Drawing.Point(138, 44);
            this.textBoxAmplitude.Name = "textBoxAmplitude";
            this.textBoxAmplitude.Size = new System.Drawing.Size(72, 20);
            this.textBoxAmplitude.TabIndex = 6;
            this.textBoxAmplitude.Text = "200";
            this.textBoxAmplitude.TextChanged += new System.EventHandler(this.textBoxFrequency_TextChanged);
            // 
            // labelAmplitude
            // 
            this.labelAmplitude.AutoSize = true;
            this.labelAmplitude.Location = new System.Drawing.Point(79, 47);
            this.labelAmplitude.Name = "labelAmplitude";
            this.labelAmplitude.Size = new System.Drawing.Size(53, 13);
            this.labelAmplitude.TabIndex = 5;
            this.labelAmplitude.Text = "Amplitude";
            // 
            // textBoxSamplerate
            // 
            this.textBoxSamplerate.Location = new System.Drawing.Point(138, 70);
            this.textBoxSamplerate.Name = "textBoxSamplerate";
            this.textBoxSamplerate.Size = new System.Drawing.Size(72, 20);
            this.textBoxSamplerate.TabIndex = 4;
            this.textBoxSamplerate.Text = "250";
            this.textBoxSamplerate.TextChanged += new System.EventHandler(this.textBoxFrequency_TextChanged);
            // 
            // labelSamplerate
            // 
            this.labelSamplerate.AutoSize = true;
            this.labelSamplerate.Location = new System.Drawing.Point(79, 73);
            this.labelSamplerate.Name = "labelSamplerate";
            this.labelSamplerate.Size = new System.Drawing.Size(60, 13);
            this.labelSamplerate.TabIndex = 3;
            this.labelSamplerate.Text = "Samplerate";
            this.labelSamplerate.Click += new System.EventHandler(this.labelSamplerate_Click);
            // 
            // textBoxFrequency
            // 
            this.textBoxFrequency.Location = new System.Drawing.Point(138, 18);
            this.textBoxFrequency.Name = "textBoxFrequency";
            this.textBoxFrequency.Size = new System.Drawing.Size(72, 20);
            this.textBoxFrequency.TabIndex = 2;
            this.textBoxFrequency.Text = "100";
            this.textBoxFrequency.TextChanged += new System.EventHandler(this.textBoxFrequency_TextChanged);
            // 
            // labelFrequency
            // 
            this.labelFrequency.AutoSize = true;
            this.labelFrequency.Location = new System.Drawing.Point(79, 21);
            this.labelFrequency.Name = "labelFrequency";
            this.labelFrequency.Size = new System.Drawing.Size(57, 13);
            this.labelFrequency.TabIndex = 1;
            this.labelFrequency.Text = "Frequency";
            // 
            // radioButton1
            // 
            this.radioButton1.AutoSize = true;
            this.radioButton1.Location = new System.Drawing.Point(22, 19);
            this.radioButton1.Name = "radioButton1";
            this.radioButton1.Size = new System.Drawing.Size(51, 17);
            this.radioButton1.TabIndex = 0;
            this.radioButton1.TabStop = true;
            this.radioButton1.Text = "Sinus";
            this.radioButton1.UseVisualStyleBackColor = true;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Controls.Add(this.labelCalcDT);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.buttonCalc);
            this.groupBox2.Controls.Add(this.textBoxCalcLPCoeff);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.textBoxCalcRate);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.textBoxCalcFreq);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Location = new System.Drawing.Point(269, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(218, 133);
            this.groupBox2.TabIndex = 9;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Calculator";
            // 
            // buttonCalc
            // 
            this.buttonCalc.Location = new System.Drawing.Point(147, 44);
            this.buttonCalc.Name = "buttonCalc";
            this.buttonCalc.Size = new System.Drawing.Size(49, 23);
            this.buttonCalc.TabIndex = 1;
            this.buttonCalc.Text = "Calc";
            this.buttonCalc.UseVisualStyleBackColor = true;
            this.buttonCalc.Click += new System.EventHandler(this.buttonCalc_Click);
            // 
            // textBoxCalcLPCoeff
            // 
            this.textBoxCalcLPCoeff.Location = new System.Drawing.Point(69, 40);
            this.textBoxCalcLPCoeff.Name = "textBoxCalcLPCoeff";
            this.textBoxCalcLPCoeff.Size = new System.Drawing.Size(72, 20);
            this.textBoxCalcLPCoeff.TabIndex = 6;
            this.textBoxCalcLPCoeff.Text = "0,025";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(10, 43);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(35, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "Coeff.";
            // 
            // textBoxCalcRate
            // 
            this.textBoxCalcRate.Location = new System.Drawing.Point(69, 62);
            this.textBoxCalcRate.Name = "textBoxCalcRate";
            this.textBoxCalcRate.Size = new System.Drawing.Size(72, 20);
            this.textBoxCalcRate.TabIndex = 4;
            this.textBoxCalcRate.Text = "250";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(10, 65);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(60, 13);
            this.label4.TabIndex = 3;
            this.label4.Text = "Samplerate";
            // 
            // textBoxCalcFreq
            // 
            this.textBoxCalcFreq.Enabled = false;
            this.textBoxCalcFreq.Location = new System.Drawing.Point(69, 18);
            this.textBoxCalcFreq.Name = "textBoxCalcFreq";
            this.textBoxCalcFreq.Size = new System.Drawing.Size(72, 20);
            this.textBoxCalcFreq.TabIndex = 2;
            this.textBoxCalcFreq.Text = "100";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(10, 21);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(57, 13);
            this.label5.TabIndex = 1;
            this.label5.Text = "Frequency";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(10, 85);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(131, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "Fc=Coef/((1-Coef)*2*Pi*dt)";
            // 
            // labelCalcDT
            // 
            this.labelCalcDT.AutoSize = true;
            this.labelCalcDT.Location = new System.Drawing.Point(147, 77);
            this.labelCalcDT.Name = "labelCalcDT";
            this.labelCalcDT.Size = new System.Drawing.Size(10, 13);
            this.labelCalcDT.TabIndex = 8;
            this.labelCalcDT.Text = "-";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(10, 104);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(193, 13);
            this.label6.TabIndex = 9;
            this.label6.Text = "val = (1 - coeff)*prevVal + coeff*newVal";
            // 
            // FormFilter
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(715, 462);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "FormFilter";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "FormFilter";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textBoxFrequency;
        private System.Windows.Forms.Label labelFrequency;
        private System.Windows.Forms.RadioButton radioButton1;
        private System.Windows.Forms.TextBox textBoxAmplitude;
        private System.Windows.Forms.Label labelAmplitude;
        private System.Windows.Forms.TextBox textBoxSamplerate;
        private System.Windows.Forms.Label labelSamplerate;
        private System.Windows.Forms.Button buttonCreate;
        private System.Windows.Forms.TextBox textBoxSenderID;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button buttonCalc;
        private System.Windows.Forms.TextBox textBoxCalcLPCoeff;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBoxCalcRate;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBoxCalcFreq;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label labelCalcDT;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label6;
    }
}