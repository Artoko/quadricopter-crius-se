using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Reflection;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Threading;

namespace GroundStation
{
    public partial class GroundStationMainForm : Form
    {
        public static ClassSerial serial = new ClassSerial();
        Server tcpserv;

        delegate void FillToolStrip(string value);

        #region load and exit main form
        public GroundStationMainForm()
        {
            InitializeComponent();
            tcpserv = new Server();
            GroundStationMainForm.serial.AddCallback(IncommingMessage);

            /*ProcessStartInfo notepadStartInfo = new ProcessStartInfo("Using3DModels.exe");
            Process notepad = new Process();
            notepad.StartInfo = notepadStartInfo;
            notepad.Start();
            Thread.Sleep(200); */ 
          
            /*ProcessStartInfo boussoleStartInfo = new ProcessStartInfo("boussole.exe");
            Process boussole = new Process();
            boussole.StartInfo = boussoleStartInfo;
            boussole.Start();
            Thread.Sleep(200);*/
        }
        private void GroundStationMainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            serial.Deconnect();
            tcpserv.CloseServer();

            try
            {
                foreach (Process proc in Process.GetProcessesByName("Using3DModels"))
                {
                    proc.Kill();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            } 
            
            try
            {
                foreach (Process proc in Process.GetProcessesByName("boussole"))
                {
                    proc.Kill();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        private void GroundStationMainForm_Load(object sender, EventArgs e)
        {
            if (ConnexiontoolStripMenuItem.Text == "Connexion")
            {
                if ((serial.Connect("COM40") == true) || (serial.Connect("COM14") == true)|| (serial.Connect("COM5") == true) || (serial.Connect("COM7") == true) || (serial.Connect("COM22") == true) || (serial.Connect("COM1") == true))
                {
                    ConnexiontoolStripMenuItem.Text = "Deconnexion";
                    StatetoolStripStatusLabel.Text = "Etat : Connecte";
                }
                else
                {
                    StatetoolStripStatusLabel.Text = "Etat : Connection impossible";
                }
            }
            else
            {
                try
                {
                    serial.Deconnect();
                }
                catch
                {
                }
                ConnexiontoolStripMenuItem.Text = "Connexion";
                StatetoolStripStatusLabel.Text = "Etat : Deconnecte";
            }


            FormGraph childForm = new FormGraph();
            childForm.MdiParent = this;
            childForm.Show();
            FormCommand childForm2 = new FormCommand();
            childForm2.MdiParent = this;
            childForm2.Show();
            LayoutMdi(MdiLayout.TileVertical);
        }
        public void IncommingMessage(string message)
        {
            try
            {
                Invoke((FillToolStrip)AddItemToolStrip, message);
            }
            catch { }
        }
        void AddItemToolStrip(string value)
        {
            try
            {
                if (!value.Contains("OK") && !value.Contains("PID"))
                {
                    toolStripStatusButtonMessage.Text = "Messages : " + value;
                    toolStripStatusButtonMessage.DropDownItems.Add(System.DateTime.Now.Minute + ":" + System.DateTime.Now.Second + "," + System.DateTime.Now.Millisecond + "\t" + value);
                    toolStripStatusButtonMessage.ToolTipText = "count ( " + Convert.ToString(toolStripStatusButtonMessage.DropDownItems.Count - 1) + " )";
                    if (toolStripStatusButtonMessage.DropDownItems.Count > 50)
                    {
                        toolStripStatusButtonMessage.DropDownItems.RemoveAt(0);
                    } 
                    
                    string[] param = value.Replace("\0", "").Replace(" ", "").Split(',');

                    //string Z = System.Convert.ToString(-1 * System.Convert.ToInt16(param[2]));
                    //tcpserv.SendMessage("x=0/y=0/z=0/rotx=" + System.Convert.ToInt16(param[0]) + "/roty=" + System.Convert.ToInt16(param[1]) + "/rotz=" + Z + "/vit=" + System.Convert.ToInt16(param[11]) + "##");

                    
                }
            }
            catch
            {
            }
        }


       
        #endregion



        


        private void ShowNewForm(object sender, EventArgs e)
        {
            FormGraph childForm = new FormGraph();
            childForm.MdiParent = this;
            childForm.Show();
            FormCommand childForm2 = new FormCommand();
            childForm2.MdiParent = this;
            childForm2.Show();
        }

        private void ConnexiontoolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (ConnexiontoolStripMenuItem.Text == "Connexion")
            {
                if ((serial.Connect("COM14") == true) || (serial.Connect("COM3") == true))
                {
                    ConnexiontoolStripMenuItem.Text = "Deconnexion";
                    StatetoolStripStatusLabel.Text = "Etat : Connecte";
                }
                else
                {
                    StatetoolStripStatusLabel.Text = "Etat : Connection impossible";
                }
            }
            else
            {
                try
                {
                    serial.Deconnect();
                }
                catch
                {
                }
                ConnexiontoolStripMenuItem.Text = "Connexion";
                StatetoolStripStatusLabel.Text = "Etat : Deconnecte";
            }
        }
        private void OpenFile(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.Personal);
            openFileDialog.Filter = "Fichiers texte (*.txt)|*.txt|Tous les fichiers (*.*)|*.*";
            if (openFileDialog.ShowDialog(this) == DialogResult.OK)
            {
                string FileName = openFileDialog.FileName;
            }
        }

        private void SaveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.Personal);
            saveFileDialog.Filter = "Fichiers texte (*.txt)|*.txt|Tous les fichiers (*.*)|*.*";
            if (saveFileDialog.ShowDialog(this) == DialogResult.OK)
            {
                string FileName = saveFileDialog.FileName;
            }
        }

        private void ExitToolsStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void CutToolStripMenuItem_Click(object sender, EventArgs e)
        {
        }

        private void CopyToolStripMenuItem_Click(object sender, EventArgs e)
        {
        }

        private void PasteToolStripMenuItem_Click(object sender, EventArgs e)
        {
        }

        private void ToolBarToolStripMenuItem_Click(object sender, EventArgs e)
        {
            toolStrip.Visible = toolBarToolStripMenuItem.Checked;
        }

        private void StatusBarToolStripMenuItem_Click(object sender, EventArgs e)
        {
            statusStrip.Visible = statusBarToolStripMenuItem.Checked;
        }

        private void CascadeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LayoutMdi(MdiLayout.Cascade);
        }

        private void TileVerticalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LayoutMdi(MdiLayout.TileVertical);
        }

        private void TileHorizontalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LayoutMdi(MdiLayout.TileHorizontal);
        }

        private void ArrangeIconsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LayoutMdi(MdiLayout.ArrangeIcons);
        }

        private void CloseAllToolStripMenuItem_Click(object sender, EventArgs e)
        {
            foreach (Form childForm in MdiChildren)
            {
                childForm.Close();
            }
        }



        

        

    
    }
}
