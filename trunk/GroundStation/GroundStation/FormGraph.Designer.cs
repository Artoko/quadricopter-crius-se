﻿namespace GroundStation
{
    partial class FormGraph
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
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.zedGraphControl1 = new ZedGraph.ZedGraphControl();
            this.timer_tick = new System.Windows.Forms.Timer(this.components);
            this.button1 = new System.Windows.Forms.Button();
            this.checkBoxRoulis = new System.Windows.Forms.CheckBox();
            this.checkBoxtangage = new System.Windows.Forms.CheckBox();
            this.checkBoxlacet = new System.Windows.Forms.CheckBox();
            this.checkBoxpidroulis = new System.Windows.Forms.CheckBox();
            this.checkBoxpidtangage = new System.Windows.Forms.CheckBox();
            this.checkBoxaltitude = new System.Windows.Forms.CheckBox();
            this.checkBoxpidlacet = new System.Windows.Forms.CheckBox();
            this.checkBoxpression = new System.Windows.Forms.CheckBox();
            this.checkBoxtemperature = new System.Windows.Forms.CheckBox();
            this.checkBoxnord = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // zedGraphControl1
            // 
            this.zedGraphControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.zedGraphControl1.Location = new System.Drawing.Point(98, 12);
            this.zedGraphControl1.Name = "zedGraphControl1";
            this.zedGraphControl1.ScrollGrace = 0D;
            this.zedGraphControl1.ScrollMaxX = 0D;
            this.zedGraphControl1.ScrollMaxY = 0D;
            this.zedGraphControl1.ScrollMaxY2 = 0D;
            this.zedGraphControl1.ScrollMinX = 0D;
            this.zedGraphControl1.ScrollMinY = 0D;
            this.zedGraphControl1.ScrollMinY2 = 0D;
            this.zedGraphControl1.Size = new System.Drawing.Size(748, 254);
            this.zedGraphControl1.TabIndex = 2;
            // 
            // timer_tick
            // 
            this.timer_tick.Tick += new System.EventHandler(this.timer_tick_Tick);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(10, 12);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 4;
            this.button1.Text = "Clear";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // checkBoxRoulis
            // 
            this.checkBoxRoulis.AutoSize = true;
            this.checkBoxRoulis.Location = new System.Drawing.Point(10, 42);
            this.checkBoxRoulis.Name = "checkBoxRoulis";
            this.checkBoxRoulis.Size = new System.Drawing.Size(50, 17);
            this.checkBoxRoulis.TabIndex = 5;
            this.checkBoxRoulis.Text = "roulis";
            this.checkBoxRoulis.UseVisualStyleBackColor = true;
            // 
            // checkBoxtangage
            // 
            this.checkBoxtangage.AutoSize = true;
            this.checkBoxtangage.Location = new System.Drawing.Point(10, 65);
            this.checkBoxtangage.Name = "checkBoxtangage";
            this.checkBoxtangage.Size = new System.Drawing.Size(65, 17);
            this.checkBoxtangage.TabIndex = 5;
            this.checkBoxtangage.Text = "tangage";
            this.checkBoxtangage.UseVisualStyleBackColor = true;
            // 
            // checkBoxlacet
            // 
            this.checkBoxlacet.AutoSize = true;
            this.checkBoxlacet.Location = new System.Drawing.Point(10, 88);
            this.checkBoxlacet.Name = "checkBoxlacet";
            this.checkBoxlacet.Size = new System.Drawing.Size(49, 17);
            this.checkBoxlacet.TabIndex = 5;
            this.checkBoxlacet.Text = "lacet";
            this.checkBoxlacet.UseVisualStyleBackColor = true;
            this.checkBoxlacet.CheckedChanged += new System.EventHandler(this.checkBoxlacet_CheckedChanged);
            // 
            // checkBoxpidroulis
            // 
            this.checkBoxpidroulis.AutoSize = true;
            this.checkBoxpidroulis.Location = new System.Drawing.Point(10, 157);
            this.checkBoxpidroulis.Name = "checkBoxpidroulis";
            this.checkBoxpidroulis.Size = new System.Drawing.Size(67, 17);
            this.checkBoxpidroulis.TabIndex = 5;
            this.checkBoxpidroulis.Text = "pid roulis";
            this.checkBoxpidroulis.UseVisualStyleBackColor = true;
            // 
            // checkBoxpidtangage
            // 
            this.checkBoxpidtangage.AutoSize = true;
            this.checkBoxpidtangage.Location = new System.Drawing.Point(10, 180);
            this.checkBoxpidtangage.Name = "checkBoxpidtangage";
            this.checkBoxpidtangage.Size = new System.Drawing.Size(82, 17);
            this.checkBoxpidtangage.TabIndex = 5;
            this.checkBoxpidtangage.Text = "pid tangage";
            this.checkBoxpidtangage.UseVisualStyleBackColor = true;
            // 
            // checkBoxaltitude
            // 
            this.checkBoxaltitude.AutoSize = true;
            this.checkBoxaltitude.Location = new System.Drawing.Point(10, 134);
            this.checkBoxaltitude.Name = "checkBoxaltitude";
            this.checkBoxaltitude.Size = new System.Drawing.Size(60, 17);
            this.checkBoxaltitude.TabIndex = 5;
            this.checkBoxaltitude.Text = "altitude";
            this.checkBoxaltitude.UseVisualStyleBackColor = true;
            // 
            // checkBoxpidlacet
            // 
            this.checkBoxpidlacet.AutoSize = true;
            this.checkBoxpidlacet.Location = new System.Drawing.Point(10, 203);
            this.checkBoxpidlacet.Name = "checkBoxpidlacet";
            this.checkBoxpidlacet.Size = new System.Drawing.Size(66, 17);
            this.checkBoxpidlacet.TabIndex = 5;
            this.checkBoxpidlacet.Text = "pid lacet";
            this.checkBoxpidlacet.UseVisualStyleBackColor = true;
            // 
            // checkBoxpression
            // 
            this.checkBoxpression.AutoSize = true;
            this.checkBoxpression.Location = new System.Drawing.Point(10, 226);
            this.checkBoxpression.Name = "checkBoxpression";
            this.checkBoxpression.Size = new System.Drawing.Size(65, 17);
            this.checkBoxpression.TabIndex = 11;
            this.checkBoxpression.Text = "pression";
            this.checkBoxpression.UseVisualStyleBackColor = true;
            // 
            // checkBoxtemperature
            // 
            this.checkBoxtemperature.AutoSize = true;
            this.checkBoxtemperature.Location = new System.Drawing.Point(10, 249);
            this.checkBoxtemperature.Name = "checkBoxtemperature";
            this.checkBoxtemperature.Size = new System.Drawing.Size(82, 17);
            this.checkBoxtemperature.TabIndex = 10;
            this.checkBoxtemperature.Text = "temperature";
            this.checkBoxtemperature.UseVisualStyleBackColor = true;
            // 
            // checkBoxnord
            // 
            this.checkBoxnord.AutoSize = true;
            this.checkBoxnord.Location = new System.Drawing.Point(10, 111);
            this.checkBoxnord.Name = "checkBoxnord";
            this.checkBoxnord.Size = new System.Drawing.Size(47, 17);
            this.checkBoxnord.TabIndex = 12;
            this.checkBoxnord.Text = "nord";
            this.checkBoxnord.UseVisualStyleBackColor = true;
            // 
            // FormGraph
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(858, 272);
            this.Controls.Add(this.checkBoxnord);
            this.Controls.Add(this.checkBoxpression);
            this.Controls.Add(this.checkBoxtemperature);
            this.Controls.Add(this.checkBoxpidlacet);
            this.Controls.Add(this.checkBoxpidtangage);
            this.Controls.Add(this.checkBoxpidroulis);
            this.Controls.Add(this.checkBoxaltitude);
            this.Controls.Add(this.checkBoxlacet);
            this.Controls.Add(this.checkBoxtangage);
            this.Controls.Add(this.checkBoxRoulis);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.zedGraphControl1);
            this.Name = "FormGraph";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.Text = "Graph";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormGraph_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.IO.Ports.SerialPort serialPort1;
        private ZedGraph.ZedGraphControl zedGraphControl1;
        private System.Windows.Forms.Timer timer_tick;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.CheckBox checkBoxRoulis;
        private System.Windows.Forms.CheckBox checkBoxtangage;
        private System.Windows.Forms.CheckBox checkBoxlacet;
        private System.Windows.Forms.CheckBox checkBoxpidroulis;
        private System.Windows.Forms.CheckBox checkBoxpidtangage;
        private System.Windows.Forms.CheckBox checkBoxaltitude;
        private System.Windows.Forms.CheckBox checkBoxpidlacet;
        private System.Windows.Forms.CheckBox checkBoxpression;
        private System.Windows.Forms.CheckBox checkBoxtemperature;
        private System.Windows.Forms.CheckBox checkBoxnord;

    }
}

