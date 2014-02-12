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
            myPane1.AddCurve("nord", courbe4, Color.Chocolate, SymbolType.None);
            myPane1.AddCurve("altitude", courbe5, Color.Brown, SymbolType.None);
            myPane1.AddCurve("pid roulis", courbe6, Color.BlueViolet, SymbolType.None);
            myPane1.AddCurve("pid tangage", courbe7, Color.Green, SymbolType.None);
            myPane1.AddCurve("pid lacet", courbe8, Color.Firebrick, SymbolType.None);
            myPane1.AddCurve("pression", courbe9, Color.IndianRed, SymbolType.None);
            myPane1.AddCurve("temperature", courbe10, Color.Khaki, SymbolType.None);
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
                courbe1.Add(timeout, System.Convert.ToInt16(param[0]));
                courbe2.Add(timeout, System.Convert.ToInt16(param[1]));
                courbe3.Add(timeout, System.Convert.ToInt16(param[2]));
                courbe4.Add(timeout, System.Convert.ToInt16(param[3]));
                courbe5.Add(timeout, System.Convert.ToInt16(param[4]));
                courbe6.Add(timeout, System.Convert.ToInt16(param[5]));
                courbe7.Add(timeout, System.Convert.ToInt16(param[6]));
                courbe8.Add(timeout, System.Convert.ToInt16(param[7]));
                courbe9.Add(timeout, System.Convert.ToInt16(param[8]));
                courbe10.Add(timeout, System.Convert.ToInt16(param[9]));
                if (checkBoxRoulis.Checked == true)
                {
                    myPane1.CurveList[0].IsVisible = true;
                }
                else
                {
                    myPane1.CurveList[0].IsVisible = false;
                }
                if (checkBoxtangage.Checked == true)
                {
                    myPane1.CurveList[1].IsVisible = true;
                }
                else
                {
                    myPane1.CurveList[1].IsVisible = false;
                }
                if (checkBoxlacet.Checked == true)
                {
                    myPane1.CurveList[2].IsVisible = true;
                }
                else
                {
                    myPane1.CurveList[2].IsVisible = false;
                }
                if (checkBoxnord.Checked == true)
                {
                    myPane1.CurveList[3].IsVisible = true;
                }
                else
                {
                    myPane1.CurveList[3].IsVisible = false;
                }
                if (checkBoxaltitude.Checked == true)
                {
                    myPane1.CurveList[4].IsVisible = true;
                }
                else
                {
                    myPane1.CurveList[4].IsVisible = false;
                }
                if (checkBoxpidroulis.Checked == true)
                {
                    myPane1.CurveList[5].IsVisible = true;
                }
                else
                {
                    myPane1.CurveList[5].IsVisible = false;
                }
                if (checkBoxpidtangage.Checked == true)
                {
                    myPane1.CurveList[6].IsVisible = true;
                }
                else
                {
                    myPane1.CurveList[6].IsVisible = false;
                }
                if (checkBoxpidlacet.Checked == true)
                {
                    myPane1.CurveList[7].IsVisible = true;
                }
                else
                {
                    myPane1.CurveList[7].IsVisible = false;
                }
                if (checkBoxpression.Checked == true)
                {
                    myPane1.CurveList[8].IsVisible = true;
                }
                else
                {
                    myPane1.CurveList[8].IsVisible = false;
                }
                if (checkBoxtemperature.Checked == true)
                {
                    myPane1.CurveList[9].IsVisible = true;
                }
                else
                {
                    myPane1.CurveList[9].IsVisible = false;
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
            timeout = 0;
            zedGraphControl1.AxisChange();
            zedGraphControl1.Refresh();
        }

        private void checkBoxlacet_CheckedChanged(object sender, EventArgs e)
        {

        }
    }
}
