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
        //Server tcpserv;

        delegate void FillToolStrip(string value);

        FormGraph graph_form = new FormGraph();
        FormCommand command_form = new FormCommand();

        Thread Thread_ListenerModem;
        bool thread_modem = false;
        static bool wait_message = false;
        
         #region load and exit main form
        public GroundStationMainForm()
        {
            InitializeComponent();
            //tcpserv = new Server();

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
            
            
            /*thread_modem = true;
            Thread_ListenerModem = new Thread(new Threa dStart(ListenerModem));
            Thread_ListenerModem.Start();*/


        }

        private void ListenerModem()
        {
            while (thread_modem)
            {
                serial.SendMessage("*6+1##");
                Thread.Sleep(10);
            }
        }

        private void GroundStationMainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            thread_modem = false;
            serial.Deconnect();
            //tcpserv.CloseServer();

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
                if ((serial.Connect("COM40", IncommingMessage) == true) ||
                    (serial.Connect("COM14", IncommingMessage) == true) ||
                    (serial.Connect("COM5", IncommingMessage) == true) ||
                    (serial.Connect("COM7", IncommingMessage) == true) ||
                    (serial.Connect("COM22", IncommingMessage) == true) ||
                    (serial.Connect("COM1", IncommingMessage) == true))
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


            graph_form.MdiParent = this;
            graph_form.Show();
            command_form.MdiParent = this;
            command_form.Show();


            serial.SendMessage("*6+2##");
            LayoutMdi(MdiLayout.TileVertical);
        }
        public void IncommingMessage(byte[] message)
        {
            //try
            {
                //Invoke((FillToolStrip)AddItemToolStrip, message);
                if (message.Length == 32)
                {
                    graph_form.IncommingMessage(message);
                }
                else
                {
                    command_form.IncommingMessage(message);
                    wait_message = false;
                }
            }
            //catch { }

            if (wait_message == false)
            {
                SendMessage("*6+2##");
            }
            

        }

        public static void SendMessage(string message)
        {
            if (message != "*6+2##")
            {
                wait_message = true;
            }
            serial.SendMessage(message);
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
