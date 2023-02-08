using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;
using ArduGui.Controller;


namespace ArduGui.Model
{
    
    public class GuiDBAccess : IViewObserver
    {
        string m_Id;
        IModelContainer m_dataContainer;
        protected List<string> regVars;
        LoadDataFunction _LoadData = null;
        public LoadDataFunction LoadDBData
        {
            get { return _LoadData; }
            set { _LoadData = value; }
        }
        public GuiDBAccess()
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

        public virtual bool NotifyChanges(MessageItem message) 
        {
            if (message.Type != MessageType.Variable) return false;
            if (ValueCommand.GetCommandType(message.Content) != ValueCommandType.Float) return false;

            string VarId;
            double content;
            ValueCommand.ExtractDouble(message.Content, out VarId, out content);
            StoreValueInDB(int.Parse( VarId), DateTime.Now, content);
            return true;
        }

    
        private static string _projectDBCreationTemplate =
            @"CREATE DATABASE [{0}] ON  PRIMARY " +
            "( NAME = N'{0}', FILENAME = N'c:\\tmp\\{0}.mdf' , SIZE = 10000KB , MAXSIZE = UNLIMITED, FILEGROWTH = 10240KB ) " +
            "LOG ON ( NAME = N'{0}_log', FILENAME = N'c:\\tmp\\{0}.ldf' , SIZE = 560KB , MAXSIZE = 2048GB , FILEGROWTH = 20%)";

        private static string _ValueTableCreationTemplate =
            "CREATE TABLE [dbo].[Data](" +
            "[Timestamp] [bigint] NULL," +
            "[Value] [float] NULL," +
            "[ID] [int] NULL" +
            ") ON [PRIMARY]";
            static string connectionstring="Network Library=DBMSSOCN;User ID=sa;Initial Catalog=Rittal;Data Source=192.168.71.144\\sqlexpress,1205 providerName=System.Data.SqlClient";

            
        System.Data.SqlClient.SqlCommand m_comm = null;
        string connectionString;

        public bool Connect(string projectName, string ConnectionString)
        {
            bool erg = Open(projectName, ConnectionString);
            if (!erg)
            {
                erg = CreateTable(ConnectionString, projectName);
            }
            return erg;
        }
        
        bool CreateTable(string ConnectionString, string DBname)
        {
            Open("master", ConnectionString);
            try
            {
                m_comm.CommandText = String.Format(_projectDBCreationTemplate, DBname);
                int iResult = m_comm.ExecuteNonQuery();
            }
            catch (Exception ex)
            {
                return false;
            }
            Open(DBname, ConnectionString);
            
            try
            {
                m_comm.CommandText = _ValueTableCreationTemplate;
                int iResult = m_comm.ExecuteNonQuery();
            }
            catch (Exception ex)
            {
                return false;
            }
            return true;
        }

        bool Open(string projectName, string ConnectionString  )
        {
            connectionString = ConnectionString + ";Initial Catalog=" + projectName;
            if (m_comm != null) m_comm.Connection.Close();
 
            m_comm = new System.Data.SqlClient.SqlCommand();
            m_comm.Connection = new System.Data.SqlClient.SqlConnection(connectionString); 

            try
            {
                m_comm.Connection.Open();
            }
            catch
            {
                m_comm = null;
                return false;
            }

            return true;
        }

        static string sqlInsertValue = "INSERT INTO [data] ([ID],[Timestamp],[value]) VALUES ({0}, {1}, {2})";
        public bool StoreValueInDB(int id, DateTime time, double value)
        {
            if (m_comm == null) return true;
            string val = value.ToString().Replace(',', '.');
            string dateStr = MilliTimeStamp(time, 1).ToString();
            try
            {
                m_comm.CommandText = String.Format(sqlInsertValue, id, dateStr, val);
                int iResult = m_comm.ExecuteNonQuery();
            }
            catch
            {
                return false;
            }
            return true;
        }
        
        ulong MilliTimeStamp(DateTime TheDate, int GMT)
        {
            DateTime d1 = new DateTime(1970, 1, 1);
            DateTime d2 = TheDate.ToUniversalTime();
            TimeSpan ts = new TimeSpan(d2.Ticks - d1.Ticks);

            return Convert.ToUInt64(ts.TotalSeconds) * 1000;
        }

        DateTime DateTimeStamp(long MilliTimeStamp, int GMT)
        {
            DateTime d1 = new DateTime(1970, 1, 1);
            DateTime d2 = d1.AddMilliseconds(MilliTimeStamp + (3600 * GMT) * 1000);
            return d2;
        }
        static string sqlSelectValue = "SELECT [timestamp],[value] FROM [data] WHERE ([timestamp] BETWEEN {0} AND {1}) AND (ID={2}) ORDER BY [timestamp]";
        
        public Value[] LoadDataFromDB(int ID, DateTime from, DateTime to, bool FromValue)
        {
            List<Value> list = new List<Value>();
            list.Clear();
            ulong msFrom = MilliTimeStamp(from, 1);
            ulong msTo = MilliTimeStamp(to, 1);
            string selString = String.Format(sqlSelectValue, msFrom, msTo, ID);
            try
            {
                m_comm.CommandText = selString;
                System.Data.SqlClient.SqlDataReader reader = m_comm.ExecuteReader();
                try
                {
                    while (reader.Read())
                    {
                        ulong ts = (ulong)reader.GetInt64(0);
                        double val = reader.GetDouble(1);
                        list.Add(new Value(val, DateTimeStamp((long)ts, 1)));
                    }
                }
                catch (Exception ex)
                {
                    return list.ToArray();
                }
            }

            catch
            {
                return list.ToArray();
            }
            return list.ToArray();

        }
        
    }
}
