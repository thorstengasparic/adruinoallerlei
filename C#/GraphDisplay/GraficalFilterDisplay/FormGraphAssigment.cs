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
    public partial class FormGraphAssigment : Form
    {
        CheckBox[] checkBoxes;
        public FormGraphAssigment()
        {
            InitializeComponent();
            checkBoxes = new CheckBox[] { checkBox0, checkBox1, checkBox2, checkBox3, checkBox4, checkBox5, checkBox6, checkBox7, checkBox8, checkBox9 };
            int i = 0;
            foreach (CheckBox cb in checkBoxes)
            {
                cb.Text = "Graph " + i.ToString();
                cb.CheckedChanged += new System.EventHandler(this.checkBox_CheckedChanged);
                i++;
            }
        }

        SamplesDispatcher _samplesDisp;
        public SamplesDispatcher SamplesDisp {
            get
            {
                return _samplesDisp;
            }
            set
            {
                _samplesDisp = SamplesDispatcher.Clone(value);
                ToGui(_samplesDisp);
            }
        }

        void ToGui(SamplesDispatcher data)
        {
            listBox1.Items.Clear();
            for (int i = 0; i < data.MaxSampleIndex; i++)
            {
                listBox1.Items.Add(string.Format("Sample ID {0}", i));
            }
            int j = 0;
            foreach (CheckBox cb in checkBoxes)
            {
                cb.Visible = j < data.MaxGraphCount;
                j++;
            }
        }
        SamplesDispatcher  FromGui()
        {
            if (listBox1.SelectedIndex == -1)
                return _samplesDisp;

            List<int> lst = new List<int>();

            int i = 0;
            foreach (CheckBox cb in checkBoxes)
            {
                if (cb.Checked)
                    lst.Add(i);
                i++;
            }
            _samplesDisp.Set(listBox1.SelectedIndex, lst.ToArray());
            return _samplesDisp;
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            Close();
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listBox1.SelectedIndex == -1) return;

            doCBChanges = false;
            int[] checkedGraphs = _samplesDisp.Disp(listBox1.SelectedIndex);

            foreach (CheckBox cb in checkBoxes)
            {
                cb.Checked = false;
            }
            foreach (int graph in checkedGraphs)
                checkBoxes[graph].Checked = true;

            doCBChanges = true; ;
        }
        bool doCBChanges = true;
        private void checkBox_CheckedChanged(object sender, EventArgs e)
        {
            if (!doCBChanges) return;
            FromGui();
        }

        private void FormGraphAssigment_Load(object sender, EventArgs e)
        {
            listBox1.SelectedIndex = 0;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            _samplesDisp.Reset();
            listBox1.SelectedIndex = 0;
            listBox1_SelectedIndexChanged(null, null);
        }
    }
}
