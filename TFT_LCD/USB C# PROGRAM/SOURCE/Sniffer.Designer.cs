namespace UsbApp
{
    partial class Sniffer
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
            this.components = new System.ComponentModel.Container();
            this.lb_recieved = new System.Windows.Forms.Label();
            this.btn_send = new System.Windows.Forms.Button();
            this.tb_send = new System.Windows.Forms.TextBox();
            this.lb_vendor = new System.Windows.Forms.Label();
            this.btn_ok = new System.Windows.Forms.Button();
            this.lb_product = new System.Windows.Forms.Label();
            this.lb_senddata = new System.Windows.Forms.Label();
            this.lb_messages = new System.Windows.Forms.Label();
            this.tb_vendor = new System.Windows.Forms.TextBox();
            this.tb_product = new System.Windows.Forms.TextBox();
            this.gb_filter = new System.Windows.Forms.GroupBox();
            this.lb_message = new System.Windows.Forms.ListBox();
            this.gb_details = new System.Windows.Forms.GroupBox();
            this.lb_read = new System.Windows.Forms.ListBox();
            this.btn_sendpicture = new System.Windows.Forms.Button();
            this.num_width = new System.Windows.Forms.NumericUpDown();
            this.num_height = new System.Windows.Forms.NumericUpDown();
            this.usb = new UsbLibrary.UsbHidPort(this.components);
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.num_xpos = new System.Windows.Forms.NumericUpDown();
            this.num_ypos = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.num_delay = new System.Windows.Forms.NumericUpDown();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.gb_filter.SuspendLayout();
            this.gb_details.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.num_width)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_height)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_xpos)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_ypos)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_delay)).BeginInit();
            this.SuspendLayout();
            // 
            // lb_recieved
            // 
            this.lb_recieved.AutoSize = true;
            this.lb_recieved.Location = new System.Drawing.Point(229, 16);
            this.lb_recieved.Name = "lb_recieved";
            this.lb_recieved.Size = new System.Drawing.Size(82, 13);
            this.lb_recieved.TabIndex = 4;
            this.lb_recieved.Text = "Recieved Data:";
            // 
            // btn_send
            // 
            this.btn_send.Location = new System.Drawing.Point(364, 263);
            this.btn_send.Name = "btn_send";
            this.btn_send.Size = new System.Drawing.Size(48, 23);
            this.btn_send.TabIndex = 3;
            this.btn_send.Text = "Send";
            this.btn_send.UseVisualStyleBackColor = true;
            this.btn_send.Click += new System.EventHandler(this.btn_send_Click);
            // 
            // tb_send
            // 
            this.tb_send.Location = new System.Drawing.Point(229, 263);
            this.tb_send.Name = "tb_send";
            this.tb_send.Size = new System.Drawing.Size(132, 20);
            this.tb_send.TabIndex = 2;
            // 
            // lb_vendor
            // 
            this.lb_vendor.AutoSize = true;
            this.lb_vendor.Location = new System.Drawing.Point(9, 22);
            this.lb_vendor.Name = "lb_vendor";
            this.lb_vendor.Size = new System.Drawing.Size(95, 13);
            this.lb_vendor.TabIndex = 5;
            this.lb_vendor.Text = "Device Vendor ID:";
            // 
            // btn_ok
            // 
            this.btn_ok.Location = new System.Drawing.Point(322, 43);
            this.btn_ok.Name = "btn_ok";
            this.btn_ok.Size = new System.Drawing.Size(75, 23);
            this.btn_ok.TabIndex = 7;
            this.btn_ok.Text = "OK";
            this.btn_ok.UseVisualStyleBackColor = true;
            this.btn_ok.Click += new System.EventHandler(this.btn_ok_Click);
            // 
            // lb_product
            // 
            this.lb_product.AutoSize = true;
            this.lb_product.Location = new System.Drawing.Point(9, 48);
            this.lb_product.Name = "lb_product";
            this.lb_product.Size = new System.Drawing.Size(98, 13);
            this.lb_product.TabIndex = 6;
            this.lb_product.Text = "Device Product ID:";
            // 
            // lb_senddata
            // 
            this.lb_senddata.AutoSize = true;
            this.lb_senddata.Location = new System.Drawing.Point(229, 247);
            this.lb_senddata.Name = "lb_senddata";
            this.lb_senddata.Size = new System.Drawing.Size(61, 13);
            this.lb_senddata.TabIndex = 5;
            this.lb_senddata.Text = "Send Data:";
            // 
            // lb_messages
            // 
            this.lb_messages.AutoSize = true;
            this.lb_messages.Location = new System.Drawing.Point(8, 16);
            this.lb_messages.Name = "lb_messages";
            this.lb_messages.Size = new System.Drawing.Size(80, 13);
            this.lb_messages.TabIndex = 7;
            this.lb_messages.Text = "Usb Messages:";
            // 
            // tb_vendor
            // 
            this.tb_vendor.Location = new System.Drawing.Point(114, 19);
            this.tb_vendor.Name = "tb_vendor";
            this.tb_vendor.Size = new System.Drawing.Size(189, 20);
            this.tb_vendor.TabIndex = 1;
            this.tb_vendor.Text = "1234";
            // 
            // tb_product
            // 
            this.tb_product.Location = new System.Drawing.Point(114, 45);
            this.tb_product.Name = "tb_product";
            this.tb_product.Size = new System.Drawing.Size(189, 20);
            this.tb_product.TabIndex = 2;
            this.tb_product.Text = "0001";
            // 
            // gb_filter
            // 
            this.gb_filter.Controls.Add(this.btn_ok);
            this.gb_filter.Controls.Add(this.lb_product);
            this.gb_filter.Controls.Add(this.lb_vendor);
            this.gb_filter.Controls.Add(this.tb_vendor);
            this.gb_filter.Controls.Add(this.tb_product);
            this.gb_filter.ForeColor = System.Drawing.Color.White;
            this.gb_filter.Location = new System.Drawing.Point(12, 12);
            this.gb_filter.Name = "gb_filter";
            this.gb_filter.Size = new System.Drawing.Size(428, 80);
            this.gb_filter.TabIndex = 5;
            this.gb_filter.TabStop = false;
            this.gb_filter.Text = "Filter for Device:";
            // 
            // lb_message
            // 
            this.lb_message.FormattingEnabled = true;
            this.lb_message.Location = new System.Drawing.Point(11, 32);
            this.lb_message.Name = "lb_message";
            this.lb_message.Size = new System.Drawing.Size(212, 251);
            this.lb_message.TabIndex = 6;
            // 
            // gb_details
            // 
            this.gb_details.Controls.Add(this.lb_read);
            this.gb_details.Controls.Add(this.lb_messages);
            this.gb_details.Controls.Add(this.lb_message);
            this.gb_details.Controls.Add(this.lb_senddata);
            this.gb_details.Controls.Add(this.lb_recieved);
            this.gb_details.Controls.Add(this.btn_send);
            this.gb_details.Controls.Add(this.tb_send);
            this.gb_details.ForeColor = System.Drawing.Color.White;
            this.gb_details.Location = new System.Drawing.Point(12, 98);
            this.gb_details.Name = "gb_details";
            this.gb_details.Size = new System.Drawing.Size(428, 291);
            this.gb_details.TabIndex = 6;
            this.gb_details.TabStop = false;
            this.gb_details.Text = "Device Details:";
            // 
            // lb_read
            // 
            this.lb_read.FormattingEnabled = true;
            this.lb_read.Location = new System.Drawing.Point(232, 32);
            this.lb_read.Name = "lb_read";
            this.lb_read.Size = new System.Drawing.Size(180, 212);
            this.lb_read.TabIndex = 8;
            // 
            // btn_sendpicture
            // 
            this.btn_sendpicture.Location = new System.Drawing.Point(470, 44);
            this.btn_sendpicture.Name = "btn_sendpicture";
            this.btn_sendpicture.Size = new System.Drawing.Size(140, 45);
            this.btn_sendpicture.TabIndex = 7;
            this.btn_sendpicture.Text = "load and send picture";
            this.btn_sendpicture.UseVisualStyleBackColor = true;
            this.btn_sendpicture.Click += new System.EventHandler(this.btn_sendpicture_Click);
            // 
            // num_width
            // 
            this.num_width.Location = new System.Drawing.Point(462, 114);
            this.num_width.Maximum = new decimal(new int[] {
            240,
            0,
            0,
            0});
            this.num_width.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.num_width.Name = "num_width";
            this.num_width.Size = new System.Drawing.Size(66, 20);
            this.num_width.TabIndex = 8;
            this.num_width.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // num_height
            // 
            this.num_height.Location = new System.Drawing.Point(462, 166);
            this.num_height.Maximum = new decimal(new int[] {
            320,
            0,
            0,
            0});
            this.num_height.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.num_height.Name = "num_height";
            this.num_height.Size = new System.Drawing.Size(66, 20);
            this.num_height.TabIndex = 8;
            this.num_height.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // usb
            // 
            this.usb.ProductId = 81;
            this.usb.VendorId = 1105;
            this.usb.OnSpecifiedDeviceRemoved += new System.EventHandler(this.usb_OnSpecifiedDeviceRemoved);
            this.usb.OnDeviceArrived += new System.EventHandler(this.usb_OnDeviceArrived);
            this.usb.OnDeviceRemoved += new System.EventHandler(this.usb_OnDeviceRemoved);
            this.usb.OnDataRecieved += new UsbLibrary.DataRecievedEventHandler(this.usb_OnDataRecieved);
            this.usb.OnSpecifiedDeviceArrived += new System.EventHandler(this.usb_OnSpecifiedDeviceArrived);
            this.usb.OnDataSend += new System.EventHandler(this.usb_OnDataSend);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label1.Location = new System.Drawing.Point(468, 98);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(32, 13);
            this.label1.TabIndex = 9;
            this.label1.Text = "width";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label2.Location = new System.Drawing.Point(468, 150);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(36, 13);
            this.label2.TabIndex = 9;
            this.label2.Text = "height";
            // 
            // num_xpos
            // 
            this.num_xpos.Location = new System.Drawing.Point(552, 114);
            this.num_xpos.Maximum = new decimal(new int[] {
            240,
            0,
            0,
            0});
            this.num_xpos.Name = "num_xpos";
            this.num_xpos.Size = new System.Drawing.Size(66, 20);
            this.num_xpos.TabIndex = 8;
            // 
            // num_ypos
            // 
            this.num_ypos.Location = new System.Drawing.Point(552, 166);
            this.num_ypos.Maximum = new decimal(new int[] {
            320,
            0,
            0,
            0});
            this.num_ypos.Name = "num_ypos";
            this.num_ypos.Size = new System.Drawing.Size(66, 20);
            this.num_ypos.TabIndex = 8;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label3.Location = new System.Drawing.Point(556, 98);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 13);
            this.label3.TabIndex = 9;
            this.label3.Text = "X position";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label4.Location = new System.Drawing.Point(556, 150);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 13);
            this.label4.TabIndex = 9;
            this.label4.Text = "Y position";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.BackColor = System.Drawing.Color.Transparent;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.ForeColor = System.Drawing.Color.Transparent;
            this.label5.Location = new System.Drawing.Point(446, 9);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(214, 16);
            this.label5.TabIndex = 10;
            this.label5.Text = "Connect before sending, press OK!";
            // 
            // num_delay
            // 
            this.num_delay.Location = new System.Drawing.Point(517, 301);
            this.num_delay.Name = "num_delay";
            this.num_delay.Size = new System.Drawing.Size(62, 20);
            this.num_delay.TabIndex = 11;
            this.num_delay.Value = new decimal(new int[] {
            4,
            0,
            0,
            0});
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label6.Location = new System.Drawing.Point(467, 256);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(162, 13);
            this.label6.TabIndex = 12;
            this.label6.Text = "Delay between sending pakages";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label7.Location = new System.Drawing.Point(459, 275);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(177, 13);
            this.label7.TabIndex = 13;
            this.label7.Text = "increase if you get corrupted images";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.label8.Location = new System.Drawing.Point(478, 31);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(121, 13);
            this.label8.TabIndex = 14;
            this.label8.Text = "Use 8 bit int array format";
            // 
            // Sniffer
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Desktop;
            this.ClientSize = new System.Drawing.Size(664, 404);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.num_delay);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.num_ypos);
            this.Controls.Add(this.num_height);
            this.Controls.Add(this.num_xpos);
            this.Controls.Add(this.num_width);
            this.Controls.Add(this.btn_sendpicture);
            this.Controls.Add(this.gb_filter);
            this.Controls.Add(this.gb_details);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "Sniffer";
            this.Text = "Send Picture over USB";
            this.gb_filter.ResumeLayout(false);
            this.gb_filter.PerformLayout();
            this.gb_details.ResumeLayout(false);
            this.gb_details.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.num_width)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_height)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_xpos)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_ypos)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_delay)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lb_recieved;
        private System.Windows.Forms.Button btn_send;
        private System.Windows.Forms.TextBox tb_send;
        private System.Windows.Forms.Label lb_vendor;
        private System.Windows.Forms.Button btn_ok;
        private System.Windows.Forms.Label lb_product;
        private System.Windows.Forms.Label lb_senddata;
        private System.Windows.Forms.Label lb_messages;
        private System.Windows.Forms.TextBox tb_vendor;
        private System.Windows.Forms.TextBox tb_product;
        private System.Windows.Forms.GroupBox gb_filter;
        private System.Windows.Forms.ListBox lb_message;
        private System.Windows.Forms.GroupBox gb_details;
        private UsbLibrary.UsbHidPort usb;
        private System.Windows.Forms.ListBox lb_read;
        private System.Windows.Forms.Button btn_sendpicture;
        private System.Windows.Forms.NumericUpDown num_width;
        private System.Windows.Forms.NumericUpDown num_height;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown num_xpos;
        private System.Windows.Forms.NumericUpDown num_ypos;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.NumericUpDown num_delay;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;

    }
}

