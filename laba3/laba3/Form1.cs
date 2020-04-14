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
            b.Root = new BinaryTree.Node(1);
            b.Root.Left = new BinaryTree.Node(2);
            b.Root.Right = new BinaryTree.Node(3);
            b.Root.Left.Left = new BinaryTree.Node(4);
            b.Root.Right.Right = new BinaryTree.Node(4);
            richTextBox1.Text = String.Format("Высота = {0}   Баланс = {1} Количество {2} = {3}", b.Height(), b.Balanced(), 5, b.AmountOfValue(5));
        }
    }
}
