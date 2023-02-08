using Infotek.Tools;
using RTExtractor;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using YoutubeExtractor;

namespace Downloader
{
    public partial class Form1 : Form
    {
        static DownloadCfg _downloadCfg = new DownloadCfg();
        static Form1 frm = null;
        static System.Windows.Forms.Timer _timer = new System.Windows.Forms.Timer();
        public Form1()
        {
            frm = this;
            InitializeComponent();
            //           GernericSerializer.Serialize("default.cfg", myObject); 
            _downloadCfg = (DownloadCfg)GernericSerializer.DeSerialize("default.cfg", _downloadCfg.GetType());
            if (_downloadCfg == null)
                _downloadCfg = new DownloadCfg();
            _timer.Tick += _timer_Tick;
            _timer.Interval = 500;
            _timer.Start();
        }

        private void _timer_Tick(object sender, EventArgs e)
        {
            if (_downloadCfg.CheckClipboard)
            {
                string txt = null;
                IDataObject ClipData = Clipboard.GetDataObject();
                if (ClipData != null)
                {
                    if (ClipData.GetDataPresent(DataFormats.Text))
                    {
                        txt = System.Windows.Forms.Clipboard.GetData(DataFormats.Text).ToString();
                        if (txt.Contains("www.youtube") || txt.Contains("www.redtube") || txt.Contains("www.youporn"))
                        {

                            Clipboard.Clear();
                        }
                        else
                            txt = null;
                    }
                }
                if (!string.IsNullOrEmpty(txt))
                {
                    _downloadCfg.DownloadList.Add(new DownloadItem { URL = txt, Status = DownloadStatus.Queued });
                    frm.CfgToGuiThread();
                }
            }
        }

        static void Save()
        {
            GernericSerializer.Serialize("default.cfg", _downloadCfg);
        }
        void CfgToGuiThread()
        {
            if (InvokeRequired)
            {
                Invoke(new MethodInvoker(CfgToGui));
            }
            else {
            // Do Something
            CfgToGui();
            }
        }


        
        void CfgToGui()
        {
            textBoxPfad.Text = _downloadCfg.Path;
            checkBoxAutostartDownload.Checked = _downloadCfg.Autostart;
            checkBoxCheckClipboard.Checked = _downloadCfg.CheckClipboard;
            //listBoxDownloads.Items.Clear();
            //listBoxDownloads.Items.AddRange(_downloadCfg.DownloadList.ToArray());
            listBoxDownloads.DataSource = null;
            listBoxDownloads.DataSource = _downloadCfg.DownloadList;
            Save();
        }

        static Thread _checkListThread = new Thread(CheckListTask);
        private void Form1_Load(object sender, EventArgs e)
        {
            CfgToGui();
            //_checkListThread.SetApartmentState(ApartmentState.STA);

            _checkListThread.Start();
        }

        static bool _stopProcess = false;
        
        static void CheckListTask(Object param)
        {

            while (true)
            {
                if (_stopProcess) return;
                
                if (_downloadCfg.Autostart)
                {
                    if (_downloadCfg.DownloadList.Count > 0)
                    {
                        foreach (DownloadItem dItem in _downloadCfg.DownloadList)
                        {
                            if (dItem.Status == DownloadStatus.Queued)
                            {
                                dItem.Status = DownloadStatus.Queued;
                                Save();
                                Thread downloadThread = new Thread(DownloadTask);
                                downloadThread.Start(dItem);
                            }
                        }
                    }
                }
                Thread.Sleep(1000);
                try
                {
                    frm.Invoke(new MethodInvoker(InvThread));
                }
                catch { return; }
                
            }
        }
        static void InvThread()
        {
            frm.listBoxDownloads.Invalidate(true);
            frm.listBoxDownloads.DataSource = null;
            frm.listBoxDownloads.DataSource = _downloadCfg.DownloadList;
        }

        private static string RemoveIllegalPathCharacters(string path)
        {
            string regexSearch = new string(Path.GetInvalidFileNameChars()) + new string(Path.GetInvalidPathChars());
            var r = new Regex(string.Format("[{0}]", Regex.Escape(regexSearch)));
            return r.Replace(path, "");
        }
        static void DownloadTask(Object param)
        {
            DownloadItem dItem = param as DownloadItem;
            try
            {
                
                dItem.Status = DownloadStatus.InProgress;
                frm.CfgToGuiThread();
                if (dItem.URL.Contains("www.youtube"))
                {
                    IEnumerable<VideoInfo> videoInfos = DownloadUrlResolver.GetDownloadUrls(dItem.URL, false);
                    VideoInfo video = null;
                    try
                    {
                        //if (video == null)
                        //    video = videoInfos.First(info => info.VideoType == VideoType.Mp4 && info.Resolution == 1080);
                        if (video == null)
                            video = videoInfos.First(info => info.VideoType == VideoType.Mp4 && info.Resolution == 720);
                    }catch{ }
                    try
                    {
                        if (video == null)
                            video = videoInfos.First(info => info.VideoType == VideoType.Mp4 && info.Resolution == 480);
                    }
                    catch { }
                    try
                    {
                        if (video == null)
                            video = videoInfos.First(info => info.VideoType == VideoType.Mp4 && info.Resolution == 360);
                    }
                    catch { }
                        
                    /*
                        * If the video has a decrypted signature, decipher it
                        */
                    if (video.RequiresDecryption)
                    {
                        DownloadUrlResolver.DecryptDownloadUrl(video);
                    }

                    /*
                        * Create the video downloader.
                        * The first argument is the video to download.
                        * The second argument is the path to save the video file.
                        */
                    var videoDownloader = new VideoDownloader(video, Path.Combine(_downloadCfg.Path, RemoveIllegalPathCharacters(video.Title) + video.VideoExtension));

                    // Register the ProgressChanged event and print the current progress
                    videoDownloader.DownloadProgressChanged += (sender, args) => { dItem.Info = Math.Round(args.ProgressPercentage).ToString() + "%"; };

                    /*
                        * Execute the video downloader.
                        * For GUI applications note, that this method runs synchronously.
                        */

                    if (videoDownloader.Execute())
                        dItem.Status = DownloadStatus.Done;
                    else
                        dItem.Status = DownloadStatus.Error;
                    frm.CfgToGuiThread();
                }
                else
                {
                    RTDownloader rt = new RTDownloader();
                    rt.SavePath = _downloadCfg.Path;
                    rt.Url = dItem.URL;
                    rt.DownloadProgressChanged += (sender, pArgs) => { dItem.Info = Math.Round(pArgs.ProgressPercentage).ToString() + "% " + pArgs.TotalDownloadSpeed.ToString(); };
                    if (rt.Execute())
                        dItem.Status = DownloadStatus.Done;
                    else
                        dItem.Status = DownloadStatus.Error;
                    frm.CfgToGuiThread();


                }
            }
            catch(Exception ex)
            {
                dItem.Status = DownloadStatus.Error;
                frm.CfgToGuiThread();
            }

        }

        private void checkBoxCheckClipboard_CheckedChanged(object sender, EventArgs e)
        {
            _downloadCfg.CheckClipboard = checkBoxCheckClipboard.Checked;
            Save();
            
        }

        private void checkBoxAutostartDownload_CheckedChanged(object sender, EventArgs e)
        {
            
            _downloadCfg.Autostart = checkBoxAutostartDownload.Checked;
            Save();
        }

        private void textBoxPfad_TextChanged(object sender, EventArgs e)
        {
            if (Directory.Exists(textBoxPfad.Text))
            {
                _downloadCfg.Path = textBoxPfad.Text;
                Save();
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            _stopProcess = true;
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            foreach (object item in listBoxDownloads.SelectedItems)
            {
                _downloadCfg.DownloadList.Remove(item as DownloadItem);
            }
                CfgToGui();
        }

        private void listBoxDownloads_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listBoxDownloads.SelectedItem == null) return;
            textBoxNewURL.Text = (listBoxDownloads.SelectedItem as DownloadItem).URL;
        }

        private void buttonAddUrl_Click(object sender, EventArgs e)
        {
            _downloadCfg.DownloadList.Add(new DownloadItem { URL = textBoxNewURL.Text, Status = DownloadStatus.Queued });
            frm.CfgToGuiThread();
        }
    }
}
