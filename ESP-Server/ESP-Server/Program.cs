using System;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using Topshelf;

namespace ESP_Server
{
    class Program
    {
        //Main function
        static void Main(string[] args)
        {
            HostFactory.Run(x => x.Service<TopShelfServiceImpl>());
        }

    }
}
