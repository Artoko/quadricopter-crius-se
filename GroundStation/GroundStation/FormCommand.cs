using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace GroundStation
{
    public partial class FormCommand : Form
    {
        delegate void FillPIDBox(short value);
        delegate void FillWeatherBox(string value);


        public FormCommand()
        {
            InitializeComponent();

            GroundStationMainForm.serial.AddCallback(IncommingMessage);
        }
        private void FormCommand_FormClosing(object sender, FormClosingEventArgs e)
        {
            GroundStationMainForm.serial.DeleteCallback(IncommingMessage);
        }


        public void IncommingMessage(string message)
        {
            try
            {
                if (message.Contains("PID:"))
                {
                    message = message.Substring(message.IndexOf("PID:"), message.Length - message.IndexOf("PID:"));
                    string [] tab = message.Remove(0, 4).Split(',');
                    if (tab.Count() == 3)
                    {
                        short P = Convert.ToInt16(tab[0]);
                        short I = Convert.ToInt16(tab[1]);
                        short D = Convert.ToInt16(tab[2]);

                        numericUpDownP.Invoke((FillPIDBox)WritenumericUpDownP, P);
                        numericUpDownI.Invoke((FillPIDBox)WritenumericUpDownI, I);
                        numericUpDownD.Invoke((FillPIDBox)WritenumericUpDownD, D);
                    }
                }
                if (message.Contains("WEATHER:"))
                {
                    message = message.Substring(message.IndexOf("WEATHER:"), message.Length - message.IndexOf("WEATHER:"));
                    string[] tab = message.Remove(0, 8).Split(',');
                    if (tab.Count() == 1)
                    {
                        label_weather.Invoke((FillWeatherBox)WriteWeather, tab[0]);
                    }
                }
            }
            catch { }
        }
        void WriteWeather(string value)
        {
            if (value == "0")
            {
                label_weather.Text = "ensoleil";
            }
            else if (value == "1")
            {
                label_weather.Text = "nuageux";
            }
            else
            {
                label_weather.Text = "pluvieux";
            }
        }
        void WritenumericUpDownP(short value)
        {
            numericUpDownP.Value = value;
        }
        void WritenumericUpDownI(short value)
        {
            numericUpDownI.Value = value;
        }
        void WritenumericUpDownD(short value)
        {
            numericUpDownD.Value = value;
        }

        private void Speedbutton_Click(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage("*0+0##");
            PowerTrackBar.Value = 0;
            trackBarRoulis.Value = 0;
            trackBarLacet.Value = 0;
            trackBarTangage.Value = 0;
        }

        private void PowerTrackBar_ValueChanged(object sender, EventArgs e)
        {
            if (checkBoxFullSpeed.Checked == true)
            {
                PowerTrackBar.Maximum = 1000;
                if (PowerTrackBar.Value > 1000) PowerTrackBar.Value = 1000;
            }
            else
            {
                PowerTrackBar.Maximum = 500;
                if (PowerTrackBar.Value > 500) PowerTrackBar.Value = 500;
            }
            GroundStationMainForm.serial.SendMessage("*0+" + PowerTrackBar.Value + "##");
            labelspeed.Text = "speed : " + PowerTrackBar.Value.ToString();
        }

        private void RoulisTrackBar_ValueChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked)
            {
                trackBarTangage.Value = trackBarRoulis.Value;
            }
            GroundStationMainForm.serial.SendMessage(FormatString());
            labelroulis.Text = "roulis angle : " + trackBarRoulis.Value.ToString();
        }

        private void tangageTrackBar_ValueChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked)
            {
                trackBarRoulis.Value = trackBarTangage.Value;
            }
            GroundStationMainForm.serial.SendMessage(FormatString());
            labeltangage.Text = "tangage angle : " + trackBarTangage.Value.ToString();
        }

        

        private void LacetTrackBar_ValueChanged(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage(FormatString());
            labelLacet.Text = "lacet angle : " + trackBarLacet.Value.ToString();
        }

        private void buttonReset_Click(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage("*4+0##");
            PowerTrackBar.Value = 0;
            trackBarRoulis.Value = 0;
            trackBarLacet.Value = 0;
            trackBarTangage.Value = 0;
        }

        private void buttonReseteeprom_Click(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage("*4+1##");
            PowerTrackBar.Value = 0;
            trackBarRoulis.Value = 0;
            trackBarLacet.Value = 0;
            trackBarTangage.Value = 0;
        }

        private void checkBoxFullSpeed_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxFullSpeed.Checked == true)
            {
                PowerTrackBar.Maximum = 1000;
            }
            else
            {
                PowerTrackBar.Maximum = 500;
            }
            if(PowerTrackBar.Value > PowerTrackBar.Maximum)
            {
                PowerTrackBar.Value = PowerTrackBar.Maximum;
               
            }
            labelspeed.Text = "speed : " + PowerTrackBar.Value.ToString();
        }

        private void ButtonWrite_Click(object sender, EventArgs e)
        {
            string frame = "*3+1+" + numericUpDownindex.Value;
            if (numericUpDownP.Value >= 0)
            {
                frame += "+" + numericUpDownP.Value;
            }
            else
            {
                frame += numericUpDownP.Value;
            }
            if (numericUpDownI.Value >= 0)
            {
                frame += "+" + numericUpDownI.Value;
            }
            else
            {
                frame += numericUpDownI.Value;
            }
            if (numericUpDownD.Value >= 0)
            {
                frame += "+" + numericUpDownD.Value + "##";
            }
            else
            {
                frame += numericUpDownD.Value + "##";
            }
            GroundStationMainForm.serial.SendMessage(frame);
        }

        private void ButtonRead_Click(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage("*3+0+" + numericUpDownindex.Value + "##");
        }

        private void buttonRepportData_Click(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage("*5+0##");

        }
        
        private string FormatString()
        {
            string frame = "*1";
            if (trackBarRoulis.Value >= 0)
            {
                frame += "+" + trackBarRoulis.Value;
            }
            else
            {
                frame += trackBarRoulis.Value;
            }
            if (trackBarTangage.Value >= 0)
            {
                frame += "+" + trackBarTangage.Value;
            }
            else
            {
                frame += trackBarTangage.Value;
            }
            if (trackBarLacet.Value >= 0)
            {
                frame += "+" + trackBarLacet.Value + "##";
            }
            else
            {
                frame += trackBarLacet.Value + "##";
            }
            return frame;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage("*2+0##");

        }

        private void buttonAltitude_Click(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage("*2+1##");
        }

        

        

        

        

        

        

       
    }
}
