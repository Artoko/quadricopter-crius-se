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
        public static bool Thread_Listener_flag = false;

        static Thread Thread_Listener;

        public bool Connect (string port_name)
        {
            bool ret = false;
            serialPort1.PortName = port_name;
            serialPort1.BaudRate = 57600;
            try
            {
                serialPort1.Open();
                
                ret = true;
            }
            catch
            {
                serialPort1.Close();
            }
            try
            {
                serialPort1.Open();
                ret = true;
            }
            catch
            {
                
            }

            if (ret == true)
            {
                Thread_Listener = new Thread(new ThreadStart(ClassUartThreadListenerModem));
                Thread_Listener.Start();
                Thread_Listener_flag = true;
            }
            return ret;
        }
        public bool Deconnect()
        {
            Thread_Listener_flag = false;
            if(serialPort1.IsOpen)
            {
                serialPort1.ReadExisting();
                serialPort1.Close();
                serialPort1.Dispose();
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

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
        }
        string frame = "";

        private void ClassUartThreadListenerModem()
        {
            while (Thread_Listener_flag)
            {
                if (serialPort1.BytesToRead > 0)
                {

                    try
                    {
                        int bytes = serialPort1.BytesToRead;
                        while (bytes != 0)
                        {
                            string frame = serialPort1.ReadLine();
                            for (int loop = 0; loop < list_callback_messages.Count; loop++)
                            {
                                list_callback_messages[loop](frame);
                                bytes -= frame.Length;
                            }
                        }

                        bytes = 0;
                    }
                    catch
                    {
                    }
                }
                else
                {
                    Thread.Sleep(5);
                }
            }
        }

       
    }
}
