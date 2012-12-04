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
        private bool combine_roulis_tangage = false;
        public FormCommand()
        {
            InitializeComponent();
        }

        private void Speedbutton_Click(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage("*0+0##");
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
                combine_roulis_tangage = true;
                trackBarTangage.Value = trackBarRoulis.Value;
            }
            else
            {
                combine_roulis_tangage = false;
            }
            GroundStationMainForm.serial.SendMessage(FormatString());
            labelroulis.Text = "roulis angle : " + trackBarRoulis.Value.ToString();
        }

        private void tangageTrackBar_ValueChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked)
            {
                combine_roulis_tangage = true;
                trackBarRoulis.Value = trackBarTangage.Value;
            }
            else
            {
                combine_roulis_tangage = false;
            }
            GroundStationMainForm.serial.SendMessage(FormatString());
            labeltangage.Text = "tangage angle : " + trackBarTangage.Value.ToString();
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked)
            {
                combine_roulis_tangage = true;
            }
            else
            {
                combine_roulis_tangage = false;
            }
        }

        private void LacetTrackBar_ValueChanged(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage(FormatString());
            labelLacet.Text = "lacet angle : " + trackBarLacet.Value.ToString();
        }

        private void buttonReset_Click(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage("*4+0##");
        }

        private void buttonReseteeprom_Click(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage("*4+1##");
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

        

       
    }
}
