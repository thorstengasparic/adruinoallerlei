using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using ArduGui.Settings;
using ArduGui.Model;
using ArduGui.Controller;
using ArduGui.View;

namespace ArdoGui.ViewControls
{
    public partial class ViewTextBox : ArduGui.View.BaseViewControl
    {
        public ViewTextBox()
        {
            InitializeComponent();
            //Reset(true);
        }

        public void Reset(string Name, bool visible)
        {
            groupBox1.Text = Name;
            groupBox1.Enabled = visible;
            label1.Text = "label";
            textBox1.Text = "text";
            groupBox1.Visible = visible;
            Visible = visible;
        }

        public override bool NotifyChanges(MessageItem message) 
        {
            if (message.Type != MessageType.Variable) return true;
            string VarId;
            string content;
            ValueCommand.ExtractInitProjectCmd(message.Content, out VarId, out content);
            if (regVars.Contains(VarId))
                textBox1.Text = content;
            return true; 
        }

        public bool Init(string HeaderText, string UnitText, string VarId)
        {
            groupBox1.Text = HeaderText;
            groupBox1.Enabled = true;
            label1.Text = UnitText;
            textBox1.Text = "";
            groupBox1.Visible = true;
            regVars.Add(VarId);
            return true;
        }
    }
}
