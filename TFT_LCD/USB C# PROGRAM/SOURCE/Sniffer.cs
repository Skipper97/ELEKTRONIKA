using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using UsbLibrary;
using System.IO;
using System.Threading;
using System.IO.Ports;

namespace UsbApp
{
    public partial class Sniffer : Form
    {
        public Sniffer()
        {
            InitializeComponent();
        }

        private void usb_OnDeviceArrived(object sender, EventArgs e)
        {
            this.lb_message.Items.Add("Found a Device");
        }

        private void usb_OnDeviceRemoved(object sender, EventArgs e)
        {
            if (InvokeRequired)
            {
                Invoke(new EventHandler(usb_OnDeviceRemoved), new object[] { sender, e });
            }
            else
            {
                this.lb_message.Items.Add("Device was removed");
            }
        }

        private void usb_OnSpecifiedDeviceArrived(object sender, EventArgs e)
        {
            this.lb_message.Items.Add("My device was found");

            //setting string form for sending data
            string text = "";
            for (int i = 0; i < this.usb.SpecifiedDevice.OutputReportLength - 1; i++)
            {
                text += "000 ";
            }
            this.tb_send.Text = text;
        }

        protected override void OnHandleCreated(EventArgs e)
        {
            base.OnHandleCreated(e);
            usb.RegisterHandle(Handle);
        }

        protected override void WndProc(ref Message m)
        {
            usb.ParseMessages(ref m);
            base.WndProc(ref m);	// pass message on to base form
        }

        private void btn_ok_Click(object sender, EventArgs e)
        {
            try
            {
                this.usb.ProductId = Int32.Parse(this.tb_product.Text, System.Globalization.NumberStyles.HexNumber);
                this.usb.VendorId = Int32.Parse(this.tb_vendor.Text, System.Globalization.NumberStyles.HexNumber);
                this.usb.CheckDevicePresent();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void btn_send_Click(object sender, EventArgs e)
        {
            string text = this.tb_send.Text + " ";
            text.Trim();
            string[] arrText = text.Split(' ');
            sendData(arrText);
        }

        private void usb_OnSpecifiedDeviceRemoved(object sender, EventArgs e)
        {
            if (InvokeRequired)
            {
                Invoke(new EventHandler(usb_OnSpecifiedDeviceRemoved), new object[] { sender, e });
            }
            else
            {
                this.lb_message.Items.Add("My device was removed");
            }
        }

        private void usb_OnDataRecieved(object sender, DataRecievedEventArgs args)
        {
            if (InvokeRequired)
            {
                try
                {
                    Invoke(new DataRecievedEventHandler(usb_OnDataRecieved), new object[] { sender, args });
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.ToString());
                }
            }
            else
            {

                string rec_data = "Data: ";
                foreach (byte myData in args.data)
                {
                    if (myData.ToString().Length == 1)
                    {
                        rec_data += "00";
                    }

                    if (myData.ToString().Length == 2)
                    {
                        rec_data += "0";
                    }

                    rec_data += myData.ToString() + " ";
                }

                this.lb_read.Items.Insert(0, rec_data);
            }
        }

        private void usb_OnDataSend(object sender, EventArgs e)
        {
            this.lb_message.Items.Add("Some data was send");
        }

        private void btn_sendpicture_Click(object sender, EventArgs e)
        {
            try
            {
                OpenFileDialog open = new OpenFileDialog();

                open.Filter = "Image Files(*.txt)|*.txt";

                if (open.ShowDialog() == DialogResult.OK) // if user selected ok
                {
                    int width = Convert.ToInt32(num_width.Value); // widht of the image
                    int height = Convert.ToInt32(num_height.Value); // height of the image

                    int xpos = Convert.ToInt32(num_xpos.Value); // x position of the image
                    int ypos = Convert.ToInt32(num_ypos.Value); // y position of the image

                    string[] arrText = new string[65]; // the array of data to be send (64 bytes a time)
                    for (int i = 0; i < 65; i++) // fill the array with zero's
                    {
                        arrText[i] = "000";
                    }

                    // send the dimensions and coordinates
                    arrText[2] = Convert.ToInt32(ConvertToLowAndHigh(width)[0], 2).ToString();
                    arrText[1] = Convert.ToInt32(ConvertToLowAndHigh(width)[1], 2).ToString();
                    arrText[4] = Convert.ToInt32(ConvertToLowAndHigh(height)[0], 2).ToString();
                    arrText[3] = Convert.ToInt32(ConvertToLowAndHigh(height)[1], 2).ToString();

                    arrText[6] = Convert.ToInt32(ConvertToLowAndHigh(xpos)[0], 2).ToString();
                    arrText[5] = Convert.ToInt32(ConvertToLowAndHigh(xpos)[1], 2).ToString();
                    arrText[8] = Convert.ToInt32(ConvertToLowAndHigh(ypos)[0], 2).ToString();
                    arrText[7] = Convert.ToInt32(ConvertToLowAndHigh(ypos)[1], 2).ToString();

                    sendData(arrText);


                    List<string> picture_array = new List<string>(); // a list of the picture array
                    int index = 0;

                    // Create an instance of StreamReader to read from a file.
                    // The using statement also closes the StreamReader.
                    using (StreamReader sr = new StreamReader(open.FileName))
                    {
                        String line;
                        // Read and display lines from the file until the end of
                        // the file is reached.
                        while ((line = sr.ReadLine()) != null)
                        {
                            string[] temp_array = line.Split(',');
                            foreach (string item in temp_array)
                            {
                                if (item != "")
                                {
                                    picture_array.Add(item); // add eacht item of the picture array to the list, execpt if its "", which is no data
                                }
                            }
                        }
                    }

                    index = 1; // index starts at 1 since the first byte is no data (part of the library, I dont know why)
                    foreach (string item in picture_array) // loop through the picture arra
                    {
                        if (index < 65 - 1) // if the index is les then 65, the array of data to be send is not full, so add item of the picture to it
                        {
                            arrText[index] = item;
                            index++;
                        }
                        else // if arrText if full, send the data and reset the index
                        {
                            arrText[index] = item;
                            sendData(arrText);
                            Thread.Sleep(Convert.ToInt32(num_delay.Value)); // sleep for a bit, otherwise the microcontroller won't be able to keep up, and the image will get corrupted
                            index = 1;
                        }
                    }
                    if (index != 1) // if there is data left in arrText, send it
                    {
                        sendData(arrText);
                    }
                }
            }

            
            catch (Exception ex)
            {
                // Let the user know what went wrong.
                MessageBox.Show(ex.ToString());
            }

        }


        private void sendData(string[] arrText) // sends the data to the pic
        {
            try
            {
                byte[] data = new byte[arrText.Length];
                for (int i = 0; i < arrText.Length; i++)
                {
                    if (arrText[i] != "")
                    {
                        int value = Int32.Parse(arrText[i], System.Globalization.NumberStyles.Number);
                        data[i] = (byte)Convert.ToByte(value);
                    }
                }

                if (this.usb.SpecifiedDevice != null)
                {
                    this.usb.SpecifiedDevice.SendData(data);
                }
                else
                {
                    MessageBox.Show("Sorry but your device is not present. Plug it in!! ");
                    throw new System.ArgumentException("Device not found exeption");;
                }

            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public string[] ConvertToLowAndHigh(int integer) // convert an int to a low and high int like string
        {
            string binary = Convert.ToString(integer, 2);
            string low = "";
            string high = "";
            while (binary.Length < 16)
            {
                binary = "0" + binary;
            }
            for (int i = 0; i < 8; i++)
            {
                low += binary[i];
                high += binary[i + 8];
            }
            string[] returnvalue = {low,high};
            return returnvalue;
        }

    }
}