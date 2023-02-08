using GraphLib;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GraficFilterDisplay
{
    public partial class FormFilter : Form
    {


        public PlotterDisplayEx display = null;
        public int MaxSamples { set; get; }
        public NewSampleDetected OnNewSampleDetected;

        
        public FormFilter()
        {
            InitializeComponent();
            buttonCreate.Enabled = false;
        }

        private void labelSamplerate_Click(object sender, EventArgs e)
        {

        }

        private void buttonCreate_Click(object sender, EventArgs e)
        {

            FunctionGenerator fg = new FunctionGenerator();
            fg.OnNewSampleDetected = OnNewSampleDetected;
            fg.MaxSamples = MaxSamples;
            fg.Amplitude = Convert.ToInt32(textBoxAmplitude.Text);
            fg.Frequency = Convert.ToInt32(textBoxFrequency.Text);
            fg.Samplerate = Convert.ToInt32(textBoxSamplerate.Text); ;
            fg.SampleID = Convert.ToInt32(textBoxSenderID.Text); ;
            fg.Calculate();
            display.Refresh();
        }

        private void textBoxFrequency_TextChanged(object sender, EventArgs e)
        {
            try
            {
                int i = Convert.ToInt32(textBoxAmplitude.Text);
                i = Convert.ToInt32(textBoxFrequency.Text);
                i = Convert.ToInt32(textBoxSamplerate.Text); ;
                i = Convert.ToInt32(textBoxSenderID.Text); ;
                buttonCreate.Enabled = true; 
            }
            catch
            {
                buttonCreate.Enabled = false;
            }
        }

        private void buttonCalc_Click(object sender, EventArgs e)
        {
            double Coef = Convert.ToDouble(textBoxCalcLPCoeff.Text);
            double dt = 1/ Convert.ToDouble(textBoxCalcRate.Text);
            labelCalcDT.Text = Math.Round(dt, 4).ToString();
            double Fc = Coef / ((1 - Coef) * 2 * Math.PI * dt);
            textBoxCalcFreq.Text = Math.Round(Fc, 2).ToString();
        }
    }
}
