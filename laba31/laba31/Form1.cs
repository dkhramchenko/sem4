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
            richTextBox1.Text = String.Format("Задание №7: проверка деревьев на строгость:\n" +
                "Первое дерево: {0}; Второе дерево: {1};" +
                " Третье дерево: {2};", t1.Strict(), t2.Strict(), t3.Strict());
        }
    }
}
