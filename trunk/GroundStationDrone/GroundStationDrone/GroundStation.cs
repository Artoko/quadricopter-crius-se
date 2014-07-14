using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using GroundStationDrone;
using MySerial;

namespace GroundStationDrone
{
    public partial class GroundStation : Form
    {

        public static ClassSerial serial_com = new ClassSerial();
        ClassSerial.callback_message_receive my_callback;
        Graphics g = null;
        List<Point> points_roulis = new List<Point>();
        List<Point> points_tangage = new List<Point>();
        List<Point> points_lacet = new List<Point>();
        List<string> frame_sent = new List<string>();

        short speed_track = 0;

        static Thread thread_sequence;
        public static bool thread_sequence_flag = false;


        public GroundStation()
        {
            InitializeComponent();
            thread_sequence = new Thread(new ThreadStart(ThreadSequence));
        }
        private void GroundStation_FormClosing(object sender, FormClosingEventArgs e)
        {
            thread_sequence_flag = false;
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

        private string ConvertFrame(byte[] frame)
        {
            string conv = "";
            for (int i = 0; i < frame.Length; i++)
            {
                conv += Convert.ToString(Convert.ToChar(frame[i]));
            }
            return conv;
        }
        private void SendSerialMessage(string message, ClassSerial.callback_message_receive callback)
        {
            message = "*" + Convert.ToChar(Convert.ToByte(message.Length + 3)) +  message + "*";          
            my_callback = callback;
            serial_com.SetCallback(IncommingMessage);
            frame_sent.Add(message);

            byte[] mess = new byte[message.Length];
            for (int i = 0; i < message.Length; i++)
            {
                mess[i] = Convert.ToByte(message.Substring(i, 1).ToCharArray()[0]);
            }

            serial_com.SendMessage(mess);
            if (frame_sent.Count > 5) frame_sent.RemoveAt(0);
        }
        private void IncommingMessage(byte[] frame)
        {
            //my_callback(frame);
            Invoke((ClassSerial.callback_message_receive)my_callback, new object[] { frame });
        }
        private void ErrorMessage(byte[] frame)
        {
            toolStripStatusLabelVersion.Text = "Frame Error : ";
            toolStripStatusLabelVersion.ForeColor = Color.Red;
        }

        #region general
        private void GetVersion()
        {
            SendSerialMessage("1+1", IncommingMessageVersion);
        }
        private void IncommingMessageVersion(byte[] frame)
        {
            string response = ConvertFrame(frame);
            if (response.Length < 3)
            {
                ErrorMessage(frame);
            }
            else if (response.Substring(0, 3) == "1+1")
            {
                byte version = Encoding.ASCII.GetBytes(response.Replace(response.Substring(0, 4),"").ToCharArray())[0];
                toolStripStatusLabelVersion.Text = "Version : " + Convert.ToString((version & 0xf0) >> 4) + "." + Convert.ToString(version & 0x0f);
                toolStripStatusLabelVersion.ForeColor = Color.Blue;
                thread_sequence_flag = true;
                thread_sequence.Start();
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
            if (response.Length < 3)
            {
                ErrorMessage(frame);
            }
            else if (response == "1+2")
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
            if (response.Length < 3)
            {
                ErrorMessage(frame);
            }
            else if (response == "1+3")
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
            if (response.Length < 3)
            {
                ErrorMessage(frame);
            }
            else if (response.Substring(0, 3) == "2+2")
            {
                short speed = (short)((frame[16] << 8) + frame[17]);
                air_speed_indicator.SetAirSpeedIndicatorParameters((int)speed);
                toolStripStatusLabelSpeed.Text = "Speed : " + Convert.ToString(speed);
            }
        }
        private void getSpeedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            GetSpeed();
        }
        
        private void SetSpeed( short speed )
        {
            SendSerialMessage("2+1+" + Convert.ToChar(Convert.ToByte(speed >> 8)) + Convert.ToChar(Convert.ToByte((byte)speed )), IncommingMessageSetSpeed);
        }
        private void IncommingMessageSetSpeed(byte[] frame)
        {
            string response = ConvertFrame(frame);
            if (response.Length < 3)
            {
                ErrorMessage(frame);
            }
            else if (response.Substring(0, 3) == "2+1")
            {
            }
        }
        private void trackBarSpeed_Scroll(object sender, EventArgs e)
        {
            speed_track = (short)trackBarSpeed.Value; 
        }

        private void showIndicatorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (air_speed_indicator.Visible)
            {
                air_speed_indicator.Visible = false;
            }
            else
            {
                air_speed_indicator.Visible = true;
            }
        }
        #endregion

        #region Angles
        private void GetAngles()
        {
            SendSerialMessage("3+2", IncommingMessageGetAngles);
        }
        private void IncommingMessageGetAngles(byte[] frame)
        {
            string response = ConvertFrame(frame);
            if (response.Length < 3)
            {
                ErrorMessage(frame);
            }
            else if (response.Substring(0, 3) == "3+2")
            {
                short angle_roulis = (short)((frame[3] << 8) + frame[4]);
                short angle_tangage = (short)((frame[6] << 8) + frame[7]);
                short angle_lacet = (short)((frame[9] << 8) + frame[10]);
                horizon_indicator.SetAttitudeIndicatorParameters(angle_tangage, angle_roulis);
                turn_indicator.SetTurnCoordinatorParameters(angle_roulis / 10, angle_roulis / 10);
                heading_indicator.SetHeadingIndicatorParameters(angle_lacet);

                toolStripStatusLabelAngles.Text = "Angles : " + Convert.ToString(angle_roulis) + " , " + Convert.ToString(angle_tangage) + " , " + Convert.ToString(angle_lacet);
            }
        }
        private void getAnglesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            GetAngles();
        } 
        #endregion

        #region Sensors
        private void GetBarometer()
        {
            SendSerialMessage("4+4", IncommingMessageGetBarometer);
        }
        private void IncommingMessageGetBarometer(byte[] frame)
        {
            string response = ConvertFrame(frame);
            if (response.Length < 3)
            {
                ErrorMessage(frame);
            }
            else if (response.Substring(0, 3) == "4+4")
            {
                short altitude = (short)((frame[3] << 8) + frame[4]);
                short temperature = (short)((frame[6] << 8) + frame[7]);
                Int32 pressure = (Int32)((frame[9] << 24) + (frame[10] << 16) + (frame[11] << 8) + (frame[12]));
                byte wheather = (byte)(frame[14]);
                altimeter_indicator.SetAlimeterParameters(altitude);

                toolStripStatusLabelAltitude.Text = "Altitude = " + Convert.ToString(altitude) ;
                toolStripStatusLabelTemperature.Text = "Temperature : " + Convert.ToString(temperature) + " °C";
                toolStripStatusLabelPresssion.Text = "Pression : " + Convert.ToString(pressure) + " Pa";
            }
        }
        private void getAltitudeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            GetBarometer();
        }

        private void GetAccelerometer()
        {
            SendSerialMessage("4+1", IncommingMessageGetAccelerometer);
        }
        private void IncommingMessageGetAccelerometer(byte[] frame)
        {
            string response = ConvertFrame(frame);
            if (response.Length < 3)
            {
                ErrorMessage(frame);
            }
            else if (response.Substring(0, 3) == "4+1")
            {
                short x = (short)((frame[3] << 8) + frame[4]);
                short y = (short)((frame[6] << 8) + frame[7]);
                short z = (short)((frame[9] << 8) + frame[10]);
            }
        }
        private void getAccelerometerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            GetAccelerometer();
        }

        private void GetGyroscope()
        {
            SendSerialMessage("4+2", IncommingMessageGetGyroscope);
        }
        private void IncommingMessageGetGyroscope(byte[] frame)
        {
            string response = ConvertFrame(frame);
            if (response.Length < 3)
            {
                ErrorMessage(frame);
            }
            else if (response.Substring(0, 3) == "4+2")
            {
                short x = (short)((frame[3] << 8) + frame[4]);
                short y = (short)((frame[6] << 8) + frame[7]);
                short z = (short)((frame[9] << 8) + frame[10]);
            }
        }
        private void getGyroscopeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            GetGyroscope();
        }

        private void GetMagnetometer()
        {
            SendSerialMessage("4+3", IncommingMessageGetMagnetometer);
        }
        private void IncommingMessageGetMagnetometer(byte[] frame)
        {
            string response = ConvertFrame(frame);
            if (response.Length < 3)
            {
                ErrorMessage(frame);
            }
            else if (response.Substring(0, 3) == "4+3")
            {
                short x = (short)((frame[3] << 8) + frame[4]);
                short y = (short)((frame[6] << 8) + frame[7]);
                short z = (short)((frame[9] << 8) + frame[10]);
            }
        }
        private void getMagnetometerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            GetMagnetometer();
        }
        #endregion

        #region PID
        private void GetPID(string index)
        {
            SendSerialMessage("5+2+" + index, IncommingMessageGetPIDs);
        }
        private void GetPID(int index)
        {
            SendSerialMessage("5+2+" + index, IncommingMessageGetPIDs);
        }
        private void IncommingMessageGetPIDs(byte[] frame)
        {
            string response = ConvertFrame(frame);
            
            if (response.Length < 3)
            {
                ErrorMessage(frame);
            }
            else if (response.Substring(0, 3) == "5+2")
            {
                byte pid_index = frame[4];
                short pid_P = (short)((frame[6] << 8) + frame[7]);
                short pid_I = (short)((frame[9] << 8) + frame[10]);
                short pid_D = (short)((frame[12] << 8) + frame[13]);
            }
        }
        private void getPIDsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            GetPID(0);
        }



        private void SetPID(short index, short pid_P, short pid_I, short pid_D)
        {
            SendSerialMessage("5+1+" +
                Convert.ToChar(Convert.ToByte(index >> 8)) +
                "+" +
                Convert.ToChar(Convert.ToByte(pid_P >> 8)) +
                Convert.ToChar(Convert.ToByte((byte)pid_P)) +
                "+" +
                Convert.ToChar(Convert.ToByte(pid_I >> 8)) +
                Convert.ToChar(Convert.ToByte((byte)pid_I)) +
                "+" +
                Convert.ToChar(Convert.ToByte(pid_D >> 8)) +
                Convert.ToChar(Convert.ToByte((byte)pid_D))
                , IncommingMessageSetPIDs);
        }
        private void IncommingMessageSetPIDs(byte[] frame)
        {
            string response = ConvertFrame(frame);

            if (response.Length < 3)
            {
                ErrorMessage(frame);
            }
            else if (response.Substring(0, 3) == "5+1")
            {
                byte pid_index = frame[4];
                short pid_P = (short)((frame[6] << 8) + frame[7]);
                short pid_I = (short)((frame[9] << 8) + frame[10]);
                short pid_D = (short)((frame[12] << 8) + frame[13]);
            }
        }
        private void setPIDsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SetPID(0,0,0,0);
        }

        #endregion

        int time = 0;
        private void SetAll(short speed, short roulis, short tangage, short lacet)
        {
            SendSerialMessage("6+" +
                Convert.ToChar(Convert.ToByte(speed >> 8)) +
                Convert.ToChar(Convert.ToByte((byte)speed)) +
                "+" +
                Convert.ToChar(Convert.ToByte(roulis >> 8)) +
                Convert.ToChar(Convert.ToByte((byte)roulis)) +
                "+" +
                Convert.ToChar(Convert.ToByte(tangage >> 8)) +
                Convert.ToChar(Convert.ToByte((byte)tangage)) +
                "+" +
                Convert.ToChar(Convert.ToByte(lacet >> 8)) +
                Convert.ToChar(Convert.ToByte((byte)lacet))
                ,IncommingMessageSetAll);
        }
        private void IncommingMessageSetAll(byte[] frame)
        {
            string response = ConvertFrame(frame);
            if (response.Length < 1)
            {
                ErrorMessage(frame);
            }
            else if (response.Substring(0, 1) == "6")
            {
                short angle_roulis = (short)((frame[2] << 8) + frame[3]);
                short angle_tangage = (short)((frame[5] << 8) + frame[6]);
                short angle_lacet = (short)((frame[8] << 8) + frame[9]);
                short angle_nord = (short)((frame[11] << 8) + frame[12]);
                short altitude = (short)((frame[14] << 8) + frame[15]);
                short speed = (short)((frame[17] << 8) + frame[18]);
                short temperature = (short)((frame[20] << 8) + frame[21]);
                Int32 pressure = (Int32)((frame[23] << 24) + (frame[24] << 16) + (frame[25] << 8) + (frame[26]));
                short x = (short)((frame[28] << 8) + frame[29]);
                short y = (short)((frame[31] << 8) + frame[32]);
                short z = (short)((frame[34] << 8) + frame[35]);


                horizon_indicator.SetAttitudeIndicatorParameters(angle_tangage, angle_roulis);
                turn_indicator.SetTurnCoordinatorParameters(angle_roulis / 10, angle_roulis / 10);
                heading_indicator.SetHeadingIndicatorParameters(angle_lacet);
                altimeter_indicator.SetAlimeterParameters(altitude);
                air_speed_indicator.SetAirSpeedIndicatorParameters((int)speed);
                vario_indicator.SetVerticalSpeedIndicatorParameters(((z - 255) * -6000) / 255);

                toolStripStatusLabelAngles.Text = "Angles : " + Convert.ToString(angle_roulis) + " , " + Convert.ToString(angle_tangage) + " , " + Convert.ToString(angle_lacet);
                toolStripStatusLabelSpeed.Text = "Speed : " + Convert.ToString(speed);
                toolStripStatusLabelAltitude.Text = "Altitude = " + Convert.ToString(altitude);
                toolStripStatusLabelTemperature.Text = "Temperature : " + Convert.ToString(temperature) + " °C";
                toolStripStatusLabelPresssion.Text = "Pression : " + Convert.ToString(pressure) + " Pa";
                time++;
                
                points_roulis.Add(new Point((int)((time * panel1.Width / 250)), panel1.Height / 2 - (int)(((angle_roulis - 1) * panel1.Height) / 180) - 1));
                points_tangage.Add(new Point((int)((time * panel1.Width / 250)), panel1.Height / 2 - (int)(((angle_tangage - 1) * panel1.Height) / 180) - 1));
                points_lacet.Add(new Point((int)((time * panel1.Width / 250)), panel1.Height - (int)(((angle_lacet - 1) * panel1.Height) / 360) - 1));

                if (points_roulis.Count > 250)
                {
                    time--;
                    for (int i = 1; i < points_roulis.Count; i++)
                    {
                        if (points_roulis[i].X - points_roulis[0].X >= 0)
                        {
                            points_roulis[i - 1] = new Point(points_roulis[i].X - points_roulis[0].X, points_roulis[i].Y);
                        }
                        else
                        {
                            points_roulis[i - 1] = new Point(0, points_roulis[i].Y);
                        }

                        if (points_tangage[i].X - points_tangage[0].X >= 0)
                        {
                            points_tangage[i - 1] = new Point(points_tangage[i].X - points_tangage[0].X, points_tangage[i].Y);
                        }
                        else
                        {
                            points_tangage[i - 1] = new Point(0, points_tangage[i].Y);
                        }

                        if (points_lacet[i].X - points_lacet[0].X >= 0)
                        {
                            points_lacet[i - 1] = new Point(points_lacet[i].X - points_lacet[0].X, points_lacet[i].Y);
                        }
                        else
                        {
                            points_lacet[i - 1] = new Point(0, points_lacet[i].Y);
                        }
                    }
                    points_roulis.RemoveRange(points_roulis.Count - 1, 1);
                    points_tangage.RemoveRange(points_tangage.Count - 1, 1);
                    points_lacet.RemoveRange(points_lacet.Count - 1, 1);
                }
                panel1.Refresh();
                //SetAll(speed_track, 0, 0, 0);
            }
        }

        private void ThreadSequence()
        {
            while (thread_sequence_flag)
            {
                SetAll(speed_track, 0, 0, 0);
                Thread.Sleep(50);
            }
        }

        #region graph

        
        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            g = e.Graphics;
            if (points_roulis.Count > 1)
            {
                g.DrawLines(new Pen(Color.Red), points_roulis.ToArray());
                g.DrawLines(new Pen(Color.Green), points_tangage.ToArray());
                g.DrawLines(new Pen(Color.Blue), points_lacet.ToArray());
            }
            g.Dispose();
        }

        #endregion
        
        #region View
        private void cockpitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!horizon_indicator.Visible)
            {
                horizon_indicator.Visible = true;
                turn_indicator.Visible = true;
                heading_indicator.Visible = true;
                altimeter_indicator.Visible = true;
                air_speed_indicator.Visible = true;
                vario_indicator.Visible = true;
            }
            else
            {
                horizon_indicator.Visible = false;
                turn_indicator.Visible = false;
                heading_indicator.Visible = false;
                altimeter_indicator.Visible = false;
                air_speed_indicator.Visible = false;
                vario_indicator.Visible = false;
            }
        }
        #endregion


        

        


        






    }
}
