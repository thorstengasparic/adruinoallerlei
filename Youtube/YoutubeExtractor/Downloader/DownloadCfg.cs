using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Downloader
{
   
    public enum DownloadStatus { Queued, InProgress, Done, Error };
    public class DownloadItem
    {
        public string URL { get; set; }
        public string Info { get; set; }
        public bool ExtractMP3 { get; set; }
        public DownloadStatus Status { get; set; }
        public override string ToString()
        {
            return URL + ": " + Status.ToString()+ " - " +Info; 
        }
    }

    public class DownloadCfg
    {
        public DownloadCfg()
        {
            DownloadList = new List<DownloadItem>();
            Path = "";
        }
        public string Path { get; set; }
        public bool Autostart {get;set;}
        public bool CheckClipboard { get; set; }
        public List<DownloadItem> DownloadList { get; set; }
        public bool ExtractMP3 { get; set; }
    }
}
