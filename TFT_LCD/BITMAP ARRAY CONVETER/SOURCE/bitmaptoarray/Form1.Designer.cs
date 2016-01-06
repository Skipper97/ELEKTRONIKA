namespace bitmaptoarray
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btn_loadimage = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.btn_convert = new System.Windows.Forms.Button();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.lb_format = new System.Windows.Forms.ListBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // btn_loadimage
            // 
            this.btn_loadimage.Location = new System.Drawing.Point(403, 39);
            this.btn_loadimage.Name = "btn_loadimage";
            this.btn_loadimage.Size = new System.Drawing.Size(80, 45);
            this.btn_loadimage.TabIndex = 0;
            this.btn_loadimage.Text = "load image";
            this.btn_loadimage.UseVisualStyleBackColor = true;
            this.btn_loadimage.Click += new System.EventHandler(this.btn_loadimage_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.pictureBox1.Location = new System.Drawing.Point(38, 39);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(320, 471);
            this.pictureBox1.TabIndex = 2;
            this.pictureBox1.TabStop = false;
            // 
            // btn_convert
            // 
            this.btn_convert.Location = new System.Drawing.Point(403, 120);
            this.btn_convert.Name = "btn_convert";
            this.btn_convert.Size = new System.Drawing.Size(80, 44);
            this.btn_convert.TabIndex = 3;
            this.btn_convert.Text = "convert";
            this.btn_convert.UseVisualStyleBackColor = true;
            this.btn_convert.Click += new System.EventHandler(this.btn_convert_Click_1);
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(22, 543);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(471, 21);
            this.progressBar1.TabIndex = 4;
            // 
            // lb_format
            // 
            this.lb_format.FormattingEnabled = true;
            this.lb_format.Items.AddRange(new object[] {
            "0xFFFF,         (16bit hex)",
            "0xFF, 0xFF,   (8bit   hex)",
            "65535,          (16bit dec)",
            "255, 255       (8bit dec)"});
            this.lb_format.Location = new System.Drawing.Point(376, 341);
            this.lb_format.Name = "lb_format";
            this.lb_format.Size = new System.Drawing.Size(126, 56);
            this.lb_format.TabIndex = 6;
            this.lb_format.SelectedIndexChanged += new System.EventHandler(this.lb_format_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(35, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(375, 13);
            this.label1.TabIndex = 7;
            this.label1.Text = "The file will be saved as output_array.txt in the folder where the .exe is locate" +
                "d";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(373, 316);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(75, 13);
            this.label2.TabIndex = 8;
            this.label2.Text = "Select Format:";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(514, 588);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lb_format);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.btn_convert);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.btn_loadimage);
            this.Name = "Form1";
            this.Text = "Bitmap To Array";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btn_loadimage;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button btn_convert;
        private System.Windows.Forms.ProgressBar progressBar1;
        public System.Windows.Forms.ListBox lb_format;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
    }
}

