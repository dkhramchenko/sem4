using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace laba3
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            BinaryTree b = new BinaryTree();
            List<int> l = new List<int> { 2, 1, 3};
            b.GenerateFromList(l);
            richTextBox1.Text = b.Root.Data.ToString() + b.Root.Left.Data.ToString() +
                b.Root.Right.Data.ToString();
        }
    }
}
