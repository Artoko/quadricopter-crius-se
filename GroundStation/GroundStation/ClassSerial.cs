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
        

        public bool Connect (string port_name)
        {
            bool ret = false;
            serialPort1.PortName = port_name;
            serialPort1.BaudRate = 115200;
            try
            {
                serialPort1.Open();
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
            if(serialPort1.IsOpen)
            {
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

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            try
            {
                /*while (serialPort1.BytesToRead != 0)
                {
                    rcv_messages.Enqueue(serialPort1.ReadLine());
                }*/
                for (int loop = 0; loop < list_callback_messages.Count; loop++)
                {
                    list_callback_messages[loop](serialPort1.ReadLine());
                }
                //serialPort1.DiscardInBuffer();
            }
            catch
            {
            }
        }


       
    }
}
