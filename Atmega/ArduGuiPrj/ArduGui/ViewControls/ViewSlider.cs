using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ArdoGui.ViewControls
{
    public partial class ViewSlider : ArduGui.View.BaseViewControl
    {
        public ViewSlider()
        {
            InitializeComponent();
            Reset("Slider", true);
        }
        
        public void Init(string HeaderText, string UnitText, string VarId, double min, double max)
        {
            Reset(HeaderText, true);
            label2.Text = min.ToString();
            label1.Text = max.ToString();
        }
        public void Reset(string name, bool visible)
        {
            label1.Text = "min";
            label2.Text = "max";
            label3.Text = name;
            trackBar1.Enabled = visible;
            textBox1.Text = "";
            Visible = visible;
        }

        public System.Windows.Forms.Orientation Orientation
        {
            get { return trackBar1.Orientation; }
            set {
                if (trackBar1.Orientation == value) return;
                if (trackBar1.Orientation == System.Windows.Forms.Orientation.Horizontal)
                {
                    //trackBar1.Dock = DockStyle.Top;
                }
                else
                {
                    //trackBar1.Dock = DockStyle.Left;
                }
                trackBar1.Orientation = value;
            }
        }

        private void ViewSlider_SizeChanged(object sender, EventArgs e)
        {
            //int tmp = Size.Width;
            //this.Dock = DockStyle.Top
            //.Width = Size.Height;
            //Size.Height = 10;
            this.BorderStyle = BorderStyle.Fixed3D;
            if (trackBar1.Orientation == System.Windows.Forms.Orientation.Horizontal)
            {
                trackBar1.Top = 2;
                trackBar1.Left = 0;
                trackBar1.Size = new Size(Size.Width -45, Size.Height);
                
                label3.Top = -2;
                label3.Left = -2;
                
                label2.Top = Size.Height / 2 ;
                label2.Left = 0;

                label1.Top = Size.Height / 2 ;
                label1.Left = Size.Width - 70;

                textBox1.Top = 2;
                textBox1.Left = Size.Width - 50;
                textBox1.Width = 45;
            }
            else
            {
                trackBar1.Top = 23;
                trackBar1.Left = 3;
                trackBar1.Size = new Size(Size.Width, Size.Height - 50);
                label3.Top = 0;
                label3.Left = 0;
                
                label1.Top = 15;
                label1.Left = 0;

                label2.Top = Size.Height -35;
                label2.Left = 0;

                textBox1.Top = Size.Height - 22;
                textBox1.Left = 0;
                textBox1.Width = Size.Width;
            }
            
        }
    }
}
