using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Xml.Serialization;
using Infotek.Tools;

namespace Infotek.Tools
{
    public class GernericSerializer
    {

        public static string UserApplPathName(string cfgName, bool createDirectory)
        {
            string configPathname = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), System.Diagnostics.Process.GetCurrentProcess().ProcessName);
            configPathname = configPathname.Replace(".vshost","");
            if (createDirectory) Directory.CreateDirectory(configPathname);
            configPathname = Path.Combine(configPathname, cfgName);
            return configPathname;
        }

        static string Pwd = "&7*#HG%g8=KJH!Gjhg";

        public static void Serialize(string cfgName, object o)
        {
            Serialize(cfgName, o, false);
        }
        public static void Serialize(string cfgName, object o, bool crypted )
        {
            // usage:    myType myObject;
            //           GernericSerializer.Serialize("default.cfg", myObject); 
            //           myObject = (myType)GernericSerializer.DeSerialize("default.cfg", myObject.GetType());
            try
            {
                byte[] ser = Serialize(o);
                //if (crypted)
                //{
                //    ITEncryption crypt = new ITEncryption();
                //    ser = crypt.Encrypt(ser, GernericSerializer.Pwd);
                //}
                File.WriteAllBytes(cfgName, ser);
            }
            catch (Exception exc)
            {
                string logString = String.Format("Fehler beim speichern der Datei {0}.", cfgName);
                //EventLogging.LogConMsg('E', "", logString);
                //EventLogging.LogConMsg('E', "", exc);
            }
            
        }
        public static byte[] Serialize(object o)
        {
            XmlSerializer mySerializer = new XmlSerializer(o.GetType());
            using (MemoryStream ms = new MemoryStream())
            {
                StreamWriter myWriter = new StreamWriter(ms);
                mySerializer.Serialize(myWriter, o);
                myWriter.Close();
                return ms.ToArray();
            }
        }

        public static string SerializeToString(object o)
        {
            XmlSerializer xmlSerializer = new XmlSerializer(o.GetType());
            StringWriter textWriter = new StringWriter();
            xmlSerializer.Serialize(textWriter, o);
            return textWriter.ToString();
        }

        public static object DeSerialize(byte[] data, Type t)
        {
            // usage:    myType myObject;
            //           GernericSerializer.Serialize("default.cfg", myObject); 
            //           myObject = (myType)GernericSerializer.DeSerialize("default.cfg", myObject.GetType());
            XmlSerializer mySerializer = new XmlSerializer(t);
            MemoryStream ms = new MemoryStream();
            ms.Write(data, 0, data.Length);
            ms.Position = 0;
            return mySerializer.Deserialize(ms);
        }

        public static object DeserializeFromString(string objectData, Type type)
        {
            var serializer = new XmlSerializer(type);
            object result = null;

            using (TextReader reader = new StringReader(objectData))
            {
                try
                {
                    result = serializer.Deserialize(reader);
                }
                catch
                {
                }
            }

            return result;
        }

        public static object DeSerialize(string cfgName, Type t)
        {
            return DeSerialize(cfgName, t, false);
        }
        public static object DeSerialize(string cfgName, Type t, bool crypted)
        {
            if (!File.Exists(cfgName)) return null;

            try
            {
                byte[] data = File.ReadAllBytes(cfgName);
                string str = Convert.ToString(data);
                //if (crypted)
                //{
                //  //  ITEncryption crypt = new ITEncryption();
                //    data = crypt.Decrypt(data, GernericSerializer.Pwd);
                //}
                return DeSerialize(data, t);
            }
            catch (Exception exc)
            {
                string logString = String.Format("Fehler beim lesen der Datei {0}.", cfgName);
               // EventLogging.LogConMsg('E', "", logString);
                //EventLogging.LogConMsg('E', "", exc);
            }
            return null;
        }
     }
}
