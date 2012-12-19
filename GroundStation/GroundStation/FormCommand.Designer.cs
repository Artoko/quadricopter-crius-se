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
            this.numericUpDownindex = new System.Windows.Forms.NumericUpDown();
            this.labelindex = new System.Windows.Forms.Label();
            this.ButtonWrite = new System.Windows.Forms.Button();
            this.buttonRepportData = new System.Windows.Forms.Button();
            this.buttonRead = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.PowerTrackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarRoulis)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarTangage)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarLacet)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownP)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownI)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownD)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownindex)).BeginInit();
            this.SuspendLayout();
            // 
            // Stopbutton
            // 
            this.Stopbutton.BackColor = System.Drawing.Color.Red;
            this.Stopbutton.Location = new System.Drawing.Point(21, 12);
            this.Stopbutton.Name = "Stopbutton";
            this.Stopbutton.Size = new System.Drawing.Size(355, 58);
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
            this.buttonReset.Location = new System.Drawing.Point(12, 340);
            this.buttonReset.Name = "buttonReset";
            this.buttonReset.Size = new System.Drawing.Size(120, 23);
            this.buttonReset.TabIndex = 3;
            this.buttonReset.Text = "Reset";
            this.buttonReset.UseVisualStyleBackColor = true;
            this.buttonReset.Click += new System.EventHandler(this.buttonReset_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(138, 340);
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
            this.checkBoxFullSpeed.Location = new System.Drawing.Point(362, 100);
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
            this.numericUpDownP.Location = new System.Drawing.Point(55, 304);
            this.numericUpDownP.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.numericUpDownP.Minimum = new decimal(new int[] {
            1000,
            0,
            0,
            -2147483648});
            this.numericUpDownP.Name = "numericUpDownP";
            this.numericUpDownP.Size = new System.Drawing.Size(86, 20);
            this.numericUpDownP.TabIndex = 6;
            // 
            // numericUpDownI
            // 
            this.numericUpDownI.Location = new System.Drawing.Point(147, 304);
            this.numericUpDownI.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.numericUpDownI.Minimum = new decimal(new int[] {
            1000,
            0,
            0,
            -2147483648});
            this.numericUpDownI.Name = "numericUpDownI";
            this.numericUpDownI.Size = new System.Drawing.Size(86, 20);
            this.numericUpDownI.TabIndex = 6;
            // 
            // numericUpDownD
            // 
            this.numericUpDownD.Location = new System.Drawing.Point(239, 304);
            this.numericUpDownD.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.numericUpDownD.Minimum = new decimal(new int[] {
            1000,
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
            this.labelP.Location = new System.Drawing.Point(91, 285);
            this.labelP.Name = "labelP";
            this.labelP.Size = new System.Drawing.Size(14, 13);
            this.labelP.TabIndex = 7;
            this.labelP.Text = "P";
            // 
            // labelI
            // 
            this.labelI.AutoSize = true;
            this.labelI.Location = new System.Drawing.Point(179, 288);
            this.labelI.Name = "labelI";
            this.labelI.Size = new System.Drawing.Size(39, 13);
            this.labelI.TabIndex = 7;
            this.labelI.Text = "I  (/10)";
            // 
            // labelD
            // 
            this.labelD.AutoSize = true;
            this.labelD.Location = new System.Drawing.Point(274, 285);
            this.labelD.Name = "labelD";
            this.labelD.Size = new System.Drawing.Size(15, 13);
            this.labelD.TabIndex = 7;
            this.labelD.Text = "D";
            // 
            // numericUpDownindex
            // 
            this.numericUpDownindex.Location = new System.Drawing.Point(8, 304);
            this.numericUpDownindex.Name = "numericUpDownindex";
            this.numericUpDownindex.Size = new System.Drawing.Size(41, 20);
            this.numericUpDownindex.TabIndex = 8;
            // 
            // labelindex
            // 
            this.labelindex.AutoSize = true;
            this.labelindex.Location = new System.Drawing.Point(12, 285);
            this.labelindex.Name = "labelindex";
            this.labelindex.Size = new System.Drawing.Size(33, 13);
            this.labelindex.TabIndex = 7;
            this.labelindex.Text = "Index";
            // 
            // ButtonWrite
            // 
            this.ButtonWrite.Location = new System.Drawing.Point(331, 301);
            this.ButtonWrite.Name = "ButtonWrite";
            this.ButtonWrite.Size = new System.Drawing.Size(75, 23);
            this.ButtonWrite.TabIndex = 9;
            this.ButtonWrite.Text = "Write";
            this.ButtonWrite.UseVisualStyleBackColor = true;
            this.ButtonWrite.Click += new System.EventHandler(this.ButtonWrite_Click);
            // 
            // buttonRepportData
            // 
            this.buttonRepportData.Location = new System.Drawing.Point(264, 340);
            this.buttonRepportData.Name = "buttonRepportData";
            this.buttonRepportData.Size = new System.Drawing.Size(120, 23);
            this.buttonRepportData.TabIndex = 10;
            this.buttonRepportData.Text = "Repport Data";
            this.buttonRepportData.UseVisualStyleBackColor = true;
            this.buttonRepportData.Click += new System.EventHandler(this.buttonRepportData_Click);
            // 
            // buttonRead
            // 
            this.buttonRead.Location = new System.Drawing.Point(412, 301);
            this.buttonRead.Name = "buttonRead";
            this.buttonRead.Size = new System.Drawing.Size(75, 23);
            this.buttonRead.TabIndex = 9;
            this.buttonRead.Text = "Read";
            this.buttonRead.UseVisualStyleBackColor = true;
            this.buttonRead.Click += new System.EventHandler(this.ButtonRead_Click);
            // 
            // FormCommand
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(563, 372);
            this.Controls.Add(this.buttonRepportData);
            this.Controls.Add(this.buttonRead);
            this.Controls.Add(this.ButtonWrite);
            this.Controls.Add(this.numericUpDownindex);
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
            ((System.ComponentModel.ISupportInitialize)(this.PowerTrackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarRoulis)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarTangage)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarLacet)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownP)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownI)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownD)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownindex)).EndInit();
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
        private System.Windows.Forms.NumericUpDown numericUpDownindex;
        private System.Windows.Forms.Label labelindex;
        private System.Windows.Forms.Button ButtonWrite;
        private System.Windows.Forms.Button buttonRepportData;
        private System.Windows.Forms.Button buttonRead;
    }
}