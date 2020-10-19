using System;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using Topshelf;

namespace ESP_Server
{
    public class TopShelfServiceImpl : ServiceControl
    {
        public bool Start(HostControl hostControl)
        {
            ThreadPool.QueueUserWorkItem(StartListener);
            return true;

        }

        public bool Stop(HostControl hostControl)
        {
            return true;
        }

        private static void StartListener(object obj)
        {
            TcpListener listener = new TcpListener(System.Net.IPAddress.Any, 8888);
            TcpClient client;

            //Start the server
            listener.Start();

            while (true) // Add your exit flag here
            {
                client = listener.AcceptTcpClient();
                ThreadPool.QueueUserWorkItem(ThreadProc, client);
            }
        }

        //Process that is run on a seperate thread when a new client is communicating.
        private static void ThreadProc(object clientObj)
        {
            //New Client Conneted
            var client = (TcpClient)clientObj;


            int previousByteCount = client.Available;
            int currentByteCount;
            int endCount = 0;


            //Wait until new bytes stop coming in before recieving message.
            while (endCount < 15)
            {
                Thread.Sleep(10);
                currentByteCount = client.Available;
                if (previousByteCount == currentByteCount)
                {
                    endCount++;
                }
                else
                {
                    previousByteCount = currentByteCount;
                    endCount = 0;
                }
            }


            //Recieve Message
            currentByteCount = client.Available;
            if (currentByteCount > 0)
            {
                //Initializing a new byte array the size of the available bytes on the network stream
                byte[] readBytes = new byte[currentByteCount];
                //Reading data from the stream
                client.GetStream().Read(readBytes, 0, currentByteCount);
                //Converting the byte array to string
                String str = Encoding.ASCII.GetString(readBytes);
                //This should output "Hello world" to the console window.                
                string[] splitter = str.Split(',');
                if (splitter.Length > 1)
                {
                    string sensorId = splitter[0];
                    double tempurature = Convert.ToDouble(splitter[1]);
                    DBController db = new DBController();
                    db.LogTempurature(sensorId, tempurature);
                    Console.WriteLine(str);
                }
                

                client.Client.Send(Encoding.ASCII.GetBytes("Data Recieved"));
            }

        }


    }
}
