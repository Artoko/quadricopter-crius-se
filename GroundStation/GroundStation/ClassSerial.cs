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

        public delegate void callback_message_receive(byte[] frame);
        callback_message_receive list_callback_messages;
        public static bool Thread_Listener_flag = false;

        static Thread Thread_Listener;

        public bool Connect(string port_name, callback_message_receive callback)
        {
            bool ret = false;
            serialPort1.PortName = port_name;
            serialPort1.BaudRate = 57600;
            list_callback_messages = callback;
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


        public void SendMessage(string message)
        {
            serialPort1.Write(message);
        }


        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
        }


        byte[] recpt_buff = new byte[100];
        int index = 0;
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
                            recpt_buff[index++] = (byte)serialPort1.ReadByte();
                            if (index > 4)
                            if ( (recpt_buff[index - 4] == '#') && (recpt_buff[index - 3] == '#') && (recpt_buff[index - 2] == '#') && (recpt_buff[index - 1] == '#'))
                            {
                                //if (index == 34)
                                {
                                    byte[] frame = new byte[index - 4];
                                    for (int i = 0; i < index - 4; i++)
                                    {
                                        frame[i] = recpt_buff[i];
                                        recpt_buff[i] = 0;
                                    }
                                    list_callback_messages(frame);
                                }
                                bytes -= index;
                                if (bytes < 0) bytes = 0;
                                index = 0;
                            }
                        }

                        bytes = 0;
                    }
                    catch
                    {
                        index = 0;
                    }
                }
                else
                {
                    Thread.Sleep(5);
                    index = 0;
                }
            }
        }

       
    }
}
