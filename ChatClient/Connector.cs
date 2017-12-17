using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Threading;

namespace ChatClient
{
    public class Connector
    {
        public static Socket Client;
        public IPAddress ip = null;
        public int port = 0;
        public Thread thread;

        public void saveInfo(string info)
        {
            try
            {
                DirectoryInfo data = new DirectoryInfo("res/info");
                data.Create();

                var sw = new StreamWriter(@"res/info/data.txt");
                sw.WriteLine(info);
                sw.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        public string loadInfo()
        {
            string buffer = "";

            try
            {
                var sr = new StreamReader(@"res/info/data.txt");
                buffer = sr.ReadToEnd();
                sr.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

            return buffer;
        }

        public void setInfo(string ip, string port)
        { 
            this.ip = IPAddress.Parse(ip);
            this.port = int.Parse(port);
        }

        public void getConnect()
        {
            Client = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            
            if (ip != null)
                Client.Connect(ip, port);
        }

        public void sender(string message)
        {
            byte[] buffer = new byte[1024];
            for (int i = 0; i < 1024; i++)
                buffer[i] = 0;

            try
            {
                if (message != "")
                {
                    message += Utill.END;
                    buffer = Encoding.UTF8.GetBytes(message);
                    Client.Send(buffer);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        public string receiver()
        {
            byte[] buffer = new byte[1024];

            Client.Receive(buffer);

            string res = "";
            string message = Encoding.UTF8.GetString(buffer);
            int count = message.IndexOf(";;;");
            
            if (count == -1) 
                return "";

            for (int i = 0; i < count; i++)
                res += message[i];

            for (int i = 0; i < buffer.Length; i++)
                buffer[i] = 0;

            return res;
        }
    }
}
