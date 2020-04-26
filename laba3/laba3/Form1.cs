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
            b.Root.Left.Parent = b.Root;
            b.Root.Right = new BinaryTree.Node(3);
            b.Root.Right.Parent = b.Root;
            b.Root.Left.Left = new BinaryTree.Node(4);
            b.Root.Left.Left.Parent = b.Root.Left;
            //b.Root.Right.Right = new BinaryTree.Node(4);
            b.Root.Left.Right = new BinaryTree.Node(4);
            b.Root.Left.Right.Parent = b.Root.Left;
            //b.Root.Right.Left = new BinaryTree.Node(6);
            /*richTextBox1.Text = String.Format("Высота = {0}; Баланс = {1}; Количество {2} = {3}; Количество листьев = {4}; " +
                "Строгое = {5}; Полное = {6}; Самая короткая ветка = {7}",
                b.Height(), b.Balanced(), 4, b.AmountOfValue(4), b.AmountOfLeaves(), b.Strict(), b.Full(), b.ShortestBranch());*/
            richTextBox1.Text = b.ShortestBranch();
            b.Full();
        }
    }
}
