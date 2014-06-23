using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.Threading;
using System.Windows.Forms;

namespace MySerial
{
    public class ClassSerial
    {
        SerialPort serialPort1 = new SerialPort();

        public delegate void callback_message_receive(byte[] frame);
        callback_message_receive list_callback_messages;
        public static bool Thread_Listener_flag = false;

        static Thread Thread_Listener;

        public bool Connect(string port_name)
        {
            bool ret = false;
            serialPort1.PortName = port_name;
            serialPort1.BaudRate = 115200;
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
                //serialPort1.DataReceived +=serialPort1_DataReceived;
                Thread_Listener = new Thread(new ThreadStart(ClassUartThreadListenerModem));
                Thread_Listener.Start();
                Thread_Listener_flag = true;
            }
            return ret;
        }


        public bool Connect(string port_name, callback_message_receive callback)
        {
            list_callback_messages = callback;
            return Connect(port_name) ;
        }

        public void SetCallback( callback_message_receive callback )
        {
            list_callback_messages = callback;
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
            if (serialPort1.IsOpen)
            {
                serialPort1.Write(message);
            }
        }

        /*private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            List<byte> bytes = Encoding.ASCII.GetBytes(serialPort1.ReadExisting().ToCharArray()).ToList();
            if ((bytes[0] == '*') && (bytes[bytes.Count - 2] == '#') && (bytes[bytes.Count - 1] == '#'))
            {
                bytes.RemoveAt(0);
                bytes.RemoveAt(bytes.Count - 1);
                bytes.RemoveAt(bytes.Count - 1);
                list_callback_messages(bytes.ToArray());
            }
        }*/


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
                            if ( (recpt_buff[index - 2] == '#') && (recpt_buff[index - 1] == '#'))
                            {
                                //if (index == 34)
                                {
                                    byte[] frame = new byte[index - 3];
                                    for (int i = 1; i < index - 2; i++)
                                    {
                                        frame[i - 1] = recpt_buff[i];
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
