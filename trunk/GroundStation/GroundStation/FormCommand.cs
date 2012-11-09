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
        public FormCommand()
        {
            InitializeComponent();
        }

        private void Speedbutton_Click(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage("*0-0##");
        }

        private void PowerTrackBar_ValueChanged(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage("*0-" + PowerTrackBar.Value + "##");
            labelspeed.Text = "speed : " + PowerTrackBar.Value.ToString();
        }

        private void RoulisTrackBar_ValueChanged(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage("*1-" + trackBarRoulis.Value + "-" + trackBarTangage.Value + "-" + trackBarLacet.Value + "##");
            labelroulis.Text = "roulis angle : " + trackBarRoulis.Value.ToString();
        }

        private void tangageTrackBar_ValueChanged(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage("*1-" + trackBarRoulis.Value + "-" + trackBarTangage.Value + "-" + trackBarLacet.Value + "##");
            labeltangage.Text = "tangage angle : " + trackBarTangage.Value.ToString();
        }

        private void LacetTrackBar_ValueChanged(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage("*1-" + trackBarRoulis.Value + "-" + trackBarTangage.Value + "-" + trackBarLacet.Value + "##");
            labelLacet.Text = "lacet angle : " + trackBarLacet.Value.ToString();
        }

        private void buttonReset_Click(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage("*4-0##");
        }

        private void buttonReseteeprom_Click(object sender, EventArgs e)
        {
            GroundStationMainForm.serial.SendMessage("*4-1##");
        }

       
    }
}
