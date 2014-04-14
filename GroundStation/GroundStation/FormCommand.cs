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
        delegate void FillPIDBox(int index,short value);
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
                    if (tab.Count() == 4)
                    {
                        short index = Convert.ToInt16(tab[0]);
                        short P = Convert.ToInt16(tab[1]);
                        short I = Convert.ToInt16(tab[2]);
                        short D = Convert.ToInt16(tab[3]);

                        Invoke((FillPIDBox)WritenumericUpDownP, index, P);
                        Invoke((FillPIDBox)WritenumericUpDownI, index, I);
                        Invoke((FillPIDBox)WritenumericUpDownD, index, D);
                    }
                }
                if (message.Contains("WEATHER:"))
                {
                    message = message.Substring(message.IndexOf("WEATHER:"), message.Length - message.IndexOf("WEATHER:"));
                    string[] tab = message.Remove(0, 8).Split(',');
                    if (tab.Count() == 1)
                    {
                        label4.Invoke((FillWeatherBox)WriteWeather, tab[0]);
                    }
                }
            }
            catch { }
        }
        void WriteWeather(string value)
        {
            if (value == "0")
            {
                label4.Text = "ensoleillé";
            }
            else if (value == "1")
            {
                label4.Text = "nuageux";
            }
            else
            {
                label4.Text = "pluvieux";
            }
        }
        void WritenumericUpDownP(int index, short value)
        {
            if (index == 0)
                numericUpDownP.Value = value;
            if (index == 1)
                numericUpDown4.Value = value;
            if (index == 2)
                numericUpDown6.Value = value;
            if (index == 3)
                numericUpDown9.Value = value;
        }
        void WritenumericUpDownI(int index, short value)
        {
            if (index == 0)
                numericUpDownI.Value = value;
            if (index == 1)
                numericUpDown3.Value = value;
            if (index == 2)
                numericUpDown5.Value = value;
            if (index == 3)
                numericUpDown8.Value = value;
        }
        void WritenumericUpDownD(int index, short value)
        {
            if (index == 0)
                numericUpDownD.Value = value;
            if (index == 1)
                numericUpDown2.Value = value;
            if (index == 2)
                numericUpDown1.Value = value;
            if (index == 3)
                numericUpDown7.Value = value;
        }

        private void Speedbutton_Click(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage("*1+0##");
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
            GroundStationMainForm.serial.SendMessage("*1+" + PowerTrackBar.Value + "##");
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
            GroundStationMainForm.serial.SendMessage("*5+0##");
            PowerTrackBar.Value = 0;
            trackBarRoulis.Value = 0;
            trackBarLacet.Value = 0;
            trackBarTangage.Value = 0;
        }

        private void buttonReseteeprom_Click(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage("*5+1##");
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
            string frame = "*4+1+0";
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
            GroundStationMainForm.serial.SendMessage("*4+0+0##");
        }

        private void buttonRepportData_Click(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage("*6+0##");

        }
        
        private string FormatString()
        {
            string frame = "*2";
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
            GroundStationMainForm.serial.SendMessage("*3+2##");
        }

        private void buttonAltitude_Click(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage("*3+1##");
        }

        private void button9_Click(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage("*3+3+" + numericUpDown10.Value + "##");
        }

        private void FormCommand_Load(object sender, EventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {
            string frame = "*4+1+1";
            if (numericUpDown4.Value >= 0)
            {
                frame += "+" + numericUpDown4.Value;
            }
            else
            {
                frame += numericUpDown4.Value;
            }
            if (numericUpDown3.Value >= 0)
            {
                frame += "+" + numericUpDown3.Value;
            }
            else
            {
                frame += numericUpDown3.Value;
            }
            if (numericUpDown2.Value >= 0)
            {
                frame += "+" + numericUpDown2.Value + "##";
            }
            else
            {
                frame += numericUpDown2.Value + "##";
            }
            GroundStationMainForm.serial.SendMessage(frame);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage("*4+0+1##");
        }

        private void button6_Click(object sender, EventArgs e)
        {
            string frame = "*4+1+2";
            if (numericUpDown6.Value >= 0)
            {
                frame += "+" + numericUpDown6.Value;
            }
            else
            {
                frame += numericUpDown6.Value;
            }
            if (numericUpDown5.Value >= 0)
            {
                frame += "+" + numericUpDown5.Value;
            }
            else
            {
                frame += numericUpDown5.Value;
            }
            if (numericUpDown1.Value >= 0)
            {
                frame += "+" + numericUpDown1.Value + "##";
            }
            else
            {
                frame += numericUpDown1.Value + "##";
            }
            GroundStationMainForm.serial.SendMessage(frame);
        }

        private void button8_Click(object sender, EventArgs e)
        {
            string frame = "*4+1+3";
            if (numericUpDown9.Value >= 0)
            {
                frame += "+" + numericUpDown9.Value;
            }
            else
            {
                frame += numericUpDown9.Value;
            }
            if (numericUpDown8.Value >= 0)
            {
                frame += "+" + numericUpDown8.Value;
            }
            else
            {
                frame += numericUpDown8.Value;
            }
            if (numericUpDown7.Value >= 0)
            {
                frame += "+" + numericUpDown7.Value + "##";
            }
            else
            {
                frame += numericUpDown7.Value + "##";
            }
            GroundStationMainForm.serial.SendMessage(frame);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage("*4+0+2##");
        }

        private void button7_Click(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage("*4+0+3##");
        }

        

        

        

        

        

        

        

       
    }
}
