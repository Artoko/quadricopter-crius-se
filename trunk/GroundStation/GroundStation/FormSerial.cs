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
    public partial class FormSerial : Form
    {
        delegate void FillListBox(string value);

        public FormSerial()
        {
            InitializeComponent();
            GroundStationMainForm.serial.AddCallback(IncommingMessage);
        }
        private void FormSerial_FormClosing(object sender, FormClosingEventArgs e)
        {
            GroundStationMainForm.serial.DeleteCallback(IncommingMessage);
        }

        
        private void Clearbutton_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
        }

        public void IncommingMessage(string message)
        {
            try
            {
                listBox1.Invoke((FillListBox)AddItemListBox, message);
            }
            catch { }
        }

        void AddItemListBox(string value)
        {
            value = value.Replace("\0", "");
            if (value.Contains(',') && (value.Split(',').Length == 4))
            {
                listBox1.Items.Add(
                            value.Split(',')[0] +
                    "\t" + value.Split(',')[1] +
                    "\t" + value.Split(',')[2] +
                    "\t" + value.Split(',')[3] //+
                    //"\t" + value.Split(',')[4] +
                    //"\t" + value.Split(',')[5] +
                    //"\t" + value.Split(',')[6] + "\t"
                    );
            }
            else 
            {
                listBox1.Items.Add(value);
            }
            listBox1.SelectedIndex = listBox1.Items.Count - 1;
        }

        

        
    }
}
