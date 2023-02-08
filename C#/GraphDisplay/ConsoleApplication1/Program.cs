using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Threading;

//namespace ConsoleApplication2
//{
//    class Program
//    {
//        static SerialPort _serialPort = new SerialPort();
//        static bool _continue = true;
//        public static void Main()
//        {
//            string name;
//            string message;
//            StringComparer stringComparer = StringComparer.OrdinalIgnoreCase;
//            Thread readThread = new Thread(Read);

//            // Create a new SerialPort object with default settings.
//            _serialPort = new SerialPort();

//            _serialPort.PortName = "COM6";
//            _serialPort.BaudRate = 57600;
//            _serialPort.Parity = Parity.None;
//            _serialPort.StopBits = StopBits.One;
//            _serialPort.DataBits = 8;
//            _serialPort.Handshake = Handshake.None;
//            _serialPort.DtrEnable = true;
//            _serialPort.RtsEnable = true;

//            // Set the read/write timeouts
//            _serialPort.ReadTimeout = 500;
//            _serialPort.WriteTimeout = 500;

//            _serialPort.Open();
//            _continue = true;
//            readThread.Start();

//            Console.Write("Name: ");
//            name = Console.ReadLine();
//            //_serialPort.WriteLine("5");
//            Console.WriteLine("Type QUIT to exit");

//            while (_continue)
//            {
//                message = Console.ReadLine();

//                if (stringComparer.Equals("quit", message))
//                {
//                    _continue = false;
//                }
//                else
//                {
//                    _serialPort.WriteLine("5");
//                        //String.Format("<{0}>: {1}", name, message));
//                }
//            }

//            readThread.Join();
//            _serialPort.Close();
//        }

//        public static void Read()
//        {
//            while (_continue)
//            {
//                try
//                {
//                    string message = _serialPort.ReadLine();
//                    Console.WriteLine(message);
//                }
//                catch (TimeoutException) { }
//            }
//        }
//    }
//}
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Threading;

namespace ConsoleApplication2
{
    class Program
    {
        static SerialPort port = null;
        
        static void Main(string[] args)
        {

            Thread readThread = new Thread(ReadFunction);
            //readThread.Start();
            ReadFunction();
            while (true)
            { 
            string str = Console.ReadLine();
            port.WriteLine(str);
                }
            Console.WriteLine("Press any key to continue...");
            Console.WriteLine();
            Console.ReadKey();
            port.Close();
        }
        
        static void ReadFunction()
        {
            int buffersize = 1024;
            port = new SerialPort("COM6", 57600);
            port.DtrEnable = true;

            port.DataReceived += port_DataReceived;

            // To be safe, set the buffer size as double the size you want to read once
            // This is for the case when the system is busy and delays the event processing
            port.ReadBufferSize = 2 * buffersize;

            // DataReceived event will be fired when in the receive buffer
            // are at least ReceivedBytesThreshold bytes
            port.ReceivedBytesThreshold = buffersize;
            port.Open();


            
            port.DiscardInBuffer();
            while (true)
            {
                Thread.Sleep(100);
                break;
            }
        }
        static void port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            // The event will also be fired for EofChar (byte 0x1A), ignore it
            if (e.EventType == SerialData.Eof)
                return;
            string indata = port.ReadLine();
            Console.WriteLine(indata);
            return;
            // Read the BytesToRead value, 
            // don't assume it's exactly ReceivedBytesThreshold
            byte[] buffer = new byte[port.BytesToRead];
            port.Read(buffer, 0, buffer.Length);
            string result = System.Text.Encoding.UTF8.GetString(buffer);
            Console.Write(result);

            // ... Process the buffer ...
        }
        static void StartProc()
        {
        }
        static void sp_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            string indata = sp.ReadExisting();
            Console.WriteLine("Data Received:");
            Console.Write(indata);
        }
    }
}