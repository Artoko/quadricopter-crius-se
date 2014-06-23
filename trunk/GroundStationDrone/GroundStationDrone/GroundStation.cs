using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MySerial;

namespace GroundStationDrone
{
    public partial class GroundStation : Form
    {
        public static ClassSerial serial_com = new ClassSerial();
        ClassSerial.callback_message_receive my_callback;
        public GroundStation()
        {
            InitializeComponent();
        }
        private void GroundStation_FormClosing(object sender, FormClosingEventArgs e)
        {
            serial_com.Deconnect();
        }
        private void GroundStation_Load(object sender, EventArgs e)
        {
            if (toolStripStatusLabelVersion.Text == "Version : 0.0")
            {
                if ((serial_com.Connect("COM7") == true)||
                    (serial_com.Connect("COM5") == true)
                    )
                {
                    GetVersion();
                }
            }
        }

        string ConvertFrame( byte[] frame )
        {
            string conv = "";
            for (int i = 0; i < frame.Length; i++)
            {
                conv += Convert.ToString(Convert.ToChar(frame[i]));
            }
            return conv;
        }
        void SendSerialMessage(string message, ClassSerial.callback_message_receive callback)
        {
            message = "*" + message + "##";
            my_callback = callback;
            serial_com.SetCallback(IncommingMessage);
            serial_com.SendMessage(message);
        }
        private void IncommingMessage(byte[] frame)
        {
            Invoke((ClassSerial.callback_message_receive)my_callback, new object[]{frame});
        }


        #region general
        private void GetVersion()
        {
            SendSerialMessage("1+1", IncommingMessageVersion);
        }
        private void IncommingMessageVersion(byte[] frame)
        {
            string response = ConvertFrame(frame);
            if (response.Substring(0, 4) == "1+1+")
            {
                byte version = Encoding.ASCII.GetBytes(response.Replace(response.Substring(0, 4),"").ToCharArray())[0];
                toolStripStatusLabelVersion.Text = "Version : " + Convert.ToString((version & 0xf0) >> 4) + "." + Convert.ToString(version & 0x0f);
                toolStripStatusLabelVersion.ForeColor = Color.Blue;
            }
        }
        private void getVersionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            GetVersion();
        }
        
        private void SetReset()
        {
            SendSerialMessage("1+2", IncommingMessageReset);
        }
        private void IncommingMessageReset(byte[] frame)
        {
            string response = ConvertFrame(frame);
            if (response == "1+2")
            {
                GetVersion();
            }
        }
        private void resetToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SetReset();
        }

        
        private void SetFullReset()
        {
            SendSerialMessage("1+3", IncommingMessageFullReset);
        }
        private void IncommingMessageFullReset(byte[] frame)
        {
            string response = ConvertFrame(frame);
            if (response == "1+3")
            {
                GetVersion();
            }
        }
        private void recalibrationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SetFullReset();
        }
        #endregion
       
        #region Motors
        private void GetSpeed()
        {
            SendSerialMessage("2+2", IncommingMessageGetSpeed);
        }
        private void IncommingMessageGetSpeed(byte[] frame)
        {
            string response = ConvertFrame(frame);
            if (response.Substring(0,3) == "2+2")
            {
                toolStripStatusLabelSpeed.Text = "Speed : " + Convert.ToString((short)((frame[16] << 8) + frame[17]));
                float speed = (float)((frame[16] << 8) + frame[17]);
                toolStripStatusLabelSpeed.ForeColor = System.Drawing.Color.FromArgb((byte)(float)(255 * (speed / 1000)), (byte)(float)(255 - (255 * (speed / 1000))), (byte)(50));
            }
        }
        private void getSpeedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            GetSpeed();
        }
        
        private void SetSpeed( int speed )
        {
            SendSerialMessage("2+1+" + speed, IncommingMessageSetSpeed);
        }
        private void IncommingMessageSetSpeed(byte[] frame)
        {
            string response = ConvertFrame(frame);
            if (response.Substring(0, 3) == "2+1")
            {
                GetSpeed();
            }
        }
        private void trackBarSpeed_Scroll(object sender, EventArgs e)
        {
            SetSpeed(trackBarSpeed.Value);
        }
        #endregion

        







    }
}
