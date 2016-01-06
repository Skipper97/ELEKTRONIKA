using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Threading;
using System.IO.Ports;

namespace bitmaptoarray
{
    public partial class Form1 : Form
    {
        int selectedFormat = -1;
        Image picture;
        Bitmap bitmap;

        public Form1()
        {
            InitializeComponent();
            lb_format.SelectedIndex = 0;
        }


        private void btn_loadimage_Click(object sender, EventArgs e)
        {
            try
            {
                OpenFileDialog open = new OpenFileDialog();

                open.Filter = "Image Files(*.jpg; *.jpeg; *.gif; *.bmp)|*.jpg; *.jpeg; *.gif; *.bmp";

                if (open.ShowDialog() == DialogResult.OK)
                {
                    picture = new Bitmap(open.FileName);

                    int NewWidth = picture.Width;

                    // Prevent using images internal thumbnail
                    picture.RotateFlip(System.Drawing.RotateFlipType.Rotate180FlipNone);
                    picture.RotateFlip(System.Drawing.RotateFlipType.Rotate180FlipNone);

                    if (picture.Width > pictureBox1.Width)
                    {
                        NewWidth = pictureBox1.Width;
                    }

                    int NewHeight = Convert.ToInt32((double)picture.Height * ((double)NewWidth / (double)picture.Width));

                    if (NewHeight > pictureBox1.Height)
                    {
                    // Resize with height instead
                        NewWidth = picture.Width * pictureBox1.Height / picture.Height;
                        NewHeight = pictureBox1.Height;
                    }
                     
                    pictureBox1.Image = picture.GetThumbnailImage(NewWidth, NewHeight, null, IntPtr.Zero);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Failed loading image. Exeption: " + ex.ToString());
            }
        }

        public static byte[] ImageToByte(Image img)
        {
            byte[] byteArray = new byte[0];
            using (MemoryStream stream = new MemoryStream())
            {
                img.Save(stream, System.Drawing.Imaging.ImageFormat.Bmp);
                stream.Close();

                byteArray = stream.ToArray();
            }
            return byteArray;
        }

        private void btn_convert_Click_1(object sender, EventArgs e)
        {
            Thread thread = new Thread(new ThreadStart(WorkThreadFunction));
            thread.Start();
        }

        public void WorkThreadFunction()
        {
            
            try
            {
                
                // create a writer and open the file
                TextWriter tw = new StreamWriter("output_array.txt");

                int itemcounter = 0; // used to count the items to create a new line every x amount of array items
                progressBar1.Invoke(new ProgresMaximumCallback(this.ProgresMaximum), new object[] { picture.Height.ToString() }); // used to update the progres bar
                for (int y = 0; y < picture.Height; y++)
                {
                    for (int x = 0; x < picture.Width; x++)
                    {
                        string finalbinairy = ""; // the final binairy string
                        double temp;
                        bitmap = new Bitmap(picture);
                        Color color = bitmap.GetPixel(x, y); // get the pixal data

                        string tempbinairy = ""; // the binairy strin for the R value of this pixel
                        temp = color.R; 
                        temp = Math.Round(temp / 255 * 31); // convert to 0 to 31 range
                        int roundedtemp = Convert.ToInt32(temp); // round it to an int
                        tempbinairy += Convert.ToString(roundedtemp, 2); // convert to binairy
                        while (tempbinairy.Length < 5) // add zero's to unsure proper length
                        {
                            tempbinairy = "0" + tempbinairy;
                        }
                        finalbinairy += tempbinairy; // add the binairy color data to the final binairy number

                        // repeat for green
                        tempbinairy = "";
                        temp = color.G;
                        temp = Math.Round(temp / 255 * 63); // green has a 0 to 63 range, since green is 6, not 5 bits
                        roundedtemp = Convert.ToInt32(temp);
                        tempbinairy += Convert.ToString(roundedtemp, 2);
                        while (tempbinairy.Length < 6)
                        {
                            tempbinairy = "0" + tempbinairy;
                        }
                        finalbinairy += tempbinairy;

                        // reapeat for blue
                        tempbinairy = "";
                        temp = color.B;
                        temp = Math.Round(temp / 255 * 31);
                        roundedtemp = Convert.ToInt32(temp);
                        tempbinairy += Convert.ToString(roundedtemp, 2);
                        while (tempbinairy.Length < 5)
                        {
                            tempbinairy = "0" + tempbinairy;
                        }
                        finalbinairy += tempbinairy;

                        string string1 = ""; 
                        string string2 = "";

                        for (int i = 0; i < 8; i++)
                        {
                            string1 += finalbinairy[i];
                            string2 += finalbinairy[i+8];
                        }

                        if (selectedFormat == 0)
                        {
                            string1 = String.Format("{0:X}", Convert.ToInt32(string1, 2));
                            while (string1.Length < 2)
                            {
                                string1 = "0" + string1;
                            }

                            string2 = String.Format("{0:X}", Convert.ToInt32(string2, 2));
                            while (string2.Length < 2)
                            {
                                string2 = "0" + string2;   
                            }
                            // write a line of text to the file
                            tw.Write("0x" + string1 + string2 + ",");
                        }

                        else if (selectedFormat == 1)
                        {
                            string1 = String.Format("{0:X}", Convert.ToInt32(string1, 2));
                            while (string1.Length < 2)
                            {
                                string1 = "0" + string1;
                            }

                            string2 = String.Format("{0:X}", Convert.ToInt32(string2, 2));
                            while (string2.Length < 2)
                            {
                                string2 = "0" + string2;
                            }
                            // write a line of text to the file
                            tw.Write("0x" + string1 + ",0x" + string2 + ",");
                        }

                        else if (selectedFormat == 2)
                        {
                            string1 = Convert.ToInt32(string1, 2).ToString();
                            while (string1.Length < 2)
                            {
                                string1 = "0" + string1;
                            }

                            string2 = Convert.ToInt32(string2, 2).ToString();
                            while (string2.Length < 2)
                            {
                                string2 = "0" + string2;
                            }
                            // write a line of text to the file
                            tw.Write(string1 + string2 + ",");
                        }

                        else if (selectedFormat == 3)
                        {
                            string1 = Convert.ToInt32(string1, 2).ToString();
                            while (string1.Length < 2)
                            {
                                string1 = "0" + string1;
                            }

                            string2 = Convert.ToInt32(string2, 2).ToString();
                            while (string2.Length < 2)
                            {
                                string2 = "0" + string2;
                            }
                            // write a line of text to the file
                            tw.Write(string1 + "," + string2 + ",");
                        }

                        

                        progressBar1.Invoke(new ProgresValueCallback(this.ProgresValue), new object[] { (y + 1).ToString() });
                        itemcounter++;
                        if(itemcounter == 20)
                        {
                            tw.WriteLine("");
                            itemcounter = 0;
                        }
                    }
                }
                // close the stream
                tw.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }


        private void ProgresMaximum(string text)
        {
            progressBar1.Maximum = Convert.ToInt32(text);
        }

        private void ProgresValue(string text)
        {
            progressBar1.Value = Convert.ToInt32(text);
        }

        public delegate void ProgresMaximumCallback(string text);
        public delegate void ProgresValueCallback(string text);


        private void lb_format_SelectedIndexChanged(object sender, EventArgs e)
        {
            selectedFormat = lb_format.SelectedIndex;
        }

    }
}
