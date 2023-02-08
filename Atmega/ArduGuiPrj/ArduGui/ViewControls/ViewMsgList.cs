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

namespace ArduGui.ViewControls
{
    public partial class ViewMsgList : BaseViewControl
    {

        public ViewMsgList()
        {
            InitializeComponent();
            m_lb.DrawMode = DrawMode.OwnerDrawFixed;
            m_lb.DrawItem += listBox1_DrawItem;
        }

        private void listBox1_DrawItem(object sender, DrawItemEventArgs e)
        {
            try
            {
                // Hintergrund zeichnen lassen
                e.DrawBackground();
                // eigenen Kram zeichnen
                //Brush b = ((e.Index & 1) == 0) ? Brushes.Green : Brushes.Red;
                ListViewItem lvi = (ListViewItem)m_lb.Items[e.Index];
                Brush b = new SolidBrush(lvi.ForeColor);
                e.Graphics.DrawString(lvi.Text, m_lb.Font, b, e.Bounds.Left, e.Bounds.Top);
                // Fokus des Eintrags zeichnen lassen
                e.DrawFocusRectangle();
            }
            catch { }
        }

        public bool Clear()
        {
            m_lb.Items.Clear();
            m_tb.Text = "";
            return true;
        }

        public void JumpToLastLine()
        {
            m_lb.ClearSelected();
            m_lb.SelectedIndex = m_lb.Items.Count - 1;
        }

        public override bool NotifyChanges(MessageItem message)
        {
            string tsatmp = message.Timestamp.ToString("yyyyMMdd-HH:mm:ss");
            if (checkBoxRawmode.Checked)
            {
                if (message.Type == MessageType.Unknown)
                    AddMessage(message.Type, tsatmp, message.RawMessage);
                else
                    AddMessage(message.Type, tsatmp, message.Content);
            }
            else
            {
                if (message.Type == MessageType.Error)
                {
                    AddMessage(message.Type, tsatmp, message.Content);
                }
                if (message.Type == MessageType.Information)
                {
                    AddMessage(message.Type, tsatmp, message.Content);
                }
            }

            return true;
        }

        bool AddMessage(MessageType msgType, string Timestamp, string msg)
        {
            ListViewItem lvi = new ListViewItem("["+Timestamp+"] - " + msg);
            lvi.ForeColor = Color.Black;
            //m_tb.BackColor = Color.White;

            if (msgType == MessageType.Error)
            {
                //m_tb.BackColor = Color.Red;
                lvi.ForeColor = Color.Red;
            }

            if (msgType == MessageType.Variable)
            {
                //m_tb.BackColor = Color.Aqua;
                lvi.ForeColor = Color.Aqua;
            }

            if (msgType == MessageType.Configuration)
            {
                //m_tb.BackColor = Color.Brown;
                lvi.ForeColor = Color.Brown;
            }

            m_lb.Items.Add(lvi);
            if (m_lb.Items.Count < m_lb.SelectedIndex + 3)
            {
                m_lb.ClearSelected();
                m_lb.SelectedIndex = m_lb.Items.Count - 1;
            }
            //m_tb.Text = msg;
            return true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Clear();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            JumpToLastLine();
        }

        private void m_tb_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                dataContainer.UserKeyInput(m_tb.Text);
                m_tb.Text = "";
            }
        }
    }
}
