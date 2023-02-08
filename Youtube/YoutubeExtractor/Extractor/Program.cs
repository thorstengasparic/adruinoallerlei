using RTExtractor;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Extractor
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length != 2)
            {
                Console.WriteLine("Usage: Extractor <storepath> <rtNumber>");
                return;
            }


            string url = "http://cdn2b.public.youporn.phncdn.com/201609/28/13102189/720p_1500k_13102189/YouPorn%20-%20My%20Dirty%20Hobby%20Bibixxx%20der%20anal%20Milf%20Dreier.mp4?rs=200&ri=1200&s=1476430900&e=1476445300&h=e24938b7151b43a96bcf9a64ee38536a";
            RTDownloader.LoadFromStream(url, @"c:\tmp\test.mp4");
            //rt.Execute();
            RTDownloader rt = new RTDownloader();
            rt.NewNumbers.Add(args[1]);
            rt.SavePath = args[0];
            rt.Url = "http://www.redtube.com/";

            rt.DownloadProgressChanged += (sender, pArgs) => Console.WriteLine(pArgs.ProgressPercentage + " % curspeed:" + pArgs.DownloadSpeed + " totalspeed:" + pArgs.TotalDownloadSpeed);
            while (rt.NewNumbers.Count > 0)
                
                rt.Execute();
        }
    }
}
