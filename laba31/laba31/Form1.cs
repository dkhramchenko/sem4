using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace laba31
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // создаём первое дерево
            BinaryTree t1 = new BinaryTree();
            t1.Root = new BinaryTree.Node(1);
            t1.Root.Left = new BinaryTree.Node(2);
            t1.Root.Right = new BinaryTree.Node(3);
            t1.Root.Left.Left = new BinaryTree.Node(4);
            t1.Root.Right.Right = new BinaryTree.Node(5);

            // создаём второе дерево
            BinaryTree t2 = new BinaryTree();
            t2.Root = new BinaryTree.Node(1);
            t2.Root.Left = new BinaryTree.Node(2);
            t2.Root.Right = new BinaryTree.Node(3);
            t2.Root.Left.Left = new BinaryTree.Node(4);
            t2.Root.Left.Right = new BinaryTree.Node(5);
            t2.Root.Right.Right = new BinaryTree.Node(6);
            t2.Root.Right.Left = new BinaryTree.Node(7);

            // создаём третье дерево
            BinaryTree t3 = new BinaryTree();
            t3.Root = new BinaryTree.Node(1);
            t3.Root.Left = new BinaryTree.Node(2);
            t3.Root.Right = new BinaryTree.Node(3);
            t3.Root.Right.Right = new BinaryTree.Node(4);
            t3.Root.Right.Left = new BinaryTree.Node(5);

            // проверяем все три дерева на строгость
            // первое дерево
            string l11 = String.Format("    1    \n");
            string l12 = String.Format("  2   3  \n");
            string l13 = String.Format("4       5\n");
            richTextBox1.Text =  l11 + l12 + l13;
            richTextBox1.Text += String.Format("Строгое = {0}", t1.Strict());

            // второе дерево
            string l21 = String.Format("      1      \n");
            string l22 = String.Format("  2       3  \n");
            string l23 = String.Format("4   5   6   7\n");
            richTextBox2.Text = l21 + l22 + l23;
            richTextBox2.Text += String.Format("Строгое = {0}", t2.Strict());

            // третье дерево
            string l31 = String.Format("     1      \n");
            string l32 = String.Format("  2      3  \n");
            string l33 = String.Format("       4   5\n");
            richTextBox3.Text = l31 + l32 + l33;
            richTextBox3.Text += String.Format("Строгое = {0}", t3.Strict());
        }
    }
}
