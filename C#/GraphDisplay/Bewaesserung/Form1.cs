using Arduino.Serial;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Bewaesserung
{
    public partial class Form1 : Form
    {



        COMSettings comCgf = new COMSettings();
        SerialFIFO serial = new SerialFIFO();
        public Form1()
        {

            InitializeComponent();
            comCgf.PortName = "COM12";
            comCgf.BaudRate = "9600";

            serial.OnNewMessage = SerialNewMessageReceived;
            serial.Init(comCgf);
            serial.Open();

        }

        private void comboBoxCOM_MouseEnter_1(object sender, EventArgs e)
        {
            comboBoxCOM.Items.Clear();
            comboBoxCOM.Text = "";
            comboBoxCOM.Items.AddRange(SerialConfig.Ports);

            int idx = comboBoxCOM.Items.IndexOf(comCgf.PortName);

            try
            {
                comboBoxCOM.SelectedIndex = idx;
            }
            catch (Exception ex)
            {
            }
        }

        private void comboBoxCOM_SelectedValueChanged(object sender, EventArgs e)
        {
            comCgf.PortName = comboBoxCOM.SelectedItem.ToString();
            serial.Close();
            serial.Init(comCgf);
            serial.Open();
        }

        private void buttonInfo_Click(object sender, EventArgs e)
        {
            serial.UserKeyInput("info\n");
        }

        public bool SerialNewMessageReceived(string newMsg)
        {
            string newMsg1 = newMsg;
            this.Invoke(new MethodInvoker(
                    delegate
                    {
                        textBox1.Text += "\n\r"+newMsg1;
                    }
                    ));
            
            return true;
        }

        private void buttonHistory_Click(object sender, EventArgs e)
        {
            serial.UserKeyInput("history\n");
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            serial.Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            serial.UserKeyInput("?\n");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            serial.UserKeyInput(textBoxCMD.Text + "\n");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            serial.UserKeyInput("measure\n");
            
        }

        private void button4_Click(object sender, EventArgs e)
        {
            textBox1.Text = "";
        }
    }
}