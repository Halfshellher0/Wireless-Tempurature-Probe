using System;
using System.Net.Sockets;

namespace ESP_Server
{
    class Program
    {
        static private void StartServer()
        {
            TcpListener server = new TcpListener(System.Net.IPAddress.Any, 8888);
            //Start the server
            server.Start();

            Console.WriteLine("Server started. Waiting for connection...");
            //Block execution until a new client is connected.
            TcpClient newClient = server.AcceptTcpClient();

            Console.WriteLine("New client connected!");

            //Checking if new data is available to be read on the network stream
            if (newClient.Available > 0)
            {
                //Initializing a new byte array the size of the available bytes on the network stream
                byte[] readBytes = new byte[newClient.Available];
                //Reading data from the stream
                newClient.GetStream().Read(readBytes, 0, newClient.Available);
                //Converting the byte array to string
                String str = System.Text.Encoding.ASCII.GetString(readBytes);
                //This should output "Hello world" to the console window
                Console.WriteLine(str);
            }
        }

        static void Main(string[] args)
        {
            StartServer();
            Console.WriteLine("Hello World!");
        }
    }
}
