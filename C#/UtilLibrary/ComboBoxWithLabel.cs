using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.Design;
using System.Drawing.Design;

namespace UtilLibrary
{
    public partial class ComboBoxWithLabel : UserControl
    {
        public ComboBoxWithLabel()
        {
            InitializeComponent();
        }

        public string LabelText
        {
            get { return label1.Text; }
            set { label1.Text = value; }
        }

        public ComboBox.ObjectCollection Items
        {
            get
            {
                return comboBox1.Items;
            }
        }
    }
    [DefaultProperty("Items")]
    [ToolStripItemDesignerAvailability(ToolStripItemDesignerAvailability.All)]
    public class MyCustomComboBoxWithLabel : ToolStripControlHost
    {
        public MyCustomComboBoxWithLabel()
            : base(new ComboBoxWithLabel())
        {
        }
        [Browsable(false)]
        public ComboBoxWithLabel ComboBoxWithLabel
        {
            get { return base.Control as ComboBoxWithLabel; }
        }


        [Browsable(true)]
        [DefaultValue(false)]
        public string LabelText
        {
            get { return ComboBoxWithLabel.LabelText; }
            set { ComboBoxWithLabel.LabelText = value; }
        }

        [Localizable(true)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Content)]
        [Editor("System.Windows.Forms.Design.ListControlStringCollectionEditor, System.Design, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b03f6f7f11d50a3a", typeof(UITypeEditor))]
        public System.Windows.Forms.ComboBox.ObjectCollection Items
        {
            get { return ComboBoxWithLabel.comboBox1.Items; }
            set
            {
                foreach (var item in value)
                {
                    ComboBoxWithLabel.comboBox1.Items.Add(item);
                }
            }
        }
    }
}
