using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using ArduGui.Settings;
using ArduGui.Model;
using ArduGui.Controller;

namespace ArduGui.View
{

    public class BaseViewControl : UserControl, IViewObserver
    {
        string m_Id;
        IModelContainer m_dataContainer;
        protected List<string> regVars;
        public BaseViewControl()
        {
            m_Id = "";
            m_dataContainer = null;
            regVars = new List<string>();
        }
        LoadDataFunction _LoadData = null;
        public LoadDataFunction LoadDBData
        {
            get { return _LoadData; }
            set { _LoadData = value; }
        }
        public string Id
        { 
            get 
            {
                return m_Id;
            }
            set
            {
                m_Id = value;
            }
        }
        public IModelContainer dataContainer
        {
            get
            {
                return m_dataContainer;
            }
            set
            {
                m_dataContainer = value;
            }
        }
        public virtual bool NotifyChanges(MessageItem message) { return false; }

    }

    public class BaseViewForm : Form, IViewObserver
    {
        string m_Id;
        IModelContainer m_dataContainer;
        protected List<string> regVars;
        public BaseViewForm()
        {
            m_Id = "";
            m_dataContainer = null;
            regVars = new List<string>();
        }

        public string Id
        {
            get
            {
                return m_Id;
            }
            set
            {
                m_Id = value;
            }
        }
        public IModelContainer dataContainer
        {
            get
            {
                return m_dataContainer;
            }
            set
            {
                m_dataContainer = value;
            }
        }
        public virtual bool NotifyChanges(MessageItem message) { return false; }
        LoadDataFunction _LoadData = null;
        public LoadDataFunction LoadDBData
        {
            get { return _LoadData; }
            set { _LoadData = value; }
        }


    }
}
