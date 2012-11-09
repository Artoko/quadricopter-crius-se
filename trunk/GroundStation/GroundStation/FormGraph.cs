using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using ZedGraph;

namespace GroundStation
{
    public partial class FormGraph : Form
    {

        PointPairList courbe1 = new PointPairList();
        PointPairList courbe2 = new PointPairList();
        PointPairList courbe3 = new PointPairList();
        PointPairList courbe4 = new PointPairList();
        PointPairList courbe5 = new PointPairList();
        PointPairList courbe6 = new PointPairList();
        PointPairList courbe7 = new PointPairList();
        PointPairList courbe8 = new PointPairList();
        PointPairList courbe9 = new PointPairList();
        PointPairList courbe10 = new PointPairList();
        PointPairList courbe11 = new PointPairList();
        
        public int timeout = 0;
        GraphPane myPane1;

        public FormGraph()
        {
            InitializeComponent();
            timer_tick.Enabled = true;
            timer_tick.Interval = 50;
            myPane1 = zedGraphControl1.GraphPane;

            myPane1.AddCurve("roulis", courbe1, Color.Red, SymbolType.None);
            myPane1.AddCurve("tangage", courbe2, Color.Blue, SymbolType.None);
            myPane1.AddCurve("lacet", courbe3, Color.DarkGreen, SymbolType.None);
            myPane1.AddCurve("altitude", courbe4, Color.Brown, SymbolType.None);
            myPane1.AddCurve("pid roulis", courbe5, Color.YellowGreen, SymbolType.None);
            myPane1.AddCurve("pid tangage", courbe6, Color.Green, SymbolType.None);
            myPane1.AddCurve("front motor R", courbe7, Color.DarkCyan, SymbolType.None);
            myPane1.AddCurve("front motor L", courbe8, Color.BlueViolet, SymbolType.None);
            myPane1.AddCurve("rear motor R", courbe9, Color.Chartreuse, SymbolType.None);
            myPane1.AddCurve("rear motor L", courbe10, Color.Chocolate, SymbolType.None);
            myPane1.AddCurve("vitesse", courbe11, Color.Coral, SymbolType.None);
            GroundStationMainForm.serial.AddCallback(IncommingMessage);
        }

        private void FormGraph_FormClosing(object sender, FormClosingEventArgs e)
        {
            GroundStationMainForm.serial.DeleteCallback(IncommingMessage);
        }
        
        
        public void IncommingMessage(string message)
        {
            try
            {
                string[] param = message.Replace("\0", "").Replace(" ", "").Split(',');
                if (checkBoxRoulis.Checked == true)
                {
                    courbe1.Add(timeout, System.Convert.ToInt16(param[0]));
                }
                if (checkBoxtangage.Checked == true)
                {
                    courbe2.Add(timeout, System.Convert.ToInt16(param[1]));
                }
                if (checkBoxlacet.Checked == true)
                {
                    courbe3.Add(timeout, System.Convert.ToInt16(param[2]));
                }
                if (checkBoxaltitude.Checked == true)
                {
                    courbe4.Add(timeout, System.Convert.ToInt16(param[3]));
                }
                if (checkBoxpidroulis.Checked == true)
                {
                    courbe5.Add(timeout, System.Convert.ToInt16(param[4]));
                }
                if (checkBoxpidtangage.Checked == true)
                {
                    courbe6.Add(timeout, System.Convert.ToInt16(param[5]));
                }
                if (checkBoxmotorFR.Checked == true)
                {
                    courbe7.Add(timeout, System.Convert.ToInt16(param[6]));
                }
                if (checkBoxmotorFL.Checked == true)
                {
                    courbe8.Add(timeout, System.Convert.ToInt16(param[7]));
                }
                if (checkBoxmotorRR.Checked == true)
                {
                    courbe9.Add(timeout, System.Convert.ToInt16(param[8]));
                }
                if (checkBoxmotorRL.Checked == true)
                {
                    courbe10.Add(timeout, System.Convert.ToInt16(param[9]));
                }
                if (checkBoxvitesse.Checked == true)
                {
                    courbe11.Add(timeout, System.Convert.ToInt16(param[10]));
                }

                zedGraphControl1.AxisChange();
            }
            catch
            { 
            }
        }

        private void timer_tick_Tick(object sender, EventArgs e)
        {
            timeout++;
            zedGraphControl1.Refresh();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            courbe1.Clear();
            courbe2.Clear();
            courbe3.Clear();
            courbe4.Clear();
            courbe5.Clear();
            courbe6.Clear();
            courbe7.Clear();
            courbe8.Clear();
            courbe9.Clear();
            courbe10.Clear();
            courbe11.Clear();
            timeout = 0;
            zedGraphControl1.AxisChange();
            zedGraphControl1.Refresh();
        }
    }
}
