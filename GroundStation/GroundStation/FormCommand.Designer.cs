namespace GroundStation
{
    partial class FormCommand
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
            this.Stopbutton = new System.Windows.Forms.Button();
            this.PowerTrackBar = new System.Windows.Forms.TrackBar();
            this.labelspeed = new System.Windows.Forms.Label();
            this.trackBarRoulis = new System.Windows.Forms.TrackBar();
            this.labelroulis = new System.Windows.Forms.Label();
            this.trackBarTangage = new System.Windows.Forms.TrackBar();
            this.labeltangage = new System.Windows.Forms.Label();
            this.trackBarLacet = new System.Windows.Forms.TrackBar();
            this.labelLacet = new System.Windows.Forms.Label();
            this.buttonReset = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.checkBoxFullSpeed = new System.Windows.Forms.CheckBox();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.numericUpDownP = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownI = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownD = new System.Windows.Forms.NumericUpDown();
            this.labelP = new System.Windows.Forms.Label();
            this.labelI = new System.Windows.Forms.Label();
            this.labelD = new System.Windows.Forms.Label();
            this.labelindex = new System.Windows.Forms.Label();
            this.ButtonWrite = new System.Windows.Forms.Button();
            this.buttonRepportData = new System.Windows.Forms.Button();
            this.buttonRead = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.buttonAltitude = new System.Windows.Forms.Button();
            this.numericUpDown2 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown3 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown4 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown5 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown6 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown7 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown8 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown9 = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            this.button7 = new System.Windows.Forms.Button();
            this.button8 = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.button9 = new System.Windows.Forms.Button();
            this.numericUpDown10 = new System.Windows.Forms.NumericUpDown();
            ((System.ComponentModel.ISupportInitialize)(this.PowerTrackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarRoulis)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarTangage)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarLacet)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownP)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownI)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownD)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown5)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown6)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown7)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown8)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown9)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown10)).BeginInit();
            this.SuspendLayout();
            // 
            // Stopbutton
            // 
            this.Stopbutton.BackColor = System.Drawing.Color.Red;
            this.Stopbutton.Location = new System.Drawing.Point(21, 12);
            this.Stopbutton.Name = "Stopbutton";
            this.Stopbutton.Size = new System.Drawing.Size(259, 58);
            this.Stopbutton.TabIndex = 0;
            this.Stopbutton.Text = "Stop";
            this.Stopbutton.UseVisualStyleBackColor = false;
            this.Stopbutton.Click += new System.EventHandler(this.Speedbutton_Click);
            // 
            // PowerTrackBar
            // 
            this.PowerTrackBar.LargeChange = 1;
            this.PowerTrackBar.Location = new System.Drawing.Point(12, 89);
            this.PowerTrackBar.Maximum = 500;
            this.PowerTrackBar.Name = "PowerTrackBar";
            this.PowerTrackBar.Size = new System.Drawing.Size(268, 45);
            this.PowerTrackBar.SmallChange = 10;
            this.PowerTrackBar.TabIndex = 1;
            this.PowerTrackBar.TickFrequency = 10;
            this.PowerTrackBar.ValueChanged += new System.EventHandler(this.PowerTrackBar_ValueChanged);
            // 
            // labelspeed
            // 
            this.labelspeed.AutoSize = true;
            this.labelspeed.Location = new System.Drawing.Point(286, 100);
            this.labelspeed.Name = "labelspeed";
            this.labelspeed.Size = new System.Drawing.Size(51, 13);
            this.labelspeed.TabIndex = 2;
            this.labelspeed.Text = "speed : 0";
            // 
            // trackBarRoulis
            // 
            this.trackBarRoulis.LargeChange = 1;
            this.trackBarRoulis.Location = new System.Drawing.Point(12, 131);
            this.trackBarRoulis.Maximum = 900;
            this.trackBarRoulis.Minimum = -900;
            this.trackBarRoulis.Name = "trackBarRoulis";
            this.trackBarRoulis.Size = new System.Drawing.Size(268, 45);
            this.trackBarRoulis.TabIndex = 1;
            this.trackBarRoulis.TickFrequency = 10;
            this.trackBarRoulis.ValueChanged += new System.EventHandler(this.RoulisTrackBar_ValueChanged);
            // 
            // labelroulis
            // 
            this.labelroulis.AutoSize = true;
            this.labelroulis.Location = new System.Drawing.Point(286, 142);
            this.labelroulis.Name = "labelroulis";
            this.labelroulis.Size = new System.Drawing.Size(75, 13);
            this.labelroulis.TabIndex = 2;
            this.labelroulis.Text = "roulis angle : 0";
            // 
            // trackBarTangage
            // 
            this.trackBarTangage.LargeChange = 1;
            this.trackBarTangage.Location = new System.Drawing.Point(12, 177);
            this.trackBarTangage.Maximum = 900;
            this.trackBarTangage.Minimum = -900;
            this.trackBarTangage.Name = "trackBarTangage";
            this.trackBarTangage.Size = new System.Drawing.Size(268, 45);
            this.trackBarTangage.TabIndex = 1;
            this.trackBarTangage.TickFrequency = 10;
            this.trackBarTangage.ValueChanged += new System.EventHandler(this.tangageTrackBar_ValueChanged);
            // 
            // labeltangage
            // 
            this.labeltangage.AutoSize = true;
            this.labeltangage.Location = new System.Drawing.Point(286, 188);
            this.labeltangage.Name = "labeltangage";
            this.labeltangage.Size = new System.Drawing.Size(90, 13);
            this.labeltangage.TabIndex = 2;
            this.labeltangage.Text = "tangage angle : 0";
            // 
            // trackBarLacet
            // 
            this.trackBarLacet.LargeChange = 1;
            this.trackBarLacet.Location = new System.Drawing.Point(12, 225);
            this.trackBarLacet.Maximum = 100;
            this.trackBarLacet.Minimum = -100;
            this.trackBarLacet.Name = "trackBarLacet";
            this.trackBarLacet.Size = new System.Drawing.Size(268, 45);
            this.trackBarLacet.TabIndex = 1;
            this.trackBarLacet.ValueChanged += new System.EventHandler(this.LacetTrackBar_ValueChanged);
            // 
            // labelLacet
            // 
            this.labelLacet.AutoSize = true;
            this.labelLacet.Location = new System.Drawing.Point(286, 236);
            this.labelLacet.Name = "labelLacet";
            this.labelLacet.Size = new System.Drawing.Size(74, 13);
            this.labelLacet.TabIndex = 2;
            this.labelLacet.Text = "lacet angle : 0";
            // 
            // buttonReset
            // 
            this.buttonReset.Location = new System.Drawing.Point(58, 430);
            this.buttonReset.Name = "buttonReset";
            this.buttonReset.Size = new System.Drawing.Size(120, 23);
            this.buttonReset.TabIndex = 3;
            this.buttonReset.Text = "Reset";
            this.buttonReset.UseVisualStyleBackColor = true;
            this.buttonReset.Click += new System.EventHandler(this.buttonReset_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(184, 430);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(120, 23);
            this.button1.TabIndex = 3;
            this.button1.Text = "Reset eeprom";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.buttonReseteeprom_Click);
            // 
            // checkBoxFullSpeed
            // 
            this.checkBoxFullSpeed.AutoSize = true;
            this.checkBoxFullSpeed.Location = new System.Drawing.Point(388, 99);
            this.checkBoxFullSpeed.Name = "checkBoxFullSpeed";
            this.checkBoxFullSpeed.Size = new System.Drawing.Size(74, 17);
            this.checkBoxFullSpeed.TabIndex = 4;
            this.checkBoxFullSpeed.Text = "Full speed";
            this.checkBoxFullSpeed.UseVisualStyleBackColor = true;
            this.checkBoxFullSpeed.CheckedChanged += new System.EventHandler(this.checkBoxFullSpeed_CheckedChanged);
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(388, 159);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(145, 17);
            this.checkBox1.TabIndex = 5;
            this.checkBox1.Text = "Combine roulis && tangage";
            this.checkBox1.UseVisualStyleBackColor = true;
            // 
            // numericUpDownP
            // 
            this.numericUpDownP.Location = new System.Drawing.Point(58, 302);
            this.numericUpDownP.Maximum = new decimal(new int[] {
            33000,
            0,
            0,
            0});
            this.numericUpDownP.Minimum = new decimal(new int[] {
            33000,
            0,
            0,
            -2147483648});
            this.numericUpDownP.Name = "numericUpDownP";
            this.numericUpDownP.Size = new System.Drawing.Size(86, 20);
            this.numericUpDownP.TabIndex = 6;
            // 
            // numericUpDownI
            // 
            this.numericUpDownI.Location = new System.Drawing.Point(150, 302);
            this.numericUpDownI.Maximum = new decimal(new int[] {
            33000,
            0,
            0,
            0});
            this.numericUpDownI.Minimum = new decimal(new int[] {
            33000,
            0,
            0,
            -2147483648});
            this.numericUpDownI.Name = "numericUpDownI";
            this.numericUpDownI.Size = new System.Drawing.Size(86, 20);
            this.numericUpDownI.TabIndex = 6;
            // 
            // numericUpDownD
            // 
            this.numericUpDownD.Location = new System.Drawing.Point(242, 302);
            this.numericUpDownD.Maximum = new decimal(new int[] {
            33000,
            0,
            0,
            0});
            this.numericUpDownD.Minimum = new decimal(new int[] {
            33000,
            0,
            0,
            -2147483648});
            this.numericUpDownD.Name = "numericUpDownD";
            this.numericUpDownD.Size = new System.Drawing.Size(86, 20);
            this.numericUpDownD.TabIndex = 6;
            // 
            // labelP
            // 
            this.labelP.AutoSize = true;
            this.labelP.Location = new System.Drawing.Point(77, 286);
            this.labelP.Name = "labelP";
            this.labelP.Size = new System.Drawing.Size(43, 13);
            this.labelP.TabIndex = 7;
            this.labelP.Text = "P  (/10)";
            // 
            // labelI
            // 
            this.labelI.AutoSize = true;
            this.labelI.Location = new System.Drawing.Point(171, 286);
            this.labelI.Name = "labelI";
            this.labelI.Size = new System.Drawing.Size(39, 13);
            this.labelI.TabIndex = 7;
            this.labelI.Text = "I  (/10)";
            // 
            // labelD
            // 
            this.labelD.AutoSize = true;
            this.labelD.Location = new System.Drawing.Point(258, 286);
            this.labelD.Name = "labelD";
            this.labelD.Size = new System.Drawing.Size(44, 13);
            this.labelD.TabIndex = 7;
            this.labelD.Text = "D  (/10)";
            // 
            // labelindex
            // 
            this.labelindex.AutoSize = true;
            this.labelindex.Location = new System.Drawing.Point(9, 304);
            this.labelindex.Name = "labelindex";
            this.labelindex.Size = new System.Drawing.Size(36, 13);
            this.labelindex.TabIndex = 7;
            this.labelindex.Text = "Roulis";
            // 
            // ButtonWrite
            // 
            this.ButtonWrite.Location = new System.Drawing.Point(334, 299);
            this.ButtonWrite.Name = "ButtonWrite";
            this.ButtonWrite.Size = new System.Drawing.Size(75, 23);
            this.ButtonWrite.TabIndex = 9;
            this.ButtonWrite.Text = "Write";
            this.ButtonWrite.UseVisualStyleBackColor = true;
            this.ButtonWrite.Click += new System.EventHandler(this.ButtonWrite_Click);
            // 
            // buttonRepportData
            // 
            this.buttonRepportData.Location = new System.Drawing.Point(310, 430);
            this.buttonRepportData.Name = "buttonRepportData";
            this.buttonRepportData.Size = new System.Drawing.Size(120, 23);
            this.buttonRepportData.TabIndex = 10;
            this.buttonRepportData.Text = "Repport Data";
            this.buttonRepportData.UseVisualStyleBackColor = true;
            this.buttonRepportData.Click += new System.EventHandler(this.buttonRepportData_Click);
            // 
            // buttonRead
            // 
            this.buttonRead.Location = new System.Drawing.Point(415, 299);
            this.buttonRead.Name = "buttonRead";
            this.buttonRead.Size = new System.Drawing.Size(75, 23);
            this.buttonRead.TabIndex = 9;
            this.buttonRead.Text = "Read";
            this.buttonRead.UseVisualStyleBackColor = true;
            this.buttonRead.Click += new System.EventHandler(this.ButtonRead_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(388, 202);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 11;
            this.button2.Text = "Weather";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // buttonAltitude
            // 
            this.buttonAltitude.Location = new System.Drawing.Point(388, 231);
            this.buttonAltitude.Name = "buttonAltitude";
            this.buttonAltitude.Size = new System.Drawing.Size(108, 23);
            this.buttonAltitude.TabIndex = 14;
            this.buttonAltitude.Text = "Set Altitude";
            this.buttonAltitude.UseVisualStyleBackColor = true;
            this.buttonAltitude.Click += new System.EventHandler(this.buttonAltitude_Click);
            // 
            // numericUpDown2
            // 
            this.numericUpDown2.Location = new System.Drawing.Point(242, 333);
            this.numericUpDown2.Maximum = new decimal(new int[] {
            33000,
            0,
            0,
            0});
            this.numericUpDown2.Minimum = new decimal(new int[] {
            33000,
            0,
            0,
            -2147483648});
            this.numericUpDown2.Name = "numericUpDown2";
            this.numericUpDown2.Size = new System.Drawing.Size(86, 20);
            this.numericUpDown2.TabIndex = 15;
            // 
            // numericUpDown3
            // 
            this.numericUpDown3.Location = new System.Drawing.Point(150, 333);
            this.numericUpDown3.Maximum = new decimal(new int[] {
            33000,
            0,
            0,
            0});
            this.numericUpDown3.Minimum = new decimal(new int[] {
            33000,
            0,
            0,
            -2147483648});
            this.numericUpDown3.Name = "numericUpDown3";
            this.numericUpDown3.Size = new System.Drawing.Size(86, 20);
            this.numericUpDown3.TabIndex = 16;
            // 
            // numericUpDown4
            // 
            this.numericUpDown4.Location = new System.Drawing.Point(58, 333);
            this.numericUpDown4.Maximum = new decimal(new int[] {
            33000,
            0,
            0,
            0});
            this.numericUpDown4.Minimum = new decimal(new int[] {
            33000,
            0,
            0,
            -2147483648});
            this.numericUpDown4.Name = "numericUpDown4";
            this.numericUpDown4.Size = new System.Drawing.Size(86, 20);
            this.numericUpDown4.TabIndex = 17;
            // 
            // numericUpDown1
            // 
            this.numericUpDown1.Location = new System.Drawing.Point(242, 362);
            this.numericUpDown1.Maximum = new decimal(new int[] {
            33000,
            0,
            0,
            0});
            this.numericUpDown1.Minimum = new decimal(new int[] {
            33000,
            0,
            0,
            -2147483648});
            this.numericUpDown1.Name = "numericUpDown1";
            this.numericUpDown1.Size = new System.Drawing.Size(86, 20);
            this.numericUpDown1.TabIndex = 25;
            // 
            // numericUpDown5
            // 
            this.numericUpDown5.Location = new System.Drawing.Point(150, 362);
            this.numericUpDown5.Maximum = new decimal(new int[] {
            33000,
            0,
            0,
            0});
            this.numericUpDown5.Minimum = new decimal(new int[] {
            33000,
            0,
            0,
            -2147483648});
            this.numericUpDown5.Name = "numericUpDown5";
            this.numericUpDown5.Size = new System.Drawing.Size(86, 20);
            this.numericUpDown5.TabIndex = 26;
            // 
            // numericUpDown6
            // 
            this.numericUpDown6.Location = new System.Drawing.Point(58, 362);
            this.numericUpDown6.Maximum = new decimal(new int[] {
            33000,
            0,
            0,
            0});
            this.numericUpDown6.Minimum = new decimal(new int[] {
            33000,
            0,
            0,
            -2147483648});
            this.numericUpDown6.Name = "numericUpDown6";
            this.numericUpDown6.Size = new System.Drawing.Size(86, 20);
            this.numericUpDown6.TabIndex = 27;
            // 
            // numericUpDown7
            // 
            this.numericUpDown7.Location = new System.Drawing.Point(242, 391);
            this.numericUpDown7.Maximum = new decimal(new int[] {
            33000,
            0,
            0,
            0});
            this.numericUpDown7.Minimum = new decimal(new int[] {
            33000,
            0,
            0,
            -2147483648});
            this.numericUpDown7.Name = "numericUpDown7";
            this.numericUpDown7.Size = new System.Drawing.Size(86, 20);
            this.numericUpDown7.TabIndex = 28;
            // 
            // numericUpDown8
            // 
            this.numericUpDown8.Location = new System.Drawing.Point(150, 391);
            this.numericUpDown8.Maximum = new decimal(new int[] {
            33000,
            0,
            0,
            0});
            this.numericUpDown8.Minimum = new decimal(new int[] {
            33000,
            0,
            0,
            -2147483648});
            this.numericUpDown8.Name = "numericUpDown8";
            this.numericUpDown8.Size = new System.Drawing.Size(86, 20);
            this.numericUpDown8.TabIndex = 29;
            // 
            // numericUpDown9
            // 
            this.numericUpDown9.Location = new System.Drawing.Point(58, 391);
            this.numericUpDown9.Maximum = new decimal(new int[] {
            33000,
            0,
            0,
            0});
            this.numericUpDown9.Minimum = new decimal(new int[] {
            33000,
            0,
            0,
            -2147483648});
            this.numericUpDown9.Name = "numericUpDown9";
            this.numericUpDown9.Size = new System.Drawing.Size(86, 20);
            this.numericUpDown9.TabIndex = 30;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 335);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(50, 13);
            this.label1.TabIndex = 7;
            this.label1.Text = "Tangage";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 364);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(34, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "Lacet";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(9, 393);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(42, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "Altitude";
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(415, 330);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 23);
            this.button3.TabIndex = 31;
            this.button3.Text = "Read";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(334, 330);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(75, 23);
            this.button4.TabIndex = 32;
            this.button4.Text = "Write";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(415, 359);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(75, 23);
            this.button5.TabIndex = 33;
            this.button5.Text = "Read";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(334, 359);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(75, 23);
            this.button6.TabIndex = 34;
            this.button6.Text = "Write";
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Click += new System.EventHandler(this.button6_Click);
            // 
            // button7
            // 
            this.button7.Location = new System.Drawing.Point(415, 388);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(75, 23);
            this.button7.TabIndex = 35;
            this.button7.Text = "Read";
            this.button7.UseVisualStyleBackColor = true;
            this.button7.Click += new System.EventHandler(this.button7_Click);
            // 
            // button8
            // 
            this.button8.Location = new System.Drawing.Point(334, 388);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(75, 23);
            this.button8.TabIndex = 36;
            this.button8.Text = "Write";
            this.button8.UseVisualStyleBackColor = true;
            this.button8.Click += new System.EventHandler(this.button8_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(97, 289);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(0, 13);
            this.label4.TabIndex = 37;
            // 
            // button9
            // 
            this.button9.Location = new System.Drawing.Point(388, 260);
            this.button9.Name = "button9";
            this.button9.Size = new System.Drawing.Size(108, 23);
            this.button9.TabIndex = 14;
            this.button9.Text = "Maintient Altitude";
            this.button9.UseVisualStyleBackColor = true;
            this.button9.Click += new System.EventHandler(this.button9_Click);
            // 
            // numericUpDown10
            // 
            this.numericUpDown10.Location = new System.Drawing.Point(502, 263);
            this.numericUpDown10.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.numericUpDown10.Minimum = new decimal(new int[] {
            1000,
            0,
            0,
            -2147483648});
            this.numericUpDown10.Name = "numericUpDown10";
            this.numericUpDown10.Size = new System.Drawing.Size(52, 20);
            this.numericUpDown10.TabIndex = 38;
            // 
            // FormCommand
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(573, 538);
            this.Controls.Add(this.numericUpDown10);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.button7);
            this.Controls.Add(this.button8);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.button6);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.numericUpDown7);
            this.Controls.Add(this.numericUpDown8);
            this.Controls.Add(this.numericUpDown9);
            this.Controls.Add(this.numericUpDown1);
            this.Controls.Add(this.numericUpDown5);
            this.Controls.Add(this.numericUpDown6);
            this.Controls.Add(this.numericUpDown2);
            this.Controls.Add(this.numericUpDown3);
            this.Controls.Add(this.numericUpDown4);
            this.Controls.Add(this.button9);
            this.Controls.Add(this.buttonAltitude);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.buttonRepportData);
            this.Controls.Add(this.buttonRead);
            this.Controls.Add(this.ButtonWrite);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.labelindex);
            this.Controls.Add(this.labelD);
            this.Controls.Add(this.labelI);
            this.Controls.Add(this.labelP);
            this.Controls.Add(this.numericUpDownD);
            this.Controls.Add(this.numericUpDownI);
            this.Controls.Add(this.numericUpDownP);
            this.Controls.Add(this.checkBox1);
            this.Controls.Add(this.checkBoxFullSpeed);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.buttonReset);
            this.Controls.Add(this.labelLacet);
            this.Controls.Add(this.labeltangage);
            this.Controls.Add(this.trackBarLacet);
            this.Controls.Add(this.labelroulis);
            this.Controls.Add(this.trackBarTangage);
            this.Controls.Add(this.labelspeed);
            this.Controls.Add(this.trackBarRoulis);
            this.Controls.Add(this.PowerTrackBar);
            this.Controls.Add(this.Stopbutton);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormCommand";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.Text = "Command";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormCommand_FormClosing);
            this.Load += new System.EventHandler(this.FormCommand_Load);
            ((System.ComponentModel.ISupportInitialize)(this.PowerTrackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarRoulis)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarTangage)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarLacet)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownP)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownI)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownD)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown5)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown6)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown7)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown8)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown9)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown10)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button Stopbutton;
        private System.Windows.Forms.TrackBar PowerTrackBar;
        private System.Windows.Forms.Label labelspeed;
        private System.Windows.Forms.TrackBar trackBarRoulis;
        private System.Windows.Forms.Label labelroulis;
        private System.Windows.Forms.TrackBar trackBarTangage;
        private System.Windows.Forms.Label labeltangage;
        private System.Windows.Forms.TrackBar trackBarLacet;
        private System.Windows.Forms.Label labelLacet;
        private System.Windows.Forms.Button buttonReset;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.CheckBox checkBoxFullSpeed;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.NumericUpDown numericUpDownP;
        private System.Windows.Forms.NumericUpDown numericUpDownI;
        private System.Windows.Forms.NumericUpDown numericUpDownD;
        private System.Windows.Forms.Label labelP;
        private System.Windows.Forms.Label labelI;
        private System.Windows.Forms.Label labelD;
        private System.Windows.Forms.Label labelindex;
        private System.Windows.Forms.Button ButtonWrite;
        private System.Windows.Forms.Button buttonRepportData;
        private System.Windows.Forms.Button buttonRead;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button buttonAltitude;
        private System.Windows.Forms.NumericUpDown numericUpDown2;
        private System.Windows.Forms.NumericUpDown numericUpDown3;
        private System.Windows.Forms.NumericUpDown numericUpDown4;
        private System.Windows.Forms.NumericUpDown numericUpDown1;
        private System.Windows.Forms.NumericUpDown numericUpDown5;
        private System.Windows.Forms.NumericUpDown numericUpDown6;
        private System.Windows.Forms.NumericUpDown numericUpDown7;
        private System.Windows.Forms.NumericUpDown numericUpDown8;
        private System.Windows.Forms.NumericUpDown numericUpDown9;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.Button button8;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button button9;
        private System.Windows.Forms.NumericUpDown numericUpDown10;
    }
}