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
            this.toolStripSep = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripStatusLabelSpeed = new System.Windows.Forms.ToolStripStatusLabel();
            this.menuStripParams = new System.Windows.Forms.MenuStrip();
            this.generalToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.getVersionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.resetToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.recalibrationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItemMotors = new System.Windows.Forms.ToolStripMenuItem();
            this.getSpeedToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.trackBarSpeed = new System.Windows.Forms.TrackBar();
            this.statusStripState.SuspendLayout();
            this.menuStripParams.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarSpeed)).BeginInit();
            this.SuspendLayout();
            // 
            // statusStripState
            // 
            this.statusStripState.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabelVersion,
            this.toolStripSep,
            this.toolStripStatusLabelSpeed});
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
            // toolStripSep
            // 
            this.toolStripSep.Name = "toolStripSep";
            this.toolStripSep.Size = new System.Drawing.Size(6, 23);
            // 
            // toolStripStatusLabelSpeed
            // 
            this.toolStripStatusLabelSpeed.Name = "toolStripStatusLabelSpeed";
            this.toolStripStatusLabelSpeed.Size = new System.Drawing.Size(59, 18);
            this.toolStripStatusLabelSpeed.Text = "Speed = 0";
            // 
            // menuStripParams
            // 
            this.menuStripParams.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.generalToolStripMenuItem,
            this.toolStripMenuItemMotors});
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
            this.getSpeedToolStripMenuItem});
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
            // trackBarSpeed
            // 
            this.trackBarSpeed.Location = new System.Drawing.Point(30, 54);
            this.trackBarSpeed.Maximum = 1000;
            this.trackBarSpeed.Name = "trackBarSpeed";
            this.trackBarSpeed.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.trackBarSpeed.Size = new System.Drawing.Size(45, 104);
            this.trackBarSpeed.TabIndex = 5;
            this.trackBarSpeed.TickFrequency = 100;
            this.trackBarSpeed.TickStyle = System.Windows.Forms.TickStyle.Both;
            this.trackBarSpeed.Scroll += new System.EventHandler(this.trackBarSpeed_Scroll);
            // 
            // GroundStation
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(756, 382);
            this.Controls.Add(this.trackBarSpeed);
            this.Controls.Add(this.statusStripState);
            this.Controls.Add(this.menuStripParams);
            this.Name = "GroundStation";
            this.Text = "GroundStation";
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
        private System.Windows.Forms.ToolStripSeparator toolStripSep;
        private System.Windows.Forms.MenuStrip menuStripParams;
        private System.Windows.Forms.ToolStripMenuItem generalToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem getVersionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem resetToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem recalibrationToolStripMenuItem;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabelSpeed;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItemMotors;
        private System.Windows.Forms.ToolStripMenuItem getSpeedToolStripMenuItem;
        private System.Windows.Forms.TrackBar trackBarSpeed;

    }
}

