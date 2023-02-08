using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Text.RegularExpressions;

namespace RTExtractor
{
    public class ProgressEventArgs : EventArgs
    {
        public ProgressEventArgs(double progressPercentage, double DownloadSpeed, double totalDownloadSpeed)
        {
            this.ProgressPercentage = progressPercentage;
            this.DownloadSpeed = DownloadSpeed;
            this.TotalDownloadSpeed = totalDownloadSpeed;
        }

        /// <summary>
        /// Gets or sets a token whether the operation that reports the progress should be canceled.
        /// </summary>
        public bool Cancel { get; set; }

        /// <summary>
        /// Gets the progress percentage in a range from 0.0 to 100.0.
        /// </summary>
        public double ProgressPercentage { get; private set; }
        public double DownloadSpeed { get; private set; }
        public double TotalDownloadSpeed { get; private set; }
    }
    public class RTDownloader
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="Downloader"/> class.
        /// </summary>
        /// <param name="video">The video to download/convert.</param>
        /// <param name="savePath">The path to save the video/audio.</param>
        /// /// <param name="bytesToDownload">An optional value to limit the number of bytes to download.</param>
        /// <exception cref="ArgumentNullException"><paramref name="video"/> or <paramref name="savePath"/> is <c>null</c>.</exception>
        //public RTDownloader(string url, string savePath, int? bytesToDownload = null)
        //{
        //    if (url == null)
        //        throw new ArgumentNullException("url");

        //    if (savePath == null)
        //        throw new ArgumentNullException("savePath");

        //    this.Url = url;
        //    this.SavePath = savePath;
        //    this.BytesToDownload = bytesToDownload;
        //}

        /// <summary>
        /// Occurs when the download finished.
        /// </summary>
        public event EventHandler DownloadFinished;

        /// <summary>
        /// Occurs when the download is starts.
        /// </summary>
        public event EventHandler DownloadStarted;

        /// <summary>
        /// Gets the number of bytes to download. <c>null</c>, if everything is downloaded.
        /// </summary>
        public int? BytesToDownload { get; private set; }

        /// <summary>
        /// Gets the path to save the video/audio.
        /// </summary>
        public string SavePath { get;  set; }

        /// <summary>
        /// Gets the video to download/convert.
        /// </summary>
        public string Url { get;  set; }


        protected void OnDownloadFinished(EventArgs e)
        {
            if (this.DownloadFinished != null)
            {
                this.DownloadFinished(this, e);
            }
        }

        protected void OnDownloadStarted(EventArgs e)
        {
            if (this.DownloadStarted != null)
            {
                this.DownloadStarted(this, e);
            }
        }

        string GetDownloadURL_RT(string url)
        {
            JArray arr = LoadJson_RT(url);
            if (arr == null) return null;
            return Url_RT(arr);
        }
        public string DownloadString(string url)
        {
            using (var client = new WebClient())
            {
                client.Encoding = System.Text.Encoding.UTF8;
                return client.DownloadString(url);
            }
        }
        public List<string> NewNumbers = new List<string>();
        string pageSource;
        JArray LoadJson_RT(string url)
        {
            pageSource = DownloadString(url);
            //string pageSource = File.ReadAllText(@"c:\tmp\test.html");


            //string pageSource = "$rt.bootstrap.push([{ \"func\":\"initDefault\",\"params\":[]    },{\"func\":\"RTA\",\"params\":[\"www.redtube.com\",\"stats_js_index%2Cstats_js_watch\"]},{\"func\":\"PHBar\",\"params\":{\"global\":\"ph_bar\",\"site\":\"redtube\",\"element\":\"PornhubNetworkBar\",\"gay\":false,\"tablet\":false,\"css\":\"\n\t\t\tbody\n\t\t\t{ background-position: 0 24px;}\n\n\t\t\tdiv.bar_body.tablet div.bar_items div.links a:hover,\n\t\t\t.alternateHead:hover,\n\t\t\t.alternateMenu a:hover,\n\t\t\t.moreHead:hover,\n\t\t\t.moreMenu a:hover{\n\t\t\t\tcolor: #A1A1A1;\n\t\t\t}\n\n\t\t\tdiv.bar_body.desktop div.bar_items\n\t\t\t\t{ width:973px;}\n\n\t\t\t@media only screen and (min-width: 1600px) {\n\t\t\t\tdiv.bar_body.desktop div.bar_items\n\t\t\t\t\t{ width:973px;}\n\t\t\t}\n\t\t\"}},{\"func\":\"navigation\",\"params\":[\"click\"]},{\"func\":\"dropDown\",\"params\":[\".community-options-link\"]},{\"func\":\"initGATracking\",\"params\":[\".header-link, .community-options-dropdown li a\",\"Header\",\"Click\"]},{\"func\":\"initSubscriptionPanel\",\"params\":[]},{\"func\":\"changeLogoForHoliday\",\"params\":[]},{\"func\":\"initNotificationConfig\",\"params\":[]},{\"func\":\"initRingBell\",\"params\":[]},{\"func\":\"initNotificationHooks\",\"params\":[]},{\"func\":\"autoComplete\",\"params\":[0,\"0\",false,\"stats_page_suggestion_use\"]},{\"func\":\"initChannelDropDown\",\"params\":[0]},{\"func\":\"initShowMoreRecommendedSidebar\",\"params\":[]},{\"func\":\"initVideoPage\",\"params\":[1681334,false]},{\"func\":\"unsubscribeRollOver\",\"params\":[]},{\"func\":\"videoView\",\"params\":[1681334,\"1475585490|d549eb8a24ef4eabc6b7627d6060cf95c6f0a219\",\"42c4a753aeb807855a2e6d699eab0a245da16e35\"]},{\"func\":\"initVideoDownload\",\"params\":[1681334,2,{\"1080p\":\"\",\"hd\":\"http:\/\/vida.lsw.hd.redtubefiles.com\/videos\/0001681\/_hd\/1681334.mp4?st=6pjsTeDwMeYRBJov6gC9XQ&e=1475589060&rs=126&ri=1400&download=1\",\"480p\":\"http:\/\/vida.lsw.redtubefiles.com\/videos\/0001681\/_mp4\/1681334.mp4?st=TyIHRKlyqeEkgPhx4k89cw&e=1475589060&rs=56&ri=1400&download=1\",\"mobile\":\"http:\/\/vida.lsw.redtubefiles.com\/videos\/0001681\/_andr\/1681334.mp4?st=wXHEIgPl_UqHdr16kplcbA&e=1475589060&rs=56&ri=1400&download=1\"}]},{\"func\":\"initRatingThumbs\",\"params\":[\".like-dislike-box\",1,1681334]},{\"func\":\"initShareEmbedBoxArrow\",\"params\":[]},{\"func\":\"initVideoTitle\",\"params\":[null,1,1681334]},{\"func\":\"loadLangLabel\",\"params\":[\"video.sidebar.recommended\",\"Recommended videos\"]},{\"func\":\"initVideoDetails\",\"params\":[]},{\"func\":\"initVideoLoginHooks\",\"params\":[1681334,1]},{\"func\":\"initVideoDetailsTabber\",\"params\":[1681334]},{\"func\":\"activateAddComment\",\"params\":[1681334,\"You must type in a comment.\",\"#comment-form\"]},{\"func\":\"selectCommentsSorting\",\"params\":[\"commentSortingDropdown\",\"video_id\",1681334]},{\"func\":\"initPornstarVote\",\"params\":[\"video\",1681334]},{\"func\":\"generateVideoThumbsJSMap\",\"params\":[{\"1689730\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1700791\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1697710\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1690618\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1695913\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1696542\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1695435\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1721527\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\"}]},{\"func\":\"generateVideoThumbsJSMap\",\"params\":[{\"1621740\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1701085\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1700845\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1577770\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1673799\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1577286\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1544507\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1644667\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\"}]},{\"func\":\"generateVideoThumbsJSMap\",\"params\":[{\"1544507\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1689730\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1690618\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1668954\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1701085\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1677129\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1670050\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1375165\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\"}]},{\"func\":\"generateVideoThumbsJSMap\",\"params\":[{\"1210658\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"0425403\":\"0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"0452686\":\"0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1174239\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"0520258\":\"0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"0406026\":\"0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0\",\"1350728\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0\",\"0501005\":\"0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"0395586\":\"0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0\",\"1423175\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\"}]},{\"func\":\"initVideoThumbs\",\"params\":\"video-thumb\"},{\"func\":\"initComments\",\"params\":{\"1443770\":{\"iCommentID\":\"1443770\",\"iObjectID\":\"1681334\",\"iAuthorID\":\"807392\",\"bIsDeleted\":false,\"bUserPage\":false},\"1447655\":{\"iCommentID\":\"1447655\",\"iObjectID\":\"1681334\",\"iAuthorID\":\"453570\",\"bIsDeleted\":false,\"bUserPage\":false},\"1445684\":{\"iCommentID\":\"1445684\",\"iObjectID\":\"1681334\",\"iAuthorID\":\"5029716\",\"bIsDeleted\":false,\"bUserPage\":false},\"1447051\":{\"iCommentID\":\"1447051\",\"iObjectID\":\"1681334\",\"iAuthorID\":\"533591\",\"bIsDeleted\":false,\"bUserPage\":false},\"1470618\":{\"iCommentID\":\"1470618\",\"iObjectID\":\"1681334\",\"iAuthorID\":\"5147965\",\"bIsDeleted\":false,\"bUserPage\":false},\"1469753\":{\"iCommentID\":\"1469753\",\"iObjectID\":\"1681334\",\"iAuthorID\":\"1475997\",\"bIsDeleted\":false,\"bUserPage\":false},\"1459362\":{\"iCommentID\":\"1459362\",\"iObjectID\":\"1681334\",\"iAuthorID\":\"3258967\",\"bIsDeleted\":false,\"bUserPage\":false},\"1448304\":{\"iCommentID\":\"1448304\",\"iObjectID\":\"1681334\",\"iAuthorID\":\"4538891\",\"bIsDeleted\":false,\"bUserPage\":false},\"1469622\":{\"iCommentID\":\"1469622\",\"iObjectID\":\"1681334\",\"iAuthorID\":\"860812\",\"bIsDeleted\":false,\"bUserPage\":false},\"1446851\":{\"iCommentID\":\"1446851\",\"iObjectID\":\"1681334\",\"iAuthorID\":\"4626686\",\"bIsDeleted\":false,\"bUserPage\":false},\"1446849\":{\"iCommentID\":\"1446849\",\"iObjectID\":\"1681334\",\"iAuthorID\":\"4626686\",\"bIsDeleted\":false,\"bUserPage\":false}}},{\"func\":\"initWarningOnExit\",\"params\":[\"comment\",\"If you leave this page, your comment will be lost.\"]},{\"func\":\"initHashLookup\",\"params\":[]},{\"func\":\"initJSErrorHandler\",\"params\":[\"\\\"aje001\\\"\\\",\"\\\"aje021\\\"\"]},{\"func\":\"cacheThumbs\",\"params\":[[]]},{\"func\":\"renderAdblockAds\",\"params\":[]}]);	$rt.bootstrap.start();";
            string starttoken = "$rt.bootstrap.push(";
            string endtoken = ");";

            int idx = pageSource.IndexOf(starttoken) + starttoken.Length;
            string extractedJson = pageSource.Substring(idx);
            idx = extractedJson.IndexOf(endtoken);
            //string extractedJson = "{" + pageSource.Substring(0, idx) + "}";
            extractedJson = extractedJson.Substring(0, idx);
            //var dataRegex = new Regex(@\"ytplayer\.config\s*=\s*(\{.+?\});\", RegexOptions.Multiline);
            //string extractedJson = dataRegex.Match(pageSource).Result(\"$1\");
            JArray reArr = JArray.Parse(extractedJson);

            string fNameToken = "videoTitle:";
            idx = pageSource.IndexOf(fNameToken) + fNameToken.Length;
            string fname = pageSource.Substring(idx);
            string[] farr = fname.Split('\"');
            Filename = farr[1];
            //string fNale = "{\"func\":\"fileattrib\",\"name\":\""+ farr[1] + "\"}";
            //JObject newJObj = new JObject(fNale);
            //reArr.Add(newJObj);


            string idsToken = "class=\"video-duration\" onclick=\"window.location.href ='/";
            extractedJson = pageSource;
            if (CrawlerEnabled)
            {
                while (true)
                {
                    idx = extractedJson.IndexOf(idsToken);
                    if (idx < 0) break;
                    idx += idsToken.Length;
                    extractedJson = extractedJson.Substring(idx);
                    farr = extractedJson.Split('\'');
                    string str = farr[0];
                    if (!NewNumbers.Contains(str) && NewNumbers.Count < 20)
                        NewNumbers.Add(str);
                }
            }
            
            return reArr;
        }
        string Filename = "";

        string PrepareURL(string url)
        {
            if (!url.StartsWith("http:"))
            {
                url = "http:" + url;
            }
                //return url.Split('?')[0];
            return url;
        }

        string Url_RT(JArray jArray)
        {
            foreach (JObject jObj in jArray)
            {

                if (jObj["func"].ToString() == "initVideoDownload")
                {
                    JArray arr = jObj["params"] as JArray;
                    JObject jUrl = arr[2] as JObject;
                    string retUrl = "";
                    try
                    {
                        retUrl = jUrl["1080p"].ToString();
                        if (retUrl.Trim().Length > 0) return PrepareURL(retUrl);
                    }
                    catch { }
                    try
                    {
                        retUrl = jUrl["hd"].ToString();
                        if (retUrl.Trim().Length > 0) return PrepareURL(retUrl);
                    }
                    catch { }
                    try
                    {
                        retUrl = jUrl["480p"].ToString();
                        if (retUrl.Trim().Length > 0) return PrepareURL(retUrl);
                    }
                    catch { }
                    throw new Exception("No download url found: " + jObj.ToString());
                }
            }
            throw new Exception("initVideoDownload funtion not found");
        }
        public bool CrawlerEnabled = false;
        public bool StopProcessing = false;
        public event EventHandler<ProgressEventArgs> DownloadProgressChanged;

        string GetDownloadURL_YP(string url)
        {
            pageSource = DownloadString(url);
            //string pageSource = File.ReadAllText(@"c:\tmp\test.html");


            //string pageSource = "$rt.bootstrap.push([{ \"func\":\"initDefault\",\"params\":[]    },{\"func\":\"RTA\",\"params\":[\"www.redtube.com\",\"stats_js_index%2Cstats_js_watch\"]},{\"func\":\"PHBar\",\"params\":{\"global\":\"ph_bar\",\"site\":\"redtube\",\"element\":\"PornhubNetworkBar\",\"gay\":false,\"tablet\":false,\"css\":\"\n\t\t\tbody\n\t\t\t{ background-position: 0 24px;}\n\n\t\t\tdiv.bar_body.tablet div.bar_items div.links a:hover,\n\t\t\t.alternateHead:hover,\n\t\t\t.alternateMenu a:hover,\n\t\t\t.moreHead:hover,\n\t\t\t.moreMenu a:hover{\n\t\t\t\tcolor: #A1A1A1;\n\t\t\t}\n\n\t\t\tdiv.bar_body.desktop div.bar_items\n\t\t\t\t{ width:973px;}\n\n\t\t\t@media only screen and (min-width: 1600px) {\n\t\t\t\tdiv.bar_body.desktop div.bar_items\n\t\t\t\t\t{ width:973px;}\n\t\t\t}\n\t\t\"}},{\"func\":\"navigation\",\"params\":[\"click\"]},{\"func\":\"dropDown\",\"params\":[\".community-options-link\"]},{\"func\":\"initGATracking\",\"params\":[\".header-link, .community-options-dropdown li a\",\"Header\",\"Click\"]},{\"func\":\"initSubscriptionPanel\",\"params\":[]},{\"func\":\"changeLogoForHoliday\",\"params\":[]},{\"func\":\"initNotificationConfig\",\"params\":[]},{\"func\":\"initRingBell\",\"params\":[]},{\"func\":\"initNotificationHooks\",\"params\":[]},{\"func\":\"autoComplete\",\"params\":[0,\"0\",false,\"stats_page_suggestion_use\"]},{\"func\":\"initChannelDropDown\",\"params\":[0]},{\"func\":\"initShowMoreRecommendedSidebar\",\"params\":[]},{\"func\":\"initVideoPage\",\"params\":[1681334,false]},{\"func\":\"unsubscribeRollOver\",\"params\":[]},{\"func\":\"videoView\",\"params\":[1681334,\"1475585490|d549eb8a24ef4eabc6b7627d6060cf95c6f0a219\",\"42c4a753aeb807855a2e6d699eab0a245da16e35\"]},{\"func\":\"initVideoDownload\",\"params\":[1681334,2,{\"1080p\":\"\",\"hd\":\"http:\/\/vida.lsw.hd.redtubefiles.com\/videos\/0001681\/_hd\/1681334.mp4?st=6pjsTeDwMeYRBJov6gC9XQ&e=1475589060&rs=126&ri=1400&download=1\",\"480p\":\"http:\/\/vida.lsw.redtubefiles.com\/videos\/0001681\/_mp4\/1681334.mp4?st=TyIHRKlyqeEkgPhx4k89cw&e=1475589060&rs=56&ri=1400&download=1\",\"mobile\":\"http:\/\/vida.lsw.redtubefiles.com\/videos\/0001681\/_andr\/1681334.mp4?st=wXHEIgPl_UqHdr16kplcbA&e=1475589060&rs=56&ri=1400&download=1\"}]},{\"func\":\"initRatingThumbs\",\"params\":[\".like-dislike-box\",1,1681334]},{\"func\":\"initShareEmbedBoxArrow\",\"params\":[]},{\"func\":\"initVideoTitle\",\"params\":[null,1,1681334]},{\"func\":\"loadLangLabel\",\"params\":[\"video.sidebar.recommended\",\"Recommended videos\"]},{\"func\":\"initVideoDetails\",\"params\":[]},{\"func\":\"initVideoLoginHooks\",\"params\":[1681334,1]},{\"func\":\"initVideoDetailsTabber\",\"params\":[1681334]},{\"func\":\"activateAddComment\",\"params\":[1681334,\"You must type in a comment.\",\"#comment-form\"]},{\"func\":\"selectCommentsSorting\",\"params\":[\"commentSortingDropdown\",\"video_id\",1681334]},{\"func\":\"initPornstarVote\",\"params\":[\"video\",1681334]},{\"func\":\"generateVideoThumbsJSMap\",\"params\":[{\"1689730\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1700791\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1697710\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1690618\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1695913\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1696542\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1695435\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1721527\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\"}]},{\"func\":\"generateVideoThumbsJSMap\",\"params\":[{\"1621740\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1701085\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1700845\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1577770\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1673799\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1577286\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1544507\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1644667\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\"}]},{\"func\":\"generateVideoThumbsJSMap\",\"params\":[{\"1544507\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1689730\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1690618\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1668954\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1701085\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1677129\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1670050\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1375165\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\"}]},{\"func\":\"generateVideoThumbsJSMap\",\"params\":[{\"1210658\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"0425403\":\"0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"0452686\":\"0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"1174239\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"0520258\":\"0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"0406026\":\"0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0\",\"1350728\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0\",\"0501005\":\"0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\",\"0395586\":\"0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0\",\"1423175\":\"1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1\"}]},{\"func\":\"initVideoThumbs\",\"params\":\"video-thumb\"},{\"func\":\"initComments\",\"params\":{\"1443770\":{\"iCommentID\":\"1443770\",\"iObjectID\":\"1681334\",\"iAuthorID\":\"807392\",\"bIsDeleted\":false,\"bUserPage\":false},\"1447655\":{\"iCommentID\":\"1447655\",\"iObjectID\":\"1681334\",\"iAuthorID\":\"453570\",\"bIsDeleted\":false,\"bUserPage\":false},\"1445684\":{\"iCommentID\":\"1445684\",\"iObjectID\":\"1681334\",\"iAuthorID\":\"5029716\",\"bIsDeleted\":false,\"bUserPage\":false},\"1447051\":{\"iCommentID\":\"1447051\",\"iObjectID\":\"1681334\",\"iAuthorID\":\"533591\",\"bIsDeleted\":false,\"bUserPage\":false},\"1470618\":{\"iCommentID\":\"1470618\",\"iObjectID\":\"1681334\",\"iAuthorID\":\"5147965\",\"bIsDeleted\":false,\"bUserPage\":false},\"1469753\":{\"iCommentID\":\"1469753\",\"iObjectID\":\"1681334\",\"iAuthorID\":\"1475997\",\"bIsDeleted\":false,\"bUserPage\":false},\"1459362\":{\"iCommentID\":\"1459362\",\"iObjectID\":\"1681334\",\"iAuthorID\":\"3258967\",\"bIsDeleted\":false,\"bUserPage\":false},\"1448304\":{\"iCommentID\":\"1448304\",\"iObjectID\":\"1681334\",\"iAuthorID\":\"4538891\",\"bIsDeleted\":false,\"bUserPage\":false},\"1469622\":{\"iCommentID\":\"1469622\",\"iObjectID\":\"1681334\",\"iAuthorID\":\"860812\",\"bIsDeleted\":false,\"bUserPage\":false},\"1446851\":{\"iCommentID\":\"1446851\",\"iObjectID\":\"1681334\",\"iAuthorID\":\"4626686\",\"bIsDeleted\":false,\"bUserPage\":false},\"1446849\":{\"iCommentID\":\"1446849\",\"iObjectID\":\"1681334\",\"iAuthorID\":\"4626686\",\"bIsDeleted\":false,\"bUserPage\":false}}},{\"func\":\"initWarningOnExit\",\"params\":[\"comment\",\"If you leave this page, your comment will be lost.\"]},{\"func\":\"initHashLookup\",\"params\":[]},{\"func\":\"initJSErrorHandler\",\"params\":[\"\\\"aje001\\\"\\\",\"\\\"aje021\\\"\"]},{\"func\":\"cacheThumbs\",\"params\":[[]]},{\"func\":\"renderAdblockAds\",\"params\":[]}]);	$rt.bootstrap.start();";
            string starttoken = "sources: ";
            string endtoken = "videoUrl:";

            int idx = pageSource.IndexOf(starttoken) + starttoken.Length;
            string extractedJson = pageSource.Substring(idx);
            idx = extractedJson.IndexOf(endtoken);
            extractedJson = extractedJson.Substring(0, idx);
            extractedJson = extractedJson.TrimEnd(new char[] { ' ', ',','\n', '\r', '\t' });

            JObject reArr = JObject.Parse(extractedJson);

            string[] token = url.Split(new char[] { '/' }, StringSplitOptions.RemoveEmptyEntries);
            Filename = token[token.Length - 1];
            //for (int i = reArr.Count-1; i>0; i--)
            {
                try
                {
                    string retUrl = reArr["1080_60"].ToString();
                    if (retUrl.Trim().Length > 0) return PrepareURL(retUrl);
                }
                catch{ }
                try
                {
                    string retUrl = reArr["1080"].ToString();
                    if (retUrl.Trim().Length > 0) return PrepareURL(retUrl);
                }
                catch { }
                try
                {
                    string retUrl = reArr["720_60"].ToString();
                    if (retUrl.Trim().Length > 0) return PrepareURL(retUrl);
                }
                catch { }
                try
                {
                    string retUrl = reArr["720"].ToString();
                    if (retUrl.Trim().Length > 0) return PrepareURL(retUrl);
                }
                catch { }
                try
                {
                    string retUrl = reArr["480"].ToString();
                    if (retUrl.Trim().Length > 0) return PrepareURL(retUrl);
                }
                catch { }
                
            }
            throw new Exception("initVideoDownload funtion not found");
            return "";
        }

        string GetDownloadURL(string url)
        {
            if (url.ToLower().Contains(".redtube."))
                return GetDownloadURL_RT(url);

            if (url.ToLower().Contains(".youporn."))
                return GetDownloadURL_YP(url);

            return "";
        }

        public bool Execute()
        {
            this.OnDownloadStarted(EventArgs.Empty);
            string dUrl = Url;
            if (CrawlerEnabled)
            {
                dUrl = Url + NewNumbers[0];
                NewNumbers.RemoveAt(0);
            }
            var request = (HttpWebRequest)WebRequest.Create(GetDownloadURL(dUrl));
            
            //if (this.BytesToDownload.HasValue)
            //{
            //    //request.AddRange(0, this.BytesToDownload.Value - 1);
            //}
           
            string filename = Path.Combine(this.SavePath , Filename + ".mp4");
            string filenameTmp = Path.Combine(this.SavePath, Filename + ".mp4.tmp");
            if (CrawlerEnabled) if (File.Exists(filename)) return true;
            //if (filename.StartsWith("VIXEN")) return;
            //if (filename.StartsWith("EroticaX ")) return;
            // the following code is alternative, you may implement the function after your needs
            double lastPercent = 0.0;
            double lastSpeed = 0.0;
            double totalDownloadSpeed = 0.0;
            DateTime startTotal = DateTime.Now;
            try {
                using (WebResponse response = request.GetResponse())
                {
                 
                    if ((response.ContentLength > 60000000) || (!CrawlerEnabled))
                    {

                        using (Stream source = response.GetResponseStream())
                        {
                            if (CrawlerEnabled)
                                File.WriteAllText(Path.Combine(this.SavePath, Filename + ".html"), pageSource);
                            using (FileStream target = File.Open(filenameTmp, FileMode.Create, FileAccess.Write))
                            {
                                var buffer = new byte[1024*4];
                                bool cancel = false;
                                int bytes;
                                int copiedBytes = 0;
                                DateTime startT = DateTime.Now;
                                double dSpeed = 0;
                                while (!cancel && (bytes = source.Read(buffer, 0, buffer.Length)) > 0)
                                {
                                    if (StopProcessing) return true;
                                    target.Write(buffer, 0, bytes);

                                    DateTime startE = DateTime.Now;
                                    double t = startE.Subtract(startT).TotalMilliseconds;
                                    if (t != 0)
                                    {
                                        dSpeed = Math.Round(bytes / t * 1000);
                                    }

                                    copiedBytes += bytes;
                                    t = startE.Subtract(startTotal).TotalMilliseconds;
                                    if (t != 0)
                                    {
                                        totalDownloadSpeed = Math.Round(copiedBytes / t * 1000);
                                    }

                                    double percent = Math.Round((copiedBytes * 1.0 / response.ContentLength) * 100, 0);
                                    if (lastPercent != percent || (Math.Abs(lastSpeed - dSpeed) > 50000))
                                    {
                                        var eventArgs = new ProgressEventArgs(percent, dSpeed, totalDownloadSpeed);
                                        if (this.DownloadProgressChanged != null)
                                        {
                                            this.DownloadProgressChanged(this, eventArgs);

                                            if (eventArgs.Cancel)
                                            {
                                                cancel = true;
                                            }
                                        }
                                        lastPercent = percent;
                                        lastSpeed = dSpeed;
                                    }
                                    startT = DateTime.Now;
                                }
                            }
                            File.Move(filenameTmp, filename);
                        }
                    }
                }
            }
            catch (Exception ex){ return false; }

            OnDownloadFinished(EventArgs.Empty);
            return true;
        }

        public static bool LoadFromStream(string dUrl, string outpath)
        {
            var request = (HttpWebRequest)WebRequest.Create(dUrl);
            try
            {
                using (WebResponse response = request.GetResponse())
                {
                    using (Stream source = response.GetResponseStream())
                    {
                            
                        using (FileStream target = File.Open(outpath, FileMode.Create, FileAccess.Write))
                        {
                            var buffer = new byte[1024 * 4];
                            bool cancel = false;
                            int bytes;
                            while (!cancel && (bytes = source.Read(buffer, 0, buffer.Length)) > 0)
                            {
                                target.Write(buffer, 0, bytes);
                            }
                        }
                    }
                }

            }
            catch (Exception ex) { return false; }
            return true;
        }
    }
}
