
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace GraficFilterDisplay
{
    public delegate bool NewSampleDetected(int graphNo, double value, bool resetCursor);
    public delegate bool NewMessageReceived(string newMsg);

    public class SamplesDispatcher
    {
        public int MaxSampleIndex { get; set; } = 10;
        public int MaxGraphCount { get; set; }
        public int[][] relationMatrix = null;

        public SamplesDispatcher()
        {
        }
        public static SamplesDispatcher Clone(SamplesDispatcher src)
        {
            SamplesDispatcher newSd = new SamplesDispatcher(src.MaxSampleIndex);
            newSd.MaxGraphCount = src.MaxGraphCount;
            for (int i = 0; i < src.MaxSampleIndex; i++)
            {
                newSd.Set(i, src.Disp(i));
            }
            return newSd;
        }

        public  SamplesDispatcher(int maxGraphps)
        {
            MaxGraphCount = maxGraphps;
            Reset();
        }

        public void Reset()
        {
            relationMatrix = new int[MaxSampleIndex][];
            for (int i = 0; i < MaxSampleIndex; i++)
            {
                Set(i, new int[] { (i % MaxGraphCount) });
            }
        }

        public int[] Disp(int sampleID)
        {
            if (sampleID >= MaxSampleIndex) return new int[] { 0 };
            if (sampleID < 0) return new int[] { 0 };
            return relationMatrix[sampleID];
        }

        public bool Set(int sampleID, int[] graphIds)
        {
            if (relationMatrix == null)
            {
                if (MaxGraphCount == 0) MaxGraphCount = 10;
                relationMatrix = new int[MaxSampleIndex][];
            }
            if (sampleID >= MaxSampleIndex) return false;
            
            relationMatrix[sampleID] = graphIds.Clone() as int[];

            return true;
        }

    }

    public class FunctionGenerator
    {

        public NewSampleDetected OnNewSampleDetected = null;

        public double Amplitude { get; set; }
        public double Frequency { get; set; }
        public double Samplerate { get; set; }
        public int MaxSamples { get; set; } 
        public int SampleID { get; set; } = 0;

        public void Calculate()
        {
            if (OnNewSampleDetected == null) return;
            bool firstTime = true;

            double x = 0;
            double delta = 2 * Math.PI / (double)Samplerate * Frequency;
            for (int i = 0; i < MaxSamples; i++)
            {
                x += delta;
                double val = Math.Sin(x) * Amplitude;
                OnNewSampleDetected?.Invoke(SampleID, val, firstTime);
                if (firstTime) firstTime = false;
            }
        }
    }




}