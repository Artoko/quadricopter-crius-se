using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Runtime.Remoting;
using System.Runtime.Remoting.Channels;
using System.Threading;

namespace GroundStation
{
    class Server
    {
        private TcpListener tcpListener;
        private Thread listenThread;
        private bool client_connect = false;
        string write_message = string.Empty;
        public Server()
        {
            this.tcpListener = new TcpListener(IPAddress.Parse("127.0.0.1"), 8001);
            this.listenThread = new Thread(new ThreadStart(ListenForClients));
            this.listenThread.Start();
        }

        public void CloseServer()
        {
            client_connect = false;
            tcpListener.Stop();
            listenThread.Abort();
        }
        private void ListenForClients()
        {
            this.tcpListener.Start();

            client_connect = true;
            while (client_connect)
            {
                try
                {
                    //blocks until a client has connected to the server
                    TcpClient client = this.tcpListener.AcceptTcpClient();

                    //create a thread to handle communication 
                    //with connected client
                    Thread clientThread = new Thread(new ParameterizedThreadStart(HandleClientComm));
                    clientThread.Start(client);
                }
                catch
                {
                }
            }
        }
        public void SendMessage(string mess)
        {
            write_message = mess;
        }

        private void HandleClientComm(object client)
        {
            TcpClient tcpClient = (TcpClient)client;
            NetworkStream clientStream = tcpClient.GetStream();

            byte[] message = new byte[4096];

            while (client_connect)
            {
                try
                {
                    //blocks until a client sends a message
                    //bytesRead = clientStream.Read(message, 0, 4096);
                }
                catch
                {
                    //a socket error has occured
                    break;
                }

                try
                {
                    if (write_message.Length > 0)
                    {
                        System.Text.UTF8Encoding encoding = new System.Text.UTF8Encoding();
                        clientStream.Write(encoding.GetBytes(write_message), 0, write_message.Length);
                        write_message = string.Empty ;
                    }
                }
                catch
                {
                    //a socket error has occured
                    break;
                }
                Thread.Sleep(10);

                //message has successfully been received
                //ASCIIEncoding encoder = new ASCIIEncoding();
                //System.Diagnostics.Debug.WriteLine(encoder.GetString(message, 0, bytesRead));
            }
        }
    }
}
