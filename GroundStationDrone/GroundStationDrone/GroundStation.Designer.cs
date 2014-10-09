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
            this.getPIDsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.setPIDsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItemView = new System.Windows.Forms.ToolStripMenuItem();
            this.cockpitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.graphToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.trackBarSpeed = new System.Windows.Forms.TrackBar();
            this.panel1 = new System.Windows.Forms.Panel();
            this.labelAttitude = new System.Windows.Forms.Label();
            this.labelAcc = new System.Windows.Forms.Label();
            this.labelGyro = new System.Windows.Forms.Label();
            this.labelMag = new System.Windows.Forms.Label();
            this.labelMot = new System.Windows.Forms.Label();
            this.numericUpDownProulis = new System.Windows.Forms.NumericUpDown();
            this.labelP = new System.Windows.Forms.Label();
            this.labelI = new System.Windows.Forms.Label();
            this.labelD = new System.Windows.Forms.Label();
            this.numericUpDownIroulis = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownDroulis = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownDtangage = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownItangage = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownPtangage = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownDlacet = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownIlacet = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownPlacet = new System.Windows.Forms.NumericUpDown();
            this.labelRoulis = new System.Windows.Forms.Label();
            this.labelTangage = new System.Windows.Forms.Label();
            this.labelLacet = new System.Windows.Forms.Label();
            this.turn_indicator = new GroundStationDrone.TurnCoordinatorInstrumentControl();
            this.vario_indicator = new GroundStationDrone.VerticalSpeedIndicatorInstrumentControl();
            this.altimeter_indicator = new GroundStationDrone.AltimeterInstrumentControl();
            this.heading_indicator = new GroundStationDrone.HeadingIndicatorInstrumentControl();
            this.horizon_indicator = new GroundStationDrone.AttitudeIndicatorInstrumentControl();
            this.air_speed_indicator = new GroundStationDrone.AirSpeedIndicatorInstrumentControl();
            this.statusStripState.SuspendLayout();
            this.menuStripParams.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarSpeed)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownProulis)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownIroulis)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownDroulis)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownDtangage)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownItangage)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPtangage)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownDlacet)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownIlacet)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPlacet)).BeginInit();
            this.SuspendLayout();
            // 
            // statusStripState
            // 
            this.statusStripState.BackColor = System.Drawing.SystemColors.GrayText;
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
            this.statusStripState.Location = new System.Drawing.Point(0, 463);
            this.statusStripState.Name = "statusStripState";
            this.statusStripState.Size = new System.Drawing.Size(967, 23);
            this.statusStripState.SizingGrip = false;
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
            this.toolStripMenuItemPID,
            this.toolStripMenuItemView});
            this.menuStripParams.Location = new System.Drawing.Point(0, 0);
            this.menuStripParams.Name = "menuStripParams";
            this.menuStripParams.Size = new System.Drawing.Size(967, 24);
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
            this.getPIDsToolStripMenuItem,
            this.setPIDsToolStripMenuItem});
            this.toolStripMenuItemPID.Name = "toolStripMenuItemPID";
            this.toolStripMenuItemPID.Size = new System.Drawing.Size(37, 20);
            this.toolStripMenuItemPID.Text = "PID";
            // 
            // getPIDsToolStripMenuItem
            // 
            this.getPIDsToolStripMenuItem.Name = "getPIDsToolStripMenuItem";
            this.getPIDsToolStripMenuItem.Size = new System.Drawing.Size(118, 22);
            this.getPIDsToolStripMenuItem.Text = "Get PIDs";
            this.getPIDsToolStripMenuItem.Click += new System.EventHandler(this.getPIDsToolStripMenuItem_Click);
            // 
            // setPIDsToolStripMenuItem
            // 
            this.setPIDsToolStripMenuItem.Name = "setPIDsToolStripMenuItem";
            this.setPIDsToolStripMenuItem.Size = new System.Drawing.Size(118, 22);
            this.setPIDsToolStripMenuItem.Text = "Set PIDs";
            this.setPIDsToolStripMenuItem.Click += new System.EventHandler(this.setPIDsToolStripMenuItem_Click);
            // 
            // toolStripMenuItemView
            // 
            this.toolStripMenuItemView.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.cockpitToolStripMenuItem,
            this.graphToolStripMenuItem});
            this.toolStripMenuItemView.Name = "toolStripMenuItemView";
            this.toolStripMenuItemView.Size = new System.Drawing.Size(44, 20);
            this.toolStripMenuItemView.Text = "View";
            // 
            // cockpitToolStripMenuItem
            // 
            this.cockpitToolStripMenuItem.Name = "cockpitToolStripMenuItem";
            this.cockpitToolStripMenuItem.Size = new System.Drawing.Size(115, 22);
            this.cockpitToolStripMenuItem.Text = "Cockpit";
            this.cockpitToolStripMenuItem.Click += new System.EventHandler(this.cockpitToolStripMenuItem_Click);
            // 
            // graphToolStripMenuItem
            // 
            this.graphToolStripMenuItem.Name = "graphToolStripMenuItem";
            this.graphToolStripMenuItem.Size = new System.Drawing.Size(115, 22);
            this.graphToolStripMenuItem.Text = "Graph";
            // 
            // trackBarSpeed
            // 
            this.trackBarSpeed.Location = new System.Drawing.Point(33, 106);
            this.trackBarSpeed.Maximum = 800;
            this.trackBarSpeed.Name = "trackBarSpeed";
            this.trackBarSpeed.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.trackBarSpeed.Size = new System.Drawing.Size(45, 150);
            this.trackBarSpeed.SmallChange = 5;
            this.trackBarSpeed.TabIndex = 5;
            this.trackBarSpeed.TickFrequency = 100;
            this.trackBarSpeed.TickStyle = System.Windows.Forms.TickStyle.Both;
            this.trackBarSpeed.Scroll += new System.EventHandler(this.trackBarSpeed_Scroll);
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.BackColor = System.Drawing.SystemColors.ControlDark;
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Location = new System.Drawing.Point(84, 340);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(860, 104);
            this.panel1.TabIndex = 6;
            this.panel1.Paint += new System.Windows.Forms.PaintEventHandler(this.panel1_Paint);
            // 
            // labelAttitude
            // 
            this.labelAttitude.AutoSize = true;
            this.labelAttitude.Cursor = System.Windows.Forms.Cursors.Hand;
            this.labelAttitude.Location = new System.Drawing.Point(12, 340);
            this.labelAttitude.Name = "labelAttitude";
            this.labelAttitude.Size = new System.Drawing.Size(43, 13);
            this.labelAttitude.TabIndex = 13;
            this.labelAttitude.Text = "Attitude";
            this.labelAttitude.Click += new System.EventHandler(this.labelAttitude_Click);
            // 
            // labelAcc
            // 
            this.labelAcc.AutoSize = true;
            this.labelAcc.Cursor = System.Windows.Forms.Cursors.Hand;
            this.labelAcc.Location = new System.Drawing.Point(12, 362);
            this.labelAcc.Name = "labelAcc";
            this.labelAcc.Size = new System.Drawing.Size(26, 13);
            this.labelAcc.TabIndex = 14;
            this.labelAcc.Text = "Acc";
            this.labelAcc.Click += new System.EventHandler(this.labelAcc_Click);
            // 
            // labelGyro
            // 
            this.labelGyro.AutoSize = true;
            this.labelGyro.Cursor = System.Windows.Forms.Cursors.Hand;
            this.labelGyro.Location = new System.Drawing.Point(12, 384);
            this.labelGyro.Name = "labelGyro";
            this.labelGyro.Size = new System.Drawing.Size(29, 13);
            this.labelGyro.TabIndex = 15;
            this.labelGyro.Text = "Gyro";
            this.labelGyro.Click += new System.EventHandler(this.labelGyro_Click);
            // 
            // labelMag
            // 
            this.labelMag.AutoSize = true;
            this.labelMag.Cursor = System.Windows.Forms.Cursors.Hand;
            this.labelMag.Location = new System.Drawing.Point(12, 406);
            this.labelMag.Name = "labelMag";
            this.labelMag.Size = new System.Drawing.Size(28, 13);
            this.labelMag.TabIndex = 16;
            this.labelMag.Text = "Mag";
            this.labelMag.Click += new System.EventHandler(this.labelMag_Click);
            // 
            // labelMot
            // 
            this.labelMot.AutoSize = true;
            this.labelMot.Cursor = System.Windows.Forms.Cursors.Hand;
            this.labelMot.Location = new System.Drawing.Point(12, 428);
            this.labelMot.Name = "labelMot";
            this.labelMot.Size = new System.Drawing.Size(45, 13);
            this.labelMot.TabIndex = 17;
            this.labelMot.Text = "Moteurs";
            this.labelMot.Click += new System.EventHandler(this.labelMot_Click);
            // 
            // numericUpDownProulis
            // 
            this.numericUpDownProulis.Location = new System.Drawing.Point(760, 106);
            this.numericUpDownProulis.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numericUpDownProulis.Name = "numericUpDownProulis";
            this.numericUpDownProulis.Size = new System.Drawing.Size(57, 20);
            this.numericUpDownProulis.TabIndex = 18;
            this.numericUpDownProulis.ValueChanged += new System.EventHandler(this.numericUpDownRoulis_ValueChanged);
            // 
            // labelP
            // 
            this.labelP.AutoSize = true;
            this.labelP.Location = new System.Drawing.Point(781, 81);
            this.labelP.Name = "labelP";
            this.labelP.Size = new System.Drawing.Size(14, 13);
            this.labelP.TabIndex = 19;
            this.labelP.Text = "P";
            // 
            // labelI
            // 
            this.labelI.AutoSize = true;
            this.labelI.Location = new System.Drawing.Point(847, 81);
            this.labelI.Name = "labelI";
            this.labelI.Size = new System.Drawing.Size(10, 13);
            this.labelI.TabIndex = 20;
            this.labelI.Text = "I";
            // 
            // labelD
            // 
            this.labelD.AutoSize = true;
            this.labelD.Location = new System.Drawing.Point(908, 81);
            this.labelD.Name = "labelD";
            this.labelD.Size = new System.Drawing.Size(15, 13);
            this.labelD.TabIndex = 21;
            this.labelD.Text = "D";
            // 
            // numericUpDownIroulis
            // 
            this.numericUpDownIroulis.Location = new System.Drawing.Point(824, 106);
            this.numericUpDownIroulis.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numericUpDownIroulis.Name = "numericUpDownIroulis";
            this.numericUpDownIroulis.Size = new System.Drawing.Size(57, 20);
            this.numericUpDownIroulis.TabIndex = 22;
            this.numericUpDownIroulis.ValueChanged += new System.EventHandler(this.numericUpDownRoulis_ValueChanged);
            // 
            // numericUpDownDroulis
            // 
            this.numericUpDownDroulis.Location = new System.Drawing.Point(887, 106);
            this.numericUpDownDroulis.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numericUpDownDroulis.Name = "numericUpDownDroulis";
            this.numericUpDownDroulis.Size = new System.Drawing.Size(57, 20);
            this.numericUpDownDroulis.TabIndex = 23;
            this.numericUpDownDroulis.ValueChanged += new System.EventHandler(this.numericUpDownRoulis_ValueChanged);
            // 
            // numericUpDownDtangage
            // 
            this.numericUpDownDtangage.Location = new System.Drawing.Point(887, 132);
            this.numericUpDownDtangage.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numericUpDownDtangage.Name = "numericUpDownDtangage";
            this.numericUpDownDtangage.Size = new System.Drawing.Size(57, 20);
            this.numericUpDownDtangage.TabIndex = 26;
            this.numericUpDownDtangage.ValueChanged += new System.EventHandler(this.numericUpDowntangage_ValueChanged);
            // 
            // numericUpDownItangage
            // 
            this.numericUpDownItangage.Location = new System.Drawing.Point(824, 132);
            this.numericUpDownItangage.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numericUpDownItangage.Name = "numericUpDownItangage";
            this.numericUpDownItangage.Size = new System.Drawing.Size(57, 20);
            this.numericUpDownItangage.TabIndex = 25;
            this.numericUpDownItangage.ValueChanged += new System.EventHandler(this.numericUpDowntangage_ValueChanged);
            // 
            // numericUpDownPtangage
            // 
            this.numericUpDownPtangage.Location = new System.Drawing.Point(760, 132);
            this.numericUpDownPtangage.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numericUpDownPtangage.Name = "numericUpDownPtangage";
            this.numericUpDownPtangage.Size = new System.Drawing.Size(57, 20);
            this.numericUpDownPtangage.TabIndex = 24;
            this.numericUpDownPtangage.ValueChanged += new System.EventHandler(this.numericUpDowntangage_ValueChanged);
            // 
            // numericUpDownDlacet
            // 
            this.numericUpDownDlacet.Location = new System.Drawing.Point(887, 158);
            this.numericUpDownDlacet.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numericUpDownDlacet.Name = "numericUpDownDlacet";
            this.numericUpDownDlacet.Size = new System.Drawing.Size(57, 20);
            this.numericUpDownDlacet.TabIndex = 29;
            this.numericUpDownDlacet.ValueChanged += new System.EventHandler(this.numericUpDownLacet_ValueChanged);
            // 
            // numericUpDownIlacet
            // 
            this.numericUpDownIlacet.Location = new System.Drawing.Point(824, 158);
            this.numericUpDownIlacet.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numericUpDownIlacet.Name = "numericUpDownIlacet";
            this.numericUpDownIlacet.Size = new System.Drawing.Size(57, 20);
            this.numericUpDownIlacet.TabIndex = 28;
            this.numericUpDownIlacet.ValueChanged += new System.EventHandler(this.numericUpDownLacet_ValueChanged);
            // 
            // numericUpDownPlacet
            // 
            this.numericUpDownPlacet.Location = new System.Drawing.Point(760, 158);
            this.numericUpDownPlacet.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numericUpDownPlacet.Name = "numericUpDownPlacet";
            this.numericUpDownPlacet.Size = new System.Drawing.Size(57, 20);
            this.numericUpDownPlacet.TabIndex = 27;
            this.numericUpDownPlacet.ValueChanged += new System.EventHandler(this.numericUpDownLacet_ValueChanged);
            // 
            // labelRoulis
            // 
            this.labelRoulis.AutoSize = true;
            this.labelRoulis.ForeColor = System.Drawing.SystemColors.Desktop;
            this.labelRoulis.Location = new System.Drawing.Point(722, 108);
            this.labelRoulis.Name = "labelRoulis";
            this.labelRoulis.Size = new System.Drawing.Size(36, 13);
            this.labelRoulis.TabIndex = 30;
            this.labelRoulis.Text = "Roulis";
            // 
            // labelTangage
            // 
            this.labelTangage.AutoSize = true;
            this.labelTangage.Location = new System.Drawing.Point(708, 134);
            this.labelTangage.Name = "labelTangage";
            this.labelTangage.Size = new System.Drawing.Size(50, 13);
            this.labelTangage.TabIndex = 31;
            this.labelTangage.Text = "Tangage";
            // 
            // labelLacet
            // 
            this.labelLacet.AutoSize = true;
            this.labelLacet.Location = new System.Drawing.Point(724, 160);
            this.labelLacet.Name = "labelLacet";
            this.labelLacet.Size = new System.Drawing.Size(34, 13);
            this.labelLacet.TabIndex = 32;
            this.labelLacet.Text = "Lacet";
            // 
            // turn_indicator
            // 
            this.turn_indicator.Location = new System.Drawing.Point(396, 184);
            this.turn_indicator.Name = "turn_indicator";
            this.turn_indicator.Size = new System.Drawing.Size(150, 150);
            this.turn_indicator.TabIndex = 12;
            this.turn_indicator.Text = "turnCoordinatorInstrumentControl1";
            // 
            // vario_indicator
            // 
            this.vario_indicator.Location = new System.Drawing.Point(240, 184);
            this.vario_indicator.Name = "vario_indicator";
            this.vario_indicator.Size = new System.Drawing.Size(150, 150);
            this.vario_indicator.TabIndex = 11;
            this.vario_indicator.Text = "verticalSpeedIndicatorInstrumentControl1";
            // 
            // altimeter_indicator
            // 
            this.altimeter_indicator.Location = new System.Drawing.Point(552, 106);
            this.altimeter_indicator.Name = "altimeter_indicator";
            this.altimeter_indicator.Size = new System.Drawing.Size(150, 150);
            this.altimeter_indicator.TabIndex = 10;
            this.altimeter_indicator.Text = "altimeterInstrumentControl1";
            // 
            // heading_indicator
            // 
            this.heading_indicator.Location = new System.Drawing.Point(396, 28);
            this.heading_indicator.Name = "heading_indicator";
            this.heading_indicator.Size = new System.Drawing.Size(150, 150);
            this.heading_indicator.TabIndex = 9;
            this.heading_indicator.Text = "headingIndicatorInstrumentControl1";
            // 
            // horizon_indicator
            // 
            this.horizon_indicator.Location = new System.Drawing.Point(240, 28);
            this.horizon_indicator.Name = "horizon_indicator";
            this.horizon_indicator.Size = new System.Drawing.Size(150, 150);
            this.horizon_indicator.TabIndex = 8;
            this.horizon_indicator.Text = "attitudeIndicatorInstrumentControl1";
            // 
            // air_speed_indicator
            // 
            this.air_speed_indicator.Location = new System.Drawing.Point(84, 106);
            this.air_speed_indicator.Name = "air_speed_indicator";
            this.air_speed_indicator.Size = new System.Drawing.Size(150, 150);
            this.air_speed_indicator.TabIndex = 7;
            this.air_speed_indicator.Text = "airSpeedIndicatorInstrumentControl1";
            // 
            // GroundStation
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.GrayText;
            this.ClientSize = new System.Drawing.Size(967, 486);
            this.Controls.Add(this.labelLacet);
            this.Controls.Add(this.labelTangage);
            this.Controls.Add(this.labelRoulis);
            this.Controls.Add(this.numericUpDownDlacet);
            this.Controls.Add(this.numericUpDownIlacet);
            this.Controls.Add(this.numericUpDownPlacet);
            this.Controls.Add(this.numericUpDownDtangage);
            this.Controls.Add(this.numericUpDownItangage);
            this.Controls.Add(this.numericUpDownPtangage);
            this.Controls.Add(this.numericUpDownDroulis);
            this.Controls.Add(this.numericUpDownIroulis);
            this.Controls.Add(this.labelD);
            this.Controls.Add(this.labelI);
            this.Controls.Add(this.labelP);
            this.Controls.Add(this.numericUpDownProulis);
            this.Controls.Add(this.labelMot);
            this.Controls.Add(this.labelMag);
            this.Controls.Add(this.labelGyro);
            this.Controls.Add(this.labelAcc);
            this.Controls.Add(this.labelAttitude);
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
            this.ForeColor = System.Drawing.SystemColors.Desktop;
            this.MaximizeBox = false;
            this.Name = "GroundStation";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "GroundStationDrone";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.GroundStation_FormClosing);
            this.Load += new System.EventHandler(this.GroundStation_Load);
            this.statusStripState.ResumeLayout(false);
            this.statusStripState.PerformLayout();
            this.menuStripParams.ResumeLayout(false);
            this.menuStripParams.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarSpeed)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownProulis)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownIroulis)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownDroulis)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownDtangage)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownItangage)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPtangage)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownDlacet)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownIlacet)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPlacet)).EndInit();
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
        private System.Windows.Forms.ToolStripMenuItem setPIDsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem getPIDsToolStripMenuItem;
        private System.Windows.Forms.Panel panel1;
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
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItemView;
        private System.Windows.Forms.ToolStripMenuItem cockpitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem graphToolStripMenuItem;
        private System.Windows.Forms.Label labelAttitude;
        private System.Windows.Forms.Label labelAcc;
        private System.Windows.Forms.Label labelGyro;
        private System.Windows.Forms.Label labelMag;
        private System.Windows.Forms.Label labelMot;
        private System.Windows.Forms.NumericUpDown numericUpDownProulis;
        private System.Windows.Forms.Label labelP;
        private System.Windows.Forms.Label labelI;
        private System.Windows.Forms.Label labelD;
        private System.Windows.Forms.NumericUpDown numericUpDownIroulis;
        private System.Windows.Forms.NumericUpDown numericUpDownDroulis;
        private System.Windows.Forms.NumericUpDown numericUpDownDtangage;
        private System.Windows.Forms.NumericUpDown numericUpDownItangage;
        private System.Windows.Forms.NumericUpDown numericUpDownPtangage;
        private System.Windows.Forms.NumericUpDown numericUpDownDlacet;
        private System.Windows.Forms.NumericUpDown numericUpDownIlacet;
        private System.Windows.Forms.NumericUpDown numericUpDownPlacet;
        private System.Windows.Forms.Label labelRoulis;
        private System.Windows.Forms.Label labelTangage;
        private System.Windows.Forms.Label labelLacet;

    }
}

