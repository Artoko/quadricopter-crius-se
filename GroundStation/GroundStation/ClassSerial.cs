using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.Threading;
using System.Windows.Forms;

namespace GroundStation
{
    public class ClassSerial
    {
        SerialPort serialPort1 = new SerialPort();
        
        public delegate void callback_message_receive(string message);
        List<callback_message_receive> list_callback_messages = new List<callback_message_receive>();
        
        Thread Thread_recept;
        public static bool Thread_recept_run_flag = false;
        Queue<string> rcv_messages = new Queue<string>();

        public bool Connect (string port_name)
        {
            bool ret = false;
            serialPort1.PortName = port_name;
            serialPort1.BaudRate = 115200;
            try
            {
                serialPort1.Open();
                Thread_recept_run_flag = true;
                Thread_recept = new Thread(new ThreadStart(ThreadReceive));
                Thread_recept.Start();
                serialPort1.DataReceived += serialPort1_DataReceived;
                ret = true;
            }
            catch
            {
                serialPort1.Close();
            }
            try
            {
                serialPort1.Open();
                Thread_recept_run_flag = true;
                Thread_recept = new Thread(new ThreadStart(ThreadReceive));
                Thread_recept.Start();
                serialPort1.DataReceived += serialPort1_DataReceived;
                ret = true;
            }
            catch
            {
                
            }
            
            return ret;
        }
        public bool Deconnect()
        {
            Thread_recept_run_flag = false;
            if(serialPort1.IsOpen)
            {
                serialPort1.DiscardInBuffer();
                serialPort1.DataReceived -= serialPort1_DataReceived;
                serialPort1.Close();
                return true;
            }
            return false;
        }


        public bool DeleteCallback(callback_message_receive callback)
        {
            try
            {
                list_callback_messages.Remove(callback);
                return true;
            }
            catch
            {
                return false;
            }
        }
        public void SendMessage(string message)
        {
            serialPort1.Write(message);
        }
        public bool AddCallback( callback_message_receive callback )
        {
            try
            {
                list_callback_messages.Add(callback);
                return true;
            }
            catch
            {
                return false;
            }
        }

        private void ThreadReceive()
        {
            while (Thread_recept_run_flag)
            {
                //si la fifo est pleine
                if (rcv_messages.Count > 0)
                {
                    //on envoie sur port serie
                    string frame = rcv_messages.Dequeue();
                    if ((frame != null) || (frame != ""))
                    {
                        //on converti en byte
                        //try
                        {
                            for(int loop = 0; loop < list_callback_messages.Count;loop++)
                            {
                                list_callback_messages[loop](frame);
                            }
                        }
                        //catch { }
                    }
                }
                Thread.Sleep(5);
            }
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            try
            {
                while (serialPort1.BytesToRead != 0)
                {
                    rcv_messages.Enqueue(serialPort1.ReadLine());
                }
                //serialPort1.DiscardInBuffer();
            }
            catch
            {
            }
        }


       
    }
}
