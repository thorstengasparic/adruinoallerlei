using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using ArduGui.Settings;
using ArduGui.Controller;

namespace ArduGui
{
    public partial class COMSetup : Form
    {

        public COMSettings ComSetting
        {
            get {
                COMSettings com = new COMSettings();
                com.PortName = comboBoxPort.Text;
                com.BaudRate = comboBoxBaud.Text;
                com.Parity = comboBoxParity.Text;
                com.DataBits = comboBoxDataBit.Text;
                com.StopBits = comboBoxStopBit.Text;
                com.Handshake = comboBoxHandShake.Text; 
                return com; 
            }
            set {
                COMSettings com = value;
                comboBoxPort.Text = com.PortName;
                comboBoxBaud.Text = com.BaudRate;
                comboBoxParity.Text = com.Parity;
                comboBoxDataBit.Text = com.DataBits;
                comboBoxStopBit.Text = com.StopBits;
                comboBoxHandShake.Text = com.Handshake; 

            }
        }
        public COMSetup()
        {
            InitializeComponent();
            
        }
        private void COMSetup_Load(object sender, EventArgs e)
        {
            comboBoxPort.Items.AddRange(SerialPort.GetPortNames());
            comboBoxBaud .Items.Add("9600");
            comboBoxBaud.Items.Add("115200");
            comboBoxParity.Items.AddRange(Enum.GetNames(typeof(Parity)));
            comboBoxDataBit.Items.Add("8");
            comboBoxStopBit.Items.AddRange(Enum.GetNames(typeof(StopBits)));
            comboBoxHandShake.Items.AddRange(Enum.GetNames(typeof(Handshake)));
        }

        public bool Init(COMSettings com)
        {
            return true;
        }
    }
}
