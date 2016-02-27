using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace SecureDataStorage
{
    public partial class CreateNew_Form2 : Form
    {
        public CreateNew_Form2()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(@"C:\Project\Batch\vol.bat.lnk");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(@"C:\Project\Batch\attach.bat.lnk");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            try
            {
                string[] str = Directory.GetLogicalDrives();
                Console.WriteLine("Using C# Directory Class ,Available drives are:");
                for (int i = 0; i < str.Length; i++)
                    Console.WriteLine(str[i]);
            }
            catch (IOException ex)
            {
                Console.WriteLine(ex.ToString());
            }
            

        }
    }

    
}
     
        
    




