using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace SecureDataStorage
{
    public partial class Vol_Info : Form
    {
        public Vol_Info()
        {
            InitializeComponent();
        }

        private void Vol_Info_Load(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(@"C:\Project\SecureDataStorage\SecureDataStorage\Stuffs\Batch\Create.bat.lnk");
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(@"C:\Project\SecureDataStorage\SecureDataStorage\Stuffs\Batch\vol.bat.lnk");

        }

        private void button3_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
