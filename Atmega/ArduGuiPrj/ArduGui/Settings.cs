using System;
using System.IO;
using System.Collections.Generic;
using System.Text;
using System.Xml.Serialization;
using System.Windows.Forms;
using System.Drawing;
using ArduGui.Controller;

namespace ArduGui.Settings
{
    public class AppSettings
    {
        public COMSettings COMParmas;
        public List<String> guiConfig;
        public FormSettings mainForm;
        public string m_description;
        
        public AppSettings()
        {
            m_description = "Default";
            COMParmas = new COMSettings();
            guiConfig = new List<string>();
            mainForm = new FormSettings();
        }
        
        public string Serialize()
        {
            XmlSerializer serializer = new XmlSerializer(typeof(AppSettings));
            StringBuilder stringBuilder = new StringBuilder();
            StringWriter stringWriter = new StringWriter(stringBuilder);
            serializer.Serialize(stringWriter, this);
            return stringBuilder.ToString();
        }

        public bool SaveToFile(string filename)
        {
            try
            {
                File.WriteAllText(filename, Serialize());
                return true;
            }
            catch { }
            return false;
        }

        public static AppSettings FromFile(string filename)
        {
            if (!File.Exists(filename)) return new AppSettings();
            try 
            {
                string str = File.ReadAllText(filename);
                return FromString(str);
            }
            catch{}
            return new AppSettings();

        }

        public static AppSettings FromString(string xmlString)
        {

            AppSettings data = null;
            try
            {
                XmlSerializer serializer = new XmlSerializer(typeof(AppSettings));
                data = (AppSettings)serializer.Deserialize(new StringReader(xmlString));
            }
            catch { }
            return data;
        }
    }

    public class FormSettings
    {
        public Size MainFormSize;
        public Point MainFormLocation;
        public FormWindowState MainFormState;

        public Size Panel1FormSize;
        public int SplitterDistance3;
        public int SplitterDistance4;
        public int SplitterDistance5;
        
        public FormSettings()
        {
            MainFormSize = new Size(1024, 786);
            MainFormLocation = new Point(0, 0);
            MainFormState = FormWindowState.Normal;
            SplitterDistance3 = 300;
            SplitterDistance4 = 420;
            SplitterDistance5 = 250;
        }
    }
    
    
}
