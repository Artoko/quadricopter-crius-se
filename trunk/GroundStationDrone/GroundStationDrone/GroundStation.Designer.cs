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
            this.toolStripStatusLabelAltitude = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripStatusLabelTemperature = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripStatusLabelPresssion = new System.Windows.Forms.ToolStripStatusLabel();
            this.menuStripParams = new System.Windows.Forms.MenuStrip();
            this.generalToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.getVersionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.resetToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.recalibrationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItemMotors = new System.Windows.Forms.ToolStripMenuItem();
            this.getSpeedToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.showIndicatorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItemAngles = new System.Windows.Forms.ToolStripMenuItem();
            this.getAnglesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItemSensors = new System.Windows.Forms.ToolStripMenuItem();
            this.getAccelerometerToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.getGyroscopeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.getMagnetometerToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.getBarometerToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItemPID = new System.Windows.Forms.ToolStripMenuItem();
            this.getPIDToolStripMenuItem = new System.Windows.Forms.ToolStripComboBox();
            this.getPIDsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.setPIDsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.trackBarSpeed = new System.Windows.Forms.TrackBar();
            this.panel1 = new System.Windows.Forms.Panel();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.turn_indicator = new GroundStationDrone.TurnCoordinatorInstrumentControl();
            this.vario_indicator = new GroundStationDrone.VerticalSpeedIndicatorInstrumentControl();
            this.altimeter_indicator = new GroundStationDrone.AltimeterInstrumentControl();
            this.heading_indicator = new GroundStationDrone.HeadingIndicatorInstrumentControl();
            this.horizon_indicator = new GroundStationDrone.AttitudeIndicatorInstrumentControl();
            this.air_speed_indicator = new GroundStationDrone.AirSpeedIndicatorInstrumentControl();
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
            this.toolStripSeparator3,
            this.toolStripStatusLabelAltitude,
            this.toolStripSeparator4,
            this.toolStripStatusLabelTemperature,
            this.toolStripSeparator5,
            this.toolStripStatusLabelPresssion});
            this.statusStripState.Location = new System.Drawing.Point(0, 359);
            this.statusStripState.Name = "statusStripState";
            this.statusStripState.Size = new System.Drawing.Size(895, 23);
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
            // toolStripStatusLabelAltitude
            // 
            this.toolStripStatusLabelAltitude.Name = "toolStripStatusLabelAltitude";
            this.toolStripStatusLabelAltitude.Size = new System.Drawing.Size(69, 18);
            this.toolStripStatusLabelAltitude.Text = "Altitude = 0";
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            this.toolStripSeparator4.Size = new System.Drawing.Size(6, 23);
            // 
            // toolStripStatusLabelTemperature
            // 
            this.toolStripStatusLabelTemperature.Name = "toolStripStatusLabelTemperature";
            this.toolStripStatusLabelTemperature.Size = new System.Drawing.Size(106, 18);
            this.toolStripStatusLabelTemperature.Text = "Temperature : 0 °C";
            // 
            // toolStripSeparator5
            // 
            this.toolStripSeparator5.Name = "toolStripSeparator5";
            this.toolStripSeparator5.Size = new System.Drawing.Size(6, 23);
            // 
            // toolStripStatusLabelPresssion
            // 
            this.toolStripStatusLabelPresssion.Name = "toolStripStatusLabelPresssion";
            this.toolStripStatusLabelPresssion.Size = new System.Drawing.Size(82, 18);
            this.toolStripStatusLabelPresssion.Text = "Pression : 0 Pa";
            // 
            // menuStripParams
            // 
            this.menuStripParams.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.generalToolStripMenuItem,
            this.toolStripMenuItemMotors,
            this.toolStripMenuItemAngles,
            this.toolStripMenuItemSensors,
            this.toolStripMenuItemPID});
            this.menuStripParams.Location = new System.Drawing.Point(0, 0);
            this.menuStripParams.Name = "menuStripParams";
            this.menuStripParams.Size = new System.Drawing.Size(895, 24);
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
            this.getSpeedToolStripMenuItem.Size = new System.Drawing.Size(153, 22);
            this.getSpeedToolStripMenuItem.Text = "Get Speed";
            this.getSpeedToolStripMenuItem.Click += new System.EventHandler(this.getSpeedToolStripMenuItem_Click);
            // 
            // showIndicatorToolStripMenuItem
            // 
            this.showIndicatorToolStripMenuItem.Name = "showIndicatorToolStripMenuItem";
            this.showIndicatorToolStripMenuItem.Size = new System.Drawing.Size(153, 22);
            this.showIndicatorToolStripMenuItem.Text = "Show Indicator";
            this.showIndicatorToolStripMenuItem.Click += new System.EventHandler(this.showIndicatorToolStripMenuItem_Click);
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
            // toolStripMenuItemSensors
            // 
            this.toolStripMenuItemSensors.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.getAccelerometerToolStripMenuItem,
            this.getGyroscopeToolStripMenuItem,
            this.getMagnetometerToolStripMenuItem,
            this.getBarometerToolStripMenuItem});
            this.toolStripMenuItemSensors.Name = "toolStripMenuItemSensors";
            this.toolStripMenuItemSensors.Size = new System.Drawing.Size(59, 20);
            this.toolStripMenuItemSensors.Text = "Sensors";
            // 
            // getAccelerometerToolStripMenuItem
            // 
            this.getAccelerometerToolStripMenuItem.Name = "getAccelerometerToolStripMenuItem";
            this.getAccelerometerToolStripMenuItem.Size = new System.Drawing.Size(174, 22);
            this.getAccelerometerToolStripMenuItem.Text = "Get Accelerometer";
            this.getAccelerometerToolStripMenuItem.Click += new System.EventHandler(this.getAccelerometerToolStripMenuItem_Click);
            // 
            // getGyroscopeToolStripMenuItem
            // 
            this.getGyroscopeToolStripMenuItem.Name = "getGyroscopeToolStripMenuItem";
            this.getGyroscopeToolStripMenuItem.Size = new System.Drawing.Size(174, 22);
            this.getGyroscopeToolStripMenuItem.Text = "Get Gyroscope";
            this.getGyroscopeToolStripMenuItem.Click += new System.EventHandler(this.getGyroscopeToolStripMenuItem_Click);
            // 
            // getMagnetometerToolStripMenuItem
            // 
            this.getMagnetometerToolStripMenuItem.Name = "getMagnetometerToolStripMenuItem";
            this.getMagnetometerToolStripMenuItem.Size = new System.Drawing.Size(174, 22);
            this.getMagnetometerToolStripMenuItem.Text = "Get Magnetometer";
            this.getMagnetometerToolStripMenuItem.Click += new System.EventHandler(this.getMagnetometerToolStripMenuItem_Click);
            // 
            // getBarometerToolStripMenuItem
            // 
            this.getBarometerToolStripMenuItem.Name = "getBarometerToolStripMenuItem";
            this.getBarometerToolStripMenuItem.Size = new System.Drawing.Size(174, 22);
            this.getBarometerToolStripMenuItem.Text = "Get Barometer";
            this.getBarometerToolStripMenuItem.Click += new System.EventHandler(this.getAltitudeToolStripMenuItem_Click);
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
            this.trackBarSpeed.Location = new System.Drawing.Point(811, 135);
            this.trackBarSpeed.Maximum = 800;
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
            this.panel1.Location = new System.Drawing.Point(707, 252);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(176, 104);
            this.panel1.TabIndex = 6;
            this.panel1.Paint += new System.Windows.Forms.PaintEventHandler(this.panel1_Paint);
            // 
            // timer1
            // 
            this.timer1.Interval = 10;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // turn_indicator
            // 
            this.turn_indicator.Location = new System.Drawing.Point(324, 183);
            this.turn_indicator.Name = "turn_indicator";
            this.turn_indicator.Size = new System.Drawing.Size(150, 150);
            this.turn_indicator.TabIndex = 12;
            this.turn_indicator.Text = "turnCoordinatorInstrumentControl1";
            // 
            // vario_indicator
            // 
            this.vario_indicator.Location = new System.Drawing.Point(168, 183);
            this.vario_indicator.Name = "vario_indicator";
            this.vario_indicator.Size = new System.Drawing.Size(150, 150);
            this.vario_indicator.TabIndex = 11;
            this.vario_indicator.Text = "verticalSpeedIndicatorInstrumentControl1";
            // 
            // altimeter_indicator
            // 
            this.altimeter_indicator.Location = new System.Drawing.Point(480, 105);
            this.altimeter_indicator.Name = "altimeter_indicator";
            this.altimeter_indicator.Size = new System.Drawing.Size(150, 150);
            this.altimeter_indicator.TabIndex = 10;
            this.altimeter_indicator.Text = "altimeterInstrumentControl1";
            // 
            // heading_indicator
            // 
            this.heading_indicator.Location = new System.Drawing.Point(324, 27);
            this.heading_indicator.Name = "heading_indicator";
            this.heading_indicator.Size = new System.Drawing.Size(150, 150);
            this.heading_indicator.TabIndex = 9;
            this.heading_indicator.Text = "headingIndicatorInstrumentControl1";
            // 
            // horizon_indicator
            // 
            this.horizon_indicator.Location = new System.Drawing.Point(168, 27);
            this.horizon_indicator.Name = "horizon_indicator";
            this.horizon_indicator.Size = new System.Drawing.Size(150, 150);
            this.horizon_indicator.TabIndex = 8;
            this.horizon_indicator.Text = "attitudeIndicatorInstrumentControl1";
            // 
            // air_speed_indicator
            // 
            this.air_speed_indicator.Location = new System.Drawing.Point(12, 105);
            this.air_speed_indicator.Name = "air_speed_indicator";
            this.air_speed_indicator.Size = new System.Drawing.Size(150, 150);
            this.air_speed_indicator.TabIndex = 7;
            this.air_speed_indicator.Text = "airSpeedIndicatorInstrumentControl1";
            // 
            // GroundStation
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(895, 382);
            this.Controls.Add(this.turn_indicator);
            this.Controls.Add(this.vario_indicator);
            this.Controls.Add(this.altimeter_indicator);
            this.Controls.Add(this.heading_indicator);
            this.Controls.Add(this.horizon_indicator);
            this.Controls.Add(this.air_speed_indicator);
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
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
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
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItemSensors;
        private System.Windows.Forms.ToolStripMenuItem getBarometerToolStripMenuItem;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabelAltitude;
        private System.Windows.Forms.ToolStripMenuItem getAccelerometerToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem getGyroscopeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem getMagnetometerToolStripMenuItem;
        private AirSpeedIndicatorInstrumentControl air_speed_indicator;
        private AttitudeIndicatorInstrumentControl horizon_indicator;
        private HeadingIndicatorInstrumentControl heading_indicator;
        private AltimeterInstrumentControl altimeter_indicator;
        private VerticalSpeedIndicatorInstrumentControl vario_indicator;
        private TurnCoordinatorInstrumentControl turn_indicator;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabelTemperature;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabelPresssion;

    }
}

