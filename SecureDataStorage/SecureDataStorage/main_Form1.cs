using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using System.IO;
using System.Security.Cryptography;

using System.Diagnostics;
using System.Management;

namespace SecureDataStorage
{
   
    public partial class main_Form1 : Form
    {
        
        
        public main_Form1()
        {
            InitializeComponent();
            
        }

        
        
        
        private void Form1_Load(object sender, EventArgs e)
        {

        }
        
        

        

        

        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }
        
        

        

        private void button4_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(@"C:\Project\SecureDataStorage\SecureDataStorage\Stuffs\Support\Secure_Password_Manager.exe");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(@"C:\Project\SecureDataStorage\SecureDataStorage\Stuffs\Support\FolderProtection.exe");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(@"C:\Project\SecureDataStorage\SecureDataStorage\Stuffs\Support\secure_file.exe");
        }
        Vol_Info vf = new Vol_Info();
        private void button6_Click(object sender, EventArgs e)
        {
            vf.Show();
            
        }


        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button7_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(@"C:\Project\SecureDataStorage\SecureDataStorage\Stuffs\Batch\mount.bat.lnk");
        }

        private void button8_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(@"C:\Project\SecureDataStorage\SecureDataStorage\Stuffs\Batch\Detach.bat.lnk");
        }

        private void button5_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        
        

       
    }
}
