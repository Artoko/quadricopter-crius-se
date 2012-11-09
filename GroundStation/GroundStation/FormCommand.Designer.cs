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
            ((System.ComponentModel.ISupportInitialize)(this.PowerTrackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarRoulis)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarTangage)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarLacet)).BeginInit();
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
            this.PowerTrackBar.Maximum = 1000;
            this.PowerTrackBar.Name = "PowerTrackBar";
            this.PowerTrackBar.Size = new System.Drawing.Size(268, 45);
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
            this.trackBarLacet.Maximum = 900;
            this.trackBarLacet.Name = "trackBarLacet";
            this.trackBarLacet.Size = new System.Drawing.Size(268, 45);
            this.trackBarLacet.TabIndex = 1;
            this.trackBarLacet.TickFrequency = 10;
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
            this.buttonReset.Location = new System.Drawing.Point(21, 304);
            this.buttonReset.Name = "buttonReset";
            this.buttonReset.Size = new System.Drawing.Size(120, 23);
            this.buttonReset.TabIndex = 3;
            this.buttonReset.Text = "Reset";
            this.buttonReset.UseVisualStyleBackColor = true;
            this.buttonReset.Click += new System.EventHandler(this.buttonReset_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(21, 333);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(120, 23);
            this.button1.TabIndex = 3;
            this.button1.Text = "Reset eeprom";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.buttonReseteeprom_Click);
            // 
            // FormCommand
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(402, 371);
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
            ((System.ComponentModel.ISupportInitialize)(this.PowerTrackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarRoulis)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarTangage)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarLacet)).EndInit();
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
    }
}