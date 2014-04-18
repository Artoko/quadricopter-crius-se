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

        PointPairList courbe_roulis = new PointPairList();
        PointPairList courbe_tangage = new PointPairList();
        PointPairList courbe_lacet = new PointPairList();
        PointPairList courbe_nord = new PointPairList();
        PointPairList courbe_altitude = new PointPairList();
        PointPairList courbe_pid_roulis = new PointPairList();
        PointPairList courbe_pid_tangage = new PointPairList();
        PointPairList courbe_pid_lacet = new PointPairList();
        PointPairList courbe_pression = new PointPairList();
        PointPairList courbe_temperature = new PointPairList();
        PointPairList courbe_moteur_1 = new PointPairList();
        PointPairList courbe_moteur_2 = new PointPairList();
        PointPairList courbe_moteur_3 = new PointPairList();
        PointPairList courbe_moteur_4 = new PointPairList();
        
        public int timeout = 0;
        GraphPane myPane1;

        public FormGraph()
        {
            InitializeComponent();
            timer_tick.Enabled = true;
            timer_tick.Interval = 50;
            myPane1 = zedGraphControl1.GraphPane;

            myPane1.AddCurve("roulis"       , courbe_roulis     , Color.Red         , SymbolType.None);
            myPane1.AddCurve("tangage"      , courbe_tangage    , Color.Blue        , SymbolType.None);
            myPane1.AddCurve("lacet"        , courbe_lacet      , Color.DarkGreen   , SymbolType.None);
            myPane1.AddCurve("nord"         , courbe_nord       , Color.Chocolate   , SymbolType.None);
            myPane1.AddCurve("altitude"     , courbe_altitude   , Color.Brown       , SymbolType.None);
            myPane1.AddCurve("pid roulis"   , courbe_pid_roulis , Color.BlueViolet  , SymbolType.None);
            myPane1.AddCurve("pid tangage"  , courbe_pid_tangage, Color.Green       , SymbolType.None);
            myPane1.AddCurve("pid lacet"    , courbe_pid_lacet  , Color.Firebrick   , SymbolType.None);
            myPane1.AddCurve("moteur 1"     , courbe_moteur_1   , Color.Aqua        , SymbolType.None);
            myPane1.AddCurve("moteur 2"     , courbe_moteur_2   , Color.DarkGray    , SymbolType.None);
            myPane1.AddCurve("moteur 3"     , courbe_moteur_3   , Color.LightSeaGreen , SymbolType.None);
            myPane1.AddCurve("moteur 4"     , courbe_moteur_4   , Color.LightBlue   , SymbolType.None);
            myPane1.AddCurve("pression"     , courbe_pression   , Color.IndianRed   , SymbolType.None);
            myPane1.AddCurve("temperature"  , courbe_temperature, Color.Khaki       , SymbolType.None);
        }

        private void FormGraph_FormClosing(object sender, FormClosingEventArgs e)
        {
        }
        
        public void IncommingMessage(string message)
        {
            try
            {
                if (courbe_roulis.Count == 500)
                {
                    courbe_roulis.RemoveAt(0);
                    courbe_tangage.RemoveAt(0);
                    courbe_lacet.RemoveAt(0);
                    courbe_nord.RemoveAt(0);
                    courbe_altitude.RemoveAt(0);
                    courbe_pid_roulis.RemoveAt(0);
                    courbe_pid_tangage.RemoveAt(0);
                    courbe_pid_lacet.RemoveAt(0);
                    courbe_pression.RemoveAt(0);
                    courbe_temperature.RemoveAt(0);
                    courbe_moteur_1.RemoveAt(0);
                    courbe_moteur_2.RemoveAt(0);
                    courbe_moteur_3.RemoveAt(0);
                    courbe_moteur_4.RemoveAt(0);
                }
                string[] param = message.Replace("\0", "").Replace(" ", "").Split(',');
                courbe_roulis.Add(timeout, System.Convert.ToInt16(param[0]));
                courbe_tangage.Add(timeout, System.Convert.ToInt16(param[1]));
                courbe_lacet.Add(timeout, System.Convert.ToInt16(param[2]));
                courbe_nord.Add(timeout, System.Convert.ToInt16(param[3]));
                courbe_altitude.Add(timeout, System.Convert.ToInt16(param[4]));
                courbe_pid_roulis.Add(timeout, -1 * System.Convert.ToInt16(param[5]));
                courbe_pid_tangage.Add(timeout, -1 * System.Convert.ToInt16(param[6]));
                courbe_pid_lacet.Add(timeout, -1 * System.Convert.ToInt16(param[7]));
                courbe_moteur_1.Add(timeout, System.Convert.ToInt16(param[8]));
                courbe_moteur_2.Add(timeout, System.Convert.ToInt16(param[9]));
                courbe_moteur_3.Add(timeout, System.Convert.ToInt16(param[10]));
                courbe_moteur_4.Add(timeout, System.Convert.ToInt16(param[11]));
                courbe_pression.Add(timeout, System.Convert.ToInt16(param[13]));
                courbe_temperature.Add(timeout, System.Convert.ToInt16(param[14]));

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
                if (checkBoxMoteur1.Checked == true)
                {
                    myPane1.CurveList[8].IsVisible = true;
                }
                else
                {
                    myPane1.CurveList[8].IsVisible = false;
                }
                if (checkBoxMoteur2.Checked == true)
                {
                    myPane1.CurveList[9].IsVisible = true;
                }
                else
                {
                    myPane1.CurveList[9].IsVisible = false;
                }
                if (checkBoxMoteur3.Checked == true)
                {
                    myPane1.CurveList[10].IsVisible = true;
                }
                else
                {
                    myPane1.CurveList[10].IsVisible = false;
                }
                if (checkBoxMoteur4.Checked == true)
                {
                    myPane1.CurveList[11].IsVisible = true;
                }
                else
                {
                    myPane1.CurveList[11].IsVisible = false;
                }

                if (checkBoxpression.Checked == true)
                {
                    myPane1.CurveList[12].IsVisible = true;
                }
                else
                {
                    myPane1.CurveList[12].IsVisible = false;
                }
                if (checkBoxtemperature.Checked == true)
                {
                    myPane1.CurveList[13].IsVisible = true;
                }
                else
                {
                    myPane1.CurveList[13].IsVisible = false;
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
            courbe_roulis.Clear();
            courbe_tangage.Clear();
            courbe_lacet.Clear();
            courbe_nord.Clear();
            courbe_altitude.Clear();
            courbe_pid_roulis.Clear();
            courbe_pid_tangage.Clear();
            courbe_pid_lacet.Clear();
            courbe_pression.Clear();
            courbe_temperature.Clear();
            courbe_moteur_1.Clear();
            courbe_moteur_2.Clear();
            courbe_moteur_3.Clear();
            courbe_moteur_4.Clear();
            timeout = 0;
            zedGraphControl1.AxisChange();
            zedGraphControl1.Refresh();
        }

        private void checkBoxlacet_CheckedChanged(object sender, EventArgs e)
        {

        }
    }
}
