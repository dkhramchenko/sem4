using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba3
{
    public class BinaryTree
    {
        private Node root = null;
        private class Node
        {
            private int count = 0;
            public Node(int data)
            {
                Data = data;
                Left = null;
                Right = null;
            }
            public int Data { get; set; }
            public Node Left { get; set; }
            public Node Right { get; set; }
        }
        public int Height()
        {
            return 0;//Math.Max(this.root.Left.heig)
        }
    }
}
