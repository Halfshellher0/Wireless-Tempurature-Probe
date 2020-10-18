using System;
using System.Net.Sockets;
using System.Text;
using System.Threading;

namespace ESP_Server
{
    class Program
    {
        //Main function
        static void Main(string[] args)
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
            Thread.Sleep(50);

            int previousByteCount = client.Available;
            int currentByteCount;
            int endCount = 0;

            //Wait until new bytes stop coming in before recieving message.
            while (endCount < 5)
            {
                Thread.Sleep(1);
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
                //This should output "Hello world" to the console window
                Console.WriteLine(str);

                client.Client.Send(Encoding.ASCII.GetBytes("Thanks!"));
            }

        }


    }
}
