using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba4
{
    // класс узла
    public class Node
    {
        // конструктор
        public Node(char letter = 'x', int frequency = 0, string code = "", int level = 0, int position = 0,
            Node left = null, Node right = null, Node parent = null)
        {
            this.letter = letter;
            this.frequency = frequency;
            this.code = code;
            this.level = level;
            this.position = position;
            this.left = left;
            this.right = right;
            this.parent = right;
        }

        // метод возвращает высоту дерева
        public int Height()
        {
            if (left == null && right == null)
            {
                return 1;
            }

            if (left != null && right == null)
            {
                return 1 + left.Height();
            }

            if (left == null && right != null)
            {
                return 1 + right.Height();
            }

            return Math.Max(left.Height(), right.Height()) + 1;
        }

        // метод расставляет уровни
        public void setLevels()
        {
            this.level = this.parent.level + 1;

            if (this == this.parent.left)
            {
                this.position = 2 * this.parent.position;
            }

            if (this == this.parent.right)
            {
                this.position = 2 * this.parent.position + 1;
            }

            if (this.left != null)
            {
                this.left.setLevels();
            }

            if (this.right != null)
            {
                this.right.setLevels();
            }
        }

        // метод заполняет массив уровня
        public void GetLevel(int level, ref Node[] list)
        {
            if (this.level > level)
            {
                return;
            }

            if (this.level == level)
            {
                int index = -1;
                if (this == this.parent.left)
                {
                    index = 2 * this.parent.position;
                }
                else
                {
                    index = 2 * this.parent.position + 1;
                }
                list[index] = this;
                return;
            }

            if (this.left != null && this.right == null)
            {
                this.left.GetLevel(level, ref list);
                return;
            }

            if (this.left == null && this.right != null)
            {
                this.right.GetLevel(level, ref list);
                return;
            }

            if (this.left != null && this.right != null)
            {
                this.left.GetLevel(level, ref list);
                this.right.GetLevel(level, ref list);
                return;
            }
        }

        // метод заполняет таблицу кодов по дереву
        public void CodingTable(ref Dictionary<char, string> codingTable)
        {
            if (this.parent == null)
            {
                this.code = "";
            }
            else
            {
                if (this.parent.left == this)
                {
                    this.code = this.parent.code + "0";
                }

                if (this.parent.right == this)
                {
                    this.code = this.parent.code + "1";
                }
            }

            if (this.left == null & this.right == null)
            {
                codingTable.Add(this.letter, this.code);
                return;
            }

            if (this.left != null && this.right == null)
            {
                left.CodingTable(ref codingTable);
                return;
            }

            if (this.left == null && this.right != null)
            {
                right.CodingTable(ref codingTable);
                return;
            }

            left.CodingTable(ref codingTable);

            right.CodingTable(ref codingTable);
        }

        // метод возвращает строковое представление дерева
        public override string ToString()
        {
            return this.letter.ToString();
        }

        // поля
        public char letter;
        public int frequency;
        public string code;
        public int level;
        public int position;
        public Node left;
        public Node right;
        public Node parent;
    }
}
