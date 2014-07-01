namespace GroundStationDrone
{
    partial class GroundStation
    {
        /// <summary>
        /// Variable nécessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Nettoyage des ressources utilisées.
        /// </summary>
        /// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code généré par le Concepteur Windows Form

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.statusStripState = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabelVersion = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripStatusLabelSpeed = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripStatusLabelAngles = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.menuStripParams = new System.Windows.Forms.MenuStrip();
            this.generalToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.getVersionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.resetToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.recalibrationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItemMotors = new System.Windows.Forms.ToolStripMenuItem();
            this.getSpeedToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItemAngles = new System.Windows.Forms.ToolStripMenuItem();
            this.getAnglesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItemPID = new System.Windows.Forms.ToolStripMenuItem();
            this.getPIDToolStripMenuItem = new System.Windows.Forms.ToolStripComboBox();
            this.getPIDsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.setPIDsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.trackBarSpeed = new System.Windows.Forms.TrackBar();
            this.panel1 = new System.Windows.Forms.Panel();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.showIndicatorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStripState.SuspendLayout();
            this.menuStripParams.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarSpeed)).BeginInit();
            this.SuspendLayout();
            // 
            // statusStripState
            // 
            this.statusStripState.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabelVersion,
            this.toolStripSeparator1,
            this.toolStripStatusLabelSpeed,
            this.toolStripSeparator2,
            this.toolStripStatusLabelAngles,
            this.toolStripSeparator3});
            this.statusStripState.Location = new System.Drawing.Point(0, 359);
            this.statusStripState.Name = "statusStripState";
            this.statusStripState.Size = new System.Drawing.Size(756, 23);
            this.statusStripState.TabIndex = 0;
            this.statusStripState.Text = "statusStrip1";
            // 
            // toolStripStatusLabelVersion
            // 
            this.toolStripStatusLabelVersion.Name = "toolStripStatusLabelVersion";
            this.toolStripStatusLabelVersion.Size = new System.Drawing.Size(70, 18);
            this.toolStripStatusLabelVersion.Text = "Version : 0.0";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 23);
            // 
            // toolStripStatusLabelSpeed
            // 
            this.toolStripStatusLabelSpeed.Name = "toolStripStatusLabelSpeed";
            this.toolStripStatusLabelSpeed.Size = new System.Drawing.Size(59, 18);
            this.toolStripStatusLabelSpeed.Text = "Speed = 0";
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 23);
            // 
            // toolStripStatusLabelAngles
            // 
            this.toolStripStatusLabelAngles.Name = "toolStripStatusLabelAngles";
            this.toolStripStatusLabelAngles.Size = new System.Drawing.Size(91, 18);
            this.toolStripStatusLabelAngles.Text = "Angles : 0 , 0 , 0 ";
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(6, 23);
            // 
            // menuStripParams
            // 
            this.menuStripParams.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.generalToolStripMenuItem,
            this.toolStripMenuItemMotors,
            this.toolStripMenuItemAngles,
            this.toolStripMenuItemPID});
            this.menuStripParams.Location = new System.Drawing.Point(0, 0);
            this.menuStripParams.Name = "menuStripParams";
            this.menuStripParams.Size = new System.Drawing.Size(756, 24);
            this.menuStripParams.TabIndex = 4;
            this.menuStripParams.Text = "menuStrip2";
            // 
            // generalToolStripMenuItem
            // 
            this.generalToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.getVersionToolStripMenuItem,
            this.resetToolStripMenuItem,
            this.recalibrationToolStripMenuItem});
            this.generalToolStripMenuItem.Name = "generalToolStripMenuItem";
            this.generalToolStripMenuItem.Size = new System.Drawing.Size(59, 20);
            this.generalToolStripMenuItem.Text = "General";
            // 
            // getVersionToolStripMenuItem
            // 
            this.getVersionToolStripMenuItem.Name = "getVersionToolStripMenuItem";
            this.getVersionToolStripMenuItem.Size = new System.Drawing.Size(157, 22);
            this.getVersionToolStripMenuItem.Text = "Get Version";
            this.getVersionToolStripMenuItem.Click += new System.EventHandler(this.getVersionToolStripMenuItem_Click);
            // 
            // resetToolStripMenuItem
            // 
            this.resetToolStripMenuItem.Name = "resetToolStripMenuItem";
            this.resetToolStripMenuItem.Size = new System.Drawing.Size(157, 22);
            this.resetToolStripMenuItem.Text = "Reset";
            this.resetToolStripMenuItem.Click += new System.EventHandler(this.resetToolStripMenuItem_Click);
            // 
            // recalibrationToolStripMenuItem
            // 
            this.recalibrationToolStripMenuItem.Name = "recalibrationToolStripMenuItem";
            this.recalibrationToolStripMenuItem.Size = new System.Drawing.Size(157, 22);
            this.recalibrationToolStripMenuItem.Text = "New calibration";
            this.recalibrationToolStripMenuItem.Click += new System.EventHandler(this.recalibrationToolStripMenuItem_Click);
            // 
            // toolStripMenuItemMotors
            // 
            this.toolStripMenuItemMotors.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.getSpeedToolStripMenuItem,
            this.showIndicatorToolStripMenuItem});
            this.toolStripMenuItemMotors.Name = "toolStripMenuItemMotors";
            this.toolStripMenuItemMotors.Size = new System.Drawing.Size(57, 20);
            this.toolStripMenuItemMotors.Text = "Motors";
            // 
            // getSpeedToolStripMenuItem
            // 
            this.getSpeedToolStripMenuItem.Name = "getSpeedToolStripMenuItem";
            this.getSpeedToolStripMenuItem.Size = new System.Drawing.Size(127, 22);
            this.getSpeedToolStripMenuItem.Text = "Get Speed";
            this.getSpeedToolStripMenuItem.Click += new System.EventHandler(this.getSpeedToolStripMenuItem_Click);
            // 
            // toolStripMenuItemAngles
            // 
            this.toolStripMenuItemAngles.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.getAnglesToolStripMenuItem});
            this.toolStripMenuItemAngles.Name = "toolStripMenuItemAngles";
            this.toolStripMenuItemAngles.Size = new System.Drawing.Size(55, 20);
            this.toolStripMenuItemAngles.Text = "Angles";
            // 
            // getAnglesToolStripMenuItem
            // 
            this.getAnglesToolStripMenuItem.Name = "getAnglesToolStripMenuItem";
            this.getAnglesToolStripMenuItem.Size = new System.Drawing.Size(131, 22);
            this.getAnglesToolStripMenuItem.Text = "Get Angles";
            this.getAnglesToolStripMenuItem.Click += new System.EventHandler(this.getAnglesToolStripMenuItem_Click);
            // 
            // toolStripMenuItemPID
            // 
            this.toolStripMenuItemPID.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.getPIDToolStripMenuItem,
            this.getPIDsToolStripMenuItem,
            this.setPIDsToolStripMenuItem});
            this.toolStripMenuItemPID.Name = "toolStripMenuItemPID";
            this.toolStripMenuItemPID.Size = new System.Drawing.Size(37, 20);
            this.toolStripMenuItemPID.Text = "PID";
            // 
            // getPIDToolStripMenuItem
            // 
            this.getPIDToolStripMenuItem.AutoCompleteCustomSource.AddRange(new string[] {
            "Get PID roulis",
            "Get PID tangage",
            "Get PID lacet",
            "Get PID altitude"});
            this.getPIDToolStripMenuItem.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.getPIDToolStripMenuItem.Items.AddRange(new object[] {
            "Get PID roulis",
            "Get PID tangage",
            "Get PID lacet",
            "Get PID altitude"});
            this.getPIDToolStripMenuItem.Name = "getPIDToolStripMenuItem";
            this.getPIDToolStripMenuItem.Size = new System.Drawing.Size(152, 23);
            // 
            // getPIDsToolStripMenuItem
            // 
            this.getPIDsToolStripMenuItem.Name = "getPIDsToolStripMenuItem";
            this.getPIDsToolStripMenuItem.Size = new System.Drawing.Size(212, 22);
            this.getPIDsToolStripMenuItem.Text = "Get PIDs";
            this.getPIDsToolStripMenuItem.Click += new System.EventHandler(this.getPIDsToolStripMenuItem_Click);
            // 
            // setPIDsToolStripMenuItem
            // 
            this.setPIDsToolStripMenuItem.Name = "setPIDsToolStripMenuItem";
            this.setPIDsToolStripMenuItem.Size = new System.Drawing.Size(212, 22);
            this.setPIDsToolStripMenuItem.Text = "Set PIDs";
            // 
            // trackBarSpeed
            // 
            this.trackBarSpeed.Location = new System.Drawing.Point(395, 27);
            this.trackBarSpeed.Maximum = 1000;
            this.trackBarSpeed.Name = "trackBarSpeed";
            this.trackBarSpeed.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.trackBarSpeed.Size = new System.Drawing.Size(45, 104);
            this.trackBarSpeed.SmallChange = 5;
            this.trackBarSpeed.TabIndex = 5;
            this.trackBarSpeed.TickFrequency = 100;
            this.trackBarSpeed.TickStyle = System.Windows.Forms.TickStyle.Both;
            this.trackBarSpeed.Scroll += new System.EventHandler(this.trackBarSpeed_Scroll);
            // 
            // panel1
            // 
            this.panel1.Location = new System.Drawing.Point(446, 27);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(298, 104);
            this.panel1.TabIndex = 6;
            this.panel1.Paint += new System.Windows.Forms.PaintEventHandler(this.panel1_Paint);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 10;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // showIndicatorToolStripMenuItem
            // 
            this.showIndicatorToolStripMenuItem.Name = "showIndicatorToolStripMenuItem";
            this.showIndicatorToolStripMenuItem.Size = new System.Drawing.Size(153, 22);
            this.showIndicatorToolStripMenuItem.Text = "Show Indicator";
            this.showIndicatorToolStripMenuItem.Click += new System.EventHandler(this.showIndicatorToolStripMenuItem_Click);
            // 
            // GroundStation
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(756, 382);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.trackBarSpeed);
            this.Controls.Add(this.statusStripState);
            this.Controls.Add(this.menuStripParams);
            this.Name = "GroundStation";
            this.Text = "GroundStationDrone";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.GroundStation_FormClosing);
            this.Load += new System.EventHandler(this.GroundStation_Load);
            this.statusStripState.ResumeLayout(false);
            this.statusStripState.PerformLayout();
            this.menuStripParams.ResumeLayout(false);
            this.menuStripParams.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarSpeed)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.StatusStrip statusStripState;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabelVersion;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.MenuStrip menuStripParams;
        private System.Windows.Forms.ToolStripMenuItem generalToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem getVersionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem resetToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem recalibrationToolStripMenuItem;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabelSpeed;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItemMotors;
        private System.Windows.Forms.ToolStripMenuItem getSpeedToolStripMenuItem;
        private System.Windows.Forms.TrackBar trackBarSpeed;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItemAngles;
        private System.Windows.Forms.ToolStripMenuItem getAnglesToolStripMenuItem;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabelAngles;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItemPID;
        private System.Windows.Forms.ToolStripComboBox getPIDToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem setPIDsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem getPIDsToolStripMenuItem;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.ToolStripMenuItem showIndicatorToolStripMenuItem;

    }
}

