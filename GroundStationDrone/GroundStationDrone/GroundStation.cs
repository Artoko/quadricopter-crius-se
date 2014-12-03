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
        ClassCommDrone comm_drone = new ClassCommDrone();

        short angle_roulis = 0;
        short angle_tangage = 0;
        short angle_lacet = 0;
        short angle_nord = 0;
        short altitude = 0;
        short speed = 0;
        short front_l = 0;
        short front_r = 0;
        short rear_l = 0;
        short rear_r = 0;
        short temperature = 0;
        Int32 pressure = 0;
        short acc_x = 0;
        short acc_y = 0;
        short acc_z = 0;
        short gyr_x = 0;
        short gyr_y = 0;
        short gyr_z = 0;
        short mag_x = 0;
        short mag_y = 0;
        short mag_z = 0;
        Int32 loop_time = 0;

        Graphics g = null;
        List<Point> points_roulis = new List<Point>();
        List<Point> points_tangage = new List<Point>();
        List<Point> points_lacet = new List<Point>();
        List<Point> points_nord = new List<Point>();

        List<Point> points_acc_x = new List<Point>();
        List<Point> points_acc_y = new List<Point>();
        List<Point> points_acc_z = new List<Point>();

        List<Point> points_gyr_x = new List<Point>();
        List<Point> points_gyr_y = new List<Point>();
        List<Point> points_gyr_z = new List<Point>();

        List<Point> points_mag_x = new List<Point>();
        List<Point> points_mag_y = new List<Point>();
        List<Point> points_mag_z = new List<Point>();

        List<Point> points_mot_1 = new List<Point>();
        List<Point> points_mot_2 = new List<Point>();
        List<Point> points_mot_3 = new List<Point>();
        List<Point> points_mot_4 = new List<Point>();

        List<Point> points_loop = new List<Point>();
        

        List<string> frame_sent = new List<string>();

        short speed_track = 0;
        bool loop_set_all = true;
        int index_pid = 0;


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
                if ((serial_com.Connect("COM3") == true)||
                    (serial_com.Connect("COM5") == true) ||
                    (serial_com.Connect("COM22") == true)
                    )
                {
                    serial_com.ClassUartReset();
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
            SendSerialMessage(comm_drone.GetVersion(), IncommingMessageVersion);
        }
        private void IncommingMessageVersion(byte[] frame)
        {
            string response = ConvertFrame(frame);
            if (response.Length < comm_drone.GetVersion().Length)
            {
                ErrorMessage(frame);
            }
            else if (response.Substring(0, comm_drone.GetVersion().Length) == comm_drone.GetVersion())
            {
                byte version = Encoding.ASCII.GetBytes(response.Replace(response.Substring(0, 4), "").ToCharArray())[0];
                toolStripStatusLabelVersion.Text = "Version : " + Convert.ToString((version & 0xf0) >> 4) + "." + Convert.ToString(version & 0x0f);
                toolStripStatusLabelVersion.ForeColor = Color.Blue;
                labelAttitude.Font = new Font(labelAttitude.Font, FontStyle.Bold);
                labelAcc.Font = new Font(labelAcc.Font, FontStyle.Regular);
                labelGyro.Font = new Font(labelGyro.Font, FontStyle.Regular);
                labelMag.Font = new Font(labelMag.Font, FontStyle.Regular);
                labelMot.Font = new Font(labelMot.Font, FontStyle.Regular);
                labelLoop.Font = new Font(labelLoop.Font, FontStyle.Regular);
                loop_set_all = true;
                GetPID(0);
            }
            else
            {
                serial_com.ClassUartReset();
            }
        }
        private void getVersionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            serial_com.ClassUartReset();
            GetVersion();
        }
        
        private void SetReset()
        {
            SendSerialMessage(comm_drone.SetReset(), IncommingMessageReset);
        }
        private void IncommingMessageReset(byte[] frame)
        {
            string response = ConvertFrame(frame);
            if (response.Length < comm_drone.SetReset().Length)
            {
                ErrorMessage(frame);
            }
            else if (response == comm_drone.SetReset())
            {
                serial_com.ClassUartReset();
                GetVersion();
            }
        }
        private void resetToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SetReset();
        }
   
        private void SetFullReset()
        {
            SendSerialMessage(comm_drone.SetFullReset(), IncommingMessageFullReset);
        }
        private void IncommingMessageFullReset(byte[] frame)
        {
            string response = ConvertFrame(frame);
            if (response.Length < comm_drone.SetFullReset().Length)
            {
                ErrorMessage(frame);
            }
            else if (response == comm_drone.SetFullReset())
            {
                serial_com.ClassUartReset();
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
            SendSerialMessage(comm_drone.GetSpeed(), IncommingMessageGetSpeed);
        }
        private void IncommingMessageGetSpeed(byte[] frame)
        {
            string response = ConvertFrame(frame);
            if (response.Length < comm_drone.GetSpeed().Length)
            {
                ErrorMessage(frame);
            }
            else if (response.Substring(0, comm_drone.GetSpeed().Length) == comm_drone.GetSpeed())
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
            SendSerialMessage(comm_drone.GetSpeed() + "+" + Convert.ToChar(Convert.ToByte(speed >> 8)) + Convert.ToChar(Convert.ToByte((byte)speed)), IncommingMessageSetSpeed);
        }
        private void IncommingMessageSetSpeed(byte[] frame)
        {
            string response = ConvertFrame(frame);
            if (response.Length < comm_drone.GetSpeed().Length)
            {
                ErrorMessage(frame);
            }
            else if (response.Substring(0, comm_drone.GetSpeed().Length) == comm_drone.GetSpeed())
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
            SendSerialMessage(comm_drone.GetAngles(), IncommingMessageGetAngles);
        }
        private void IncommingMessageGetAngles(byte[] frame)
        {
            string response = ConvertFrame(frame);
            if (response.Length < comm_drone.GetAngles().Length)
            {
                ErrorMessage(frame);
            }
            else if (response.Substring(0, comm_drone.GetAngles().Length) == comm_drone.GetAngles())
            {
                short angle_roulis = (short)((frame[3] << 8) + frame[4]);
                short angle_tangage = (short)((frame[6] << 8) + frame[7]);
                short angle_lacet = (short)((frame[9] << 8) + frame[10]);
                horizon_indicator.SetAttitudeIndicatorParameters(angle_tangage, angle_roulis);
                turn_indicator.SetTurnCoordinatorParameters(angle_roulis / 10, angle_roulis / 10);
                heading_indicator.SetHeadingIndicatorParameters(angle_lacet);

                toolStripStatusLabelAngles.Text = "Angles : " + Convert.ToString(angle_roulis) + "° , " + Convert.ToString(angle_tangage) + "° , " + Convert.ToString(angle_lacet)+"°";
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
            SendSerialMessage(comm_drone.GetBarometer(), IncommingMessageGetBarometer);
        }
        private void IncommingMessageGetBarometer(byte[] frame)
        {
            string response = ConvertFrame(frame);
            if (response.Length < comm_drone.GetBarometer().Length)
            {
                ErrorMessage(frame);
            }
            else if (response.Substring(0, comm_drone.GetBarometer().Length) == comm_drone.GetBarometer())
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
            SendSerialMessage(comm_drone.GetAccelerometer(), IncommingMessageGetAccelerometer);
        }
        private void IncommingMessageGetAccelerometer(byte[] frame)
        {
            string response = ConvertFrame(frame);
            if (response.Length < comm_drone.GetAccelerometer().Length)
            {
                ErrorMessage(frame);
            }
            else if (response.Substring(0, comm_drone.GetAccelerometer().Length) == comm_drone.GetAccelerometer())
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
            SendSerialMessage(comm_drone.GetGyroscope(), IncommingMessageGetGyroscope);
        }
        private void IncommingMessageGetGyroscope(byte[] frame)
        {
            string response = ConvertFrame(frame);
            if (response.Length < comm_drone.GetGyroscope().Length)
            {
                ErrorMessage(frame);
            }
            else if (response.Substring(0, comm_drone.GetGyroscope().Length) == comm_drone.GetGyroscope())
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
            SendSerialMessage(comm_drone.GetMagnetometer(), IncommingMessageGetMagnetometer);
        }
        private void IncommingMessageGetMagnetometer(byte[] frame)
        {
            string response = ConvertFrame(frame);
            if (response.Length < comm_drone.GetMagnetometer().Length)
            {
                ErrorMessage(frame);
            }
            else if (response.Substring(0, comm_drone.GetMagnetometer().Length) == comm_drone.GetMagnetometer())
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
            SendSerialMessage( comm_drone.GetPID() + "+" + index, IncommingMessageGetPIDs);
        }
        private void GetPID(int index)
        {
            SendSerialMessage(comm_drone.GetPID() + "+" + index, IncommingMessageGetPIDs);
        }
        private void IncommingMessageGetPIDs(byte[] frame)
        {
            string response = ConvertFrame(frame);

            if (response.Length < comm_drone.GetPID().Length)
            {
                ErrorMessage(frame);
            }
            else if (response.Substring(0, comm_drone.GetPID().Length) == comm_drone.GetPID())
            {
                byte pid_index = frame[4];
                short pid_P = (short)((frame[6] << 8) + frame[7]);
                short pid_I = (short)((frame[9] << 8) + frame[10]);
                short pid_D = (short)((frame[12] << 8) + frame[13]);

                if (pid_index == 0)
                {
                    numericUpDownProulis.Value = pid_P;
                    numericUpDownIroulis.Value = pid_I;
                    numericUpDownDroulis.Value = pid_D;
                    GetPID(1);
                }
                else if (pid_index == 1)
                {
                    numericUpDownPtangage.Value = pid_P;
                    numericUpDownItangage.Value = pid_I;
                    numericUpDownDtangage.Value = pid_D;
                    GetPID(2);
                }
                else if (pid_index == 2)
                {
                    numericUpDownPlacet.Value = pid_P;
                    numericUpDownIlacet.Value = pid_I;
                    numericUpDownDlacet.Value = pid_D;
                    loop_set_all = true;
                    SetAll(speed_track, 0, 0, 0);
                }
            }
        }
        private void getPIDsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            GetPID(0);
        }



        private void SetPID(short index, short pid_P, short pid_I, short pid_D)
        {
            SendSerialMessage("5+1+" +
                index +
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

                if (pid_index == 0)
                {
                    numericUpDownProulis.Value = pid_P;
                    numericUpDownIroulis.Value = pid_I;
                    numericUpDownDroulis.Value = pid_D;
                }
                else if (pid_index == 1)
                {
                    numericUpDownPtangage.Value = pid_P;
                    numericUpDownItangage.Value = pid_I;
                    numericUpDownDtangage.Value = pid_D;
                }
                else if (pid_index == 2)
                {
                    numericUpDownPlacet.Value = pid_P;
                    numericUpDownIlacet.Value = pid_I;
                    numericUpDownDlacet.Value = pid_D;
                }

            }
            loop_set_all = true;
            SetAll(speed_track, 0, 0, 0);
        }
        private void setPIDsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SetPID(0,0,0,0);
        }

        #endregion

        int time = 0;
        private void SetAll(short speed, short roulis, short tangage, short lacet)
        {
            SendSerialMessage( comm_drone.SetAll() + "+" +
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
            if (response.Length < comm_drone.SetAll().Length)
            {
                ErrorMessage(frame);
            }
            else if (response.Substring(0, comm_drone.SetAll().Length) == comm_drone.SetAll())
            {
                //get data from quad
                angle_roulis = (short)((frame[2] << 8) + frame[3]);
                angle_tangage = (short)((frame[4] << 8) + frame[5]);
                angle_lacet = (short)((frame[6] << 8) + frame[7]);
                angle_nord = (short)((frame[8] << 8) + frame[9]);
                altitude = (short)((frame[10] << 8) + frame[11]);
                speed = (short)((frame[12] << 8) + frame[13]);
                front_l = (short)((frame[14] << 8) + frame[15]);
                front_r = (short)((frame[16] << 8) + frame[17]);
                rear_l = (short)((frame[18] << 8) + frame[19]);
                rear_r = (short)((frame[20] << 8) + frame[21]);
                temperature = (short)((frame[22] << 8) + frame[23]);
                pressure = (Int32)((frame[24] << 24) + (frame[25] << 16) + (frame[26] << 8) + (frame[27]));
                acc_x = (short)((frame[28] << 8) + frame[29]);
                acc_y = (short)((frame[30] << 8) + frame[31]);
                acc_z = (short)((frame[32] << 8) + frame[33]);
                gyr_x = (short)((frame[34] << 8) + frame[35]);
                gyr_y = (short)((frame[36] << 8) + frame[37]);
                gyr_z = (short)((frame[38] << 8) + frame[39]);
                mag_x = (short)((frame[40] << 8) + frame[41]);
                mag_y = (short)((frame[42] << 8) + frame[43]);
                mag_z = (short)((frame[44] << 8) + frame[45]);
                loop_time = (Int32)((frame[46] << 24) + (frame[47] << 16) + (frame[48] << 8) + (frame[49]));

                //set indicators
                horizon_indicator.SetAttitudeIndicatorParameters(angle_tangage, angle_roulis);
                turn_indicator.SetTurnCoordinatorParameters(angle_roulis / 10, angle_roulis / 10);
                heading_indicator.SetHeadingIndicatorParameters(angle_nord);
                altimeter_indicator.SetAlimeterParameters((int)(altitude * 3.2808399));
                air_speed_indicator.SetAirSpeedIndicatorParameters((int)speed);
                vario_indicator.SetVerticalSpeedIndicatorParameters(((acc_z - 16383) * 6000) / 16383);

                toolStripStatusLabelAngles.Text = "Angles : " + Convert.ToString(angle_roulis) + "° , " + Convert.ToString(angle_tangage) + "° , " + Convert.ToString(angle_lacet)+"°";
                toolStripStatusLabelSpeed.Text = "Speed : " + Convert.ToString(speed);
                toolStripStatusLabelAltitude.Text = "Altitude = " + Convert.ToString(altitude) + "m";
                toolStripStatusLabelTemperature.Text = "Temperature : " + Convert.ToString(temperature) + "°C";
                toolStripStatusLabelPresssion.Text = "Pression : " + Convert.ToString(pressure) + "Pa";
                time++;
                
                points_roulis.Add(new Point((int)((time * panel1.Width / 250)), panel1.Height / 2 - (int)(((angle_roulis - 1) * panel1.Height) / 180) - 1));
                points_tangage.Add(new Point((int)((time * panel1.Width / 250)), panel1.Height / 2 - (int)(((angle_tangage - 1) * panel1.Height) / 180) - 1));
                points_lacet.Add(new Point((int)((time * panel1.Width / 250)), panel1.Height - (int)(((angle_lacet - 1) * panel1.Height) / 360) - 1));
                points_nord.Add(new Point((int)((time * panel1.Width / 250)), panel1.Height - (int)(((angle_nord - 1) * panel1.Height) / 360) - 1));


                points_acc_x.Add(new Point((int)((time * panel1.Width / 250)), panel1.Height / 2 - (int)(((acc_x - 1) * panel1.Height) / (0xFFFF / 1)) - 1));
                points_acc_y.Add(new Point((int)((time * panel1.Width / 250)), panel1.Height / 2 - (int)(((acc_y - 1) * panel1.Height) / (0xFFFF / 1)) - 1));
                points_acc_z.Add(new Point((int)((time * panel1.Width / 250)), panel1.Height / 2 - (int)(((acc_z - 0xffff / 4 - 1) * panel1.Height) / (0xFFFF / 1)) - 1));

                points_gyr_x.Add(new Point((int)((time * panel1.Width / 250)), panel1.Height / 2 - (int)(((gyr_x - 1) * panel1.Height) / (0xFFFF)) - 1));
                points_gyr_y.Add(new Point((int)((time * panel1.Width / 250)), panel1.Height / 2 - (int)(((gyr_y - 1) * panel1.Height) / (0xFFFF)) - 1));
                points_gyr_z.Add(new Point((int)((time * panel1.Width / 250)), panel1.Height / 2 - (int)(((gyr_z - 1) * panel1.Height) / (0xFFFF)) - 1));
                
                points_mag_x.Add(new Point((int)((time * panel1.Width / 250)), panel1.Height / 2 - (int)(((mag_x - 1) * panel1.Height) / (0x3FF)) - 1));
                points_mag_y.Add(new Point((int)((time * panel1.Width / 250)), panel1.Height / 2 - (int)(((mag_y - 1) * panel1.Height) / (0x3FF)) - 1));
                points_mag_z.Add(new Point((int)((time * panel1.Width / 250)), panel1.Height / 2 - (int)(((mag_z - 1) * panel1.Height) / (0x3FF)) - 1));

                points_mot_1.Add(new Point((int)((time * panel1.Width / 250)), panel1.Height - (int)(((front_l - 1) * panel1.Height) / (1000)) - 1));
                points_mot_2.Add(new Point((int)((time * panel1.Width / 250)), panel1.Height - (int)(((front_r - 1) * panel1.Height) / (1000)) - 1));
                points_mot_3.Add(new Point((int)((time * panel1.Width / 250)), panel1.Height - (int)(((rear_l - 1) * panel1.Height) / (1000)) - 1));
                points_mot_4.Add(new Point((int)((time * panel1.Width / 250)), panel1.Height - (int)(((rear_r - 1) * panel1.Height) / (1000)) - 1));

                //points_loop
                points_loop.Add(new Point((int)((time * panel1.Width / 250)), panel1.Height - (int)(((loop_time - 1) * panel1.Height) / (10000)) - 1));


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

                        if (points_nord[i].X - points_nord[0].X >= 0)
                        {
                            points_nord[i - 1] = new Point(points_nord[i].X - points_nord[0].X, points_nord[i].Y);
                        }
                        else
                        {
                            points_nord[i - 1] = new Point(0, points_nord[i].Y);
                        }

                        //acc
                        if (points_acc_x[i].X - points_acc_x[0].X >= 0)
                        {
                            points_acc_x[i - 1] = new Point(points_acc_x[i].X - points_acc_x[0].X, points_acc_x[i].Y);
                        }
                        else
                        {
                            points_acc_x[i - 1] = new Point(0, points_acc_x[i].Y);
                        }

                        if (points_acc_y[i].X - points_acc_y[0].X >= 0)
                        {
                            points_acc_y[i - 1] = new Point(points_acc_y[i].X - points_acc_y[0].X, points_acc_y[i].Y);
                        }
                        else
                        {
                            points_acc_y[i - 1] = new Point(0, points_acc_y[i].Y);
                        }

                        if (points_acc_z[i].X - points_acc_z[0].X >= 0)
                        {
                            points_acc_z[i - 1] = new Point(points_acc_z[i].X - points_acc_z[0].X, points_acc_z[i].Y);
                        }
                        else
                        {
                            points_acc_z[i - 1] = new Point(0, points_acc_z[i].Y);
                        }

                        //gyro
                        if (points_gyr_x[i].X - points_gyr_x[0].X >= 0)
                        {
                            points_gyr_x[i - 1] = new Point(points_gyr_x[i].X - points_gyr_x[0].X, points_gyr_x[i].Y);
                        }
                        else
                        {
                            points_gyr_x[i - 1] = new Point(0, points_gyr_x[i].Y);
                        }

                        if (points_gyr_y[i].X - points_gyr_y[0].X >= 0)
                        {
                            points_gyr_y[i - 1] = new Point(points_gyr_y[i].X - points_gyr_y[0].X, points_gyr_y[i].Y);
                        }
                        else
                        {
                            points_gyr_y[i - 1] = new Point(0, points_gyr_y[i].Y);
                        }

                        if (points_gyr_z[i].X - points_gyr_z[0].X >= 0)
                        {
                            points_gyr_z[i - 1] = new Point(points_gyr_z[i].X - points_gyr_z[0].X, points_gyr_z[i].Y);
                        }
                        else
                        {
                            points_gyr_z[i - 1] = new Point(0, points_gyr_z[i].Y);
                        }

                        //mag
                        if (points_mag_x[i].X - points_mag_x[0].X >= 0)
                        {
                            points_mag_x[i - 1] = new Point(points_mag_x[i].X - points_mag_x[0].X, points_mag_x[i].Y);
                        }
                        else
                        {
                            points_mag_x[i - 1] = new Point(0, points_mag_x[i].Y);
                        }

                        if (points_mag_y[i].X - points_mag_y[0].X >= 0)
                        {
                            points_mag_y[i - 1] = new Point(points_mag_y[i].X - points_mag_y[0].X, points_mag_y[i].Y);
                        }
                        else
                        {
                            points_mag_y[i - 1] = new Point(0, points_mag_y[i].Y);
                        }

                        if (points_mag_z[i].X - points_mag_z[0].X >= 0)
                        {
                            points_mag_z[i - 1] = new Point(points_mag_z[i].X - points_mag_z[0].X, points_mag_z[i].Y);
                        }
                        else
                        {
                            points_mag_z[i - 1] = new Point(0, points_mag_z[i].Y);
                        }

                        //moteur
                        if (points_mot_1[i].X - points_mot_1[0].X >= 0)
                        {
                            points_mot_1[i - 1] = new Point(points_mot_1[i].X - points_mot_1[0].X, points_mot_1[i].Y);
                        }
                        else
                        {
                            points_mot_1[i - 1] = new Point(0, points_mot_1[i].Y);
                        }

                        if (points_mot_2[i].X - points_mot_2[0].X >= 0)
                        {
                            points_mot_2[i - 1] = new Point(points_mot_2[i].X - points_mot_2[0].X, points_mot_2[i].Y);
                        }
                        else
                        {
                            points_mot_2[i - 1] = new Point(0, points_mot_2[i].Y);
                        }

                        if (points_mot_3[i].X - points_mot_3[0].X >= 0)
                        {
                            points_mot_3[i - 1] = new Point(points_mot_3[i].X - points_mot_3[0].X, points_mot_3[i].Y);
                        }
                        else
                        {
                            points_mot_3[i - 1] = new Point(0, points_mot_3[i].Y);
                        }

                        if (points_mot_4[i].X - points_mot_4[0].X >= 0)
                        {
                            points_mot_4[i - 1] = new Point(points_mot_4[i].X - points_mot_4[0].X, points_mot_4[i].Y);
                        }
                        else
                        {
                            points_mot_4[i - 1] = new Point(0, points_mot_4[i].Y);
                        }

                        //points_loop
                        if (points_loop[i].X - points_loop[0].X >= 0)
                        {
                            points_loop[i - 1] = new Point(points_loop[i].X - points_loop[0].X, points_loop[i].Y);
                        }
                        else
                        {
                            points_loop[i - 1] = new Point(0, points_loop[i].Y);
                        }
                        

                    }
                    points_roulis.RemoveRange(points_roulis.Count - 1, 1);
                    points_tangage.RemoveRange(points_tangage.Count - 1, 1);
                    points_lacet.RemoveRange(points_lacet.Count - 1, 1);
                    points_nord.RemoveRange(points_nord.Count - 1, 1);
                    points_acc_x.RemoveRange(points_acc_x.Count - 1, 1);
                    points_acc_y.RemoveRange(points_acc_y.Count - 1, 1);
                    points_acc_z.RemoveRange(points_acc_z.Count - 1, 1);
                    points_gyr_x.RemoveRange(points_gyr_x.Count - 1, 1);
                    points_gyr_y.RemoveRange(points_gyr_y.Count - 1, 1);
                    points_gyr_z.RemoveRange(points_gyr_z.Count - 1, 1);
                    points_mag_x.RemoveRange(points_mag_x.Count - 1, 1);
                    points_mag_y.RemoveRange(points_mag_y.Count - 1, 1);
                    points_mag_z.RemoveRange(points_mag_z.Count - 1, 1);
                    points_mot_1.RemoveRange(points_mot_1.Count - 1, 1);
                    points_mot_2.RemoveRange(points_mot_2.Count - 1, 1);
                    points_mot_3.RemoveRange(points_mot_3.Count - 1, 1);
                    points_mot_4.RemoveRange(points_mot_4.Count - 1, 1);
                    points_loop.RemoveRange(points_loop.Count - 1, 1);
                }
                panel1.Refresh();
                if (loop_set_all == true)
                {
                    SetAll(speed_track, 0, 0, 0);
                }
                else
                {
                    if(index_pid == 0)
                        SetPID(0, (short)numericUpDownProulis.Value, (short)numericUpDownIroulis.Value, (short)numericUpDownDroulis.Value);
                    if (index_pid == 1)
                        SetPID(1, (short)numericUpDownPtangage.Value, (short)numericUpDownItangage.Value, (short)numericUpDownDtangage.Value);
                    if (index_pid == 2)
                        SetPID(2, (short)numericUpDownPlacet.Value, (short)numericUpDownIlacet.Value, (short)numericUpDownDlacet.Value);
                }
            }
        }

        #region graph

        private void labelAttitude_Click(object sender, EventArgs e)
        {
            if (labelAttitude.Font.Style == FontStyle.Bold)
            {
                labelAttitude.Font = new Font(labelAttitude.Font, FontStyle.Regular);
            }
            else
            {
                labelAttitude.Font = new Font(labelAttitude.Font, FontStyle.Bold);
                labelAcc.Font = new Font(labelAcc.Font, FontStyle.Regular);
                labelGyro.Font = new Font(labelGyro.Font, FontStyle.Regular);
                labelMag.Font = new Font(labelMag.Font, FontStyle.Regular);
                labelMot.Font = new Font(labelMot.Font, FontStyle.Regular);
                labelLoop.Font = new Font(labelLoop.Font, FontStyle.Regular);
            }
        }

        private void labelAcc_Click(object sender, EventArgs e)
        {
            if (labelAcc.Font.Style == FontStyle.Bold)
            {
                labelAcc.Font = new Font(labelAcc.Font, FontStyle.Regular);
            }
            else
            {
                labelAcc.Font = new Font(labelAcc.Font, FontStyle.Bold);
                labelGyro.Font = new Font(labelGyro.Font, FontStyle.Regular);
                labelAttitude.Font = new Font(labelAttitude.Font, FontStyle.Regular);
                labelMag.Font = new Font(labelMag.Font, FontStyle.Regular);
                labelMot.Font = new Font(labelMot.Font, FontStyle.Regular);
                labelLoop.Font = new Font(labelLoop.Font, FontStyle.Regular);
            }
        }

        private void labelGyro_Click(object sender, EventArgs e)
        {
            if (labelGyro.Font.Style == FontStyle.Bold)
            {
                labelGyro.Font = new Font(labelGyro.Font, FontStyle.Regular);
            }
            else
            {
                labelGyro.Font = new Font(labelGyro.Font, FontStyle.Bold);
                labelAcc.Font = new Font(labelAcc.Font, FontStyle.Regular);
                labelAttitude.Font = new Font(labelAttitude.Font, FontStyle.Regular);
                labelMag.Font = new Font(labelMag.Font, FontStyle.Regular);
                labelMot.Font = new Font(labelMot.Font, FontStyle.Regular);
                labelLoop.Font = new Font(labelLoop.Font, FontStyle.Regular);
            }
        }

        private void labelMag_Click(object sender, EventArgs e)
        {
            if (labelMag.Font.Style == FontStyle.Bold)
            {
                labelMag.Font = new Font(labelMag.Font, FontStyle.Regular);
            }
            else
            {
                labelMag.Font = new Font(labelMag.Font, FontStyle.Bold);
                labelAcc.Font = new Font(labelAcc.Font, FontStyle.Regular);
                labelGyro.Font = new Font(labelGyro.Font, FontStyle.Regular);
                labelAttitude.Font = new Font(labelAttitude.Font, FontStyle.Regular);
                labelMot.Font = new Font(labelMot.Font, FontStyle.Regular);
                labelLoop.Font = new Font(labelLoop.Font, FontStyle.Regular);
            }
        }
        
        private void labelLoop_Click(object sender, EventArgs e)
        {
            if (labelLoop.Font.Style == FontStyle.Bold)
            {
                labelMag.Font = new Font(labelLoop.Font, FontStyle.Regular);
            }
            else
            {
                labelLoop.Font = new Font(labelLoop.Font, FontStyle.Bold);
                labelAcc.Font = new Font(labelAcc.Font, FontStyle.Regular);
                labelGyro.Font = new Font(labelGyro.Font, FontStyle.Regular);
                labelAttitude.Font = new Font(labelAttitude.Font, FontStyle.Regular);
                labelMot.Font = new Font(labelMot.Font, FontStyle.Regular);
                labelMag.Font = new Font(labelMag.Font, FontStyle.Regular);
            }
        }

        private void labelMot_Click(object sender, EventArgs e)
        {

            if (labelMot.Font.Style == FontStyle.Bold)
            {
                labelMot.Font = new Font(labelMot.Font, FontStyle.Regular);
            }
            else
            {
                labelMot.Font = new Font(labelMot.Font, FontStyle.Bold);
                labelAcc.Font = new Font(labelAcc.Font, FontStyle.Regular);
                labelAttitude.Font = new Font(labelAttitude.Font, FontStyle.Regular);
                labelMag.Font = new Font(labelMag.Font, FontStyle.Regular);
                labelGyro.Font = new Font(labelGyro.Font, FontStyle.Regular);
                labelLoop.Font = new Font(labelLoop.Font, FontStyle.Regular);
            }
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            g = e.Graphics;
            if (points_roulis.Count > 1)
            {
                if (labelAttitude.Font.Style == FontStyle.Bold)
                {
                    g.DrawLines(new Pen(Color.Red), points_roulis.ToArray());
                    g.DrawLines(new Pen(Color.Green), points_tangage.ToArray());
                    g.DrawLines(new Pen(Color.Blue), points_lacet.ToArray());
                    g.DrawLines(new Pen(Color.YellowGreen), points_nord.ToArray());
                    
                    labelMax.Text = "+180";
                    labelMid.Text = "0";
                    labelMin.Text = "-180";
                }

                if (labelAcc.Font.Style == FontStyle.Bold)
                {
                    g.DrawLines(new Pen(Color.Red), points_acc_x.ToArray());
                    g.DrawLines(new Pen(Color.Green), points_acc_y.ToArray());
                    g.DrawLines(new Pen(Color.Blue), points_acc_z.ToArray());
                    labelMax.Text = "+32767";
                    labelMid.Text = "0";
                    labelMin.Text = "-32767";
                }

                if (labelGyro.Font.Style == FontStyle.Bold)
                {
                    g.DrawLines(new Pen(Color.Red), points_gyr_x.ToArray());
                    g.DrawLines(new Pen(Color.Green), points_gyr_y.ToArray());
                    g.DrawLines(new Pen(Color.Blue), points_gyr_z.ToArray());
                    labelMax.Text = "+32767";
                    labelMid.Text = "0";
                    labelMin.Text = "-32767";
                }

                if (labelMag.Font.Style == FontStyle.Bold)
                {
                    g.DrawLines(new Pen(Color.Red), points_mag_x.ToArray());
                    g.DrawLines(new Pen(Color.Green), points_mag_y.ToArray());
                    g.DrawLines(new Pen(Color.Blue), points_mag_z.ToArray());
                    labelMax.Text = "+512";
                    labelMid.Text = "0";
                    labelMin.Text = "-512";
                }

                if (labelMot.Font.Style == FontStyle.Bold)
                {
                    g.DrawLines(new Pen(Color.Red), points_mot_1.ToArray());
                    g.DrawLines(new Pen(Color.Green), points_mot_2.ToArray());
                    g.DrawLines(new Pen(Color.Blue), points_mot_3.ToArray());
                    g.DrawLines(new Pen(Color.YellowGreen), points_mot_4.ToArray());
                    labelMax.Text = "1000";
                    labelMid.Text = speed.ToString();
                    labelMin.Text = "0";
                }

                if (labelLoop.Font.Style == FontStyle.Bold)
                {
                    g.DrawLines(new Pen(Color.Red), points_loop.ToArray());
                    labelMax.Text = "10000";
                    labelMid.Text = loop_time.ToString();
                    labelMin.Text = "0";
                }

            }
            g.Dispose();
        }

        #endregion
        
        #region View
        private void cockpitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            
        }
        #endregion

        private void numericUpDownRoulis_ValueChanged(object sender, EventArgs e)
        {
            loop_set_all = false;
            index_pid = 0;
        }

        private void numericUpDowntangage_ValueChanged(object sender, EventArgs e)
        {
            loop_set_all = false;
            index_pid = 1;

        }

        private void numericUpDownLacet_ValueChanged(object sender, EventArgs e)
        {
            loop_set_all = false;
            index_pid = 2;
        }



        

        


        

        


        






    }
}
