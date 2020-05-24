using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba4
{
    // класс дерева
    public class Tree
    {
        // конструктор
        public Tree(Node root = null)
        {
            this.root = root;
        }

        // метод возвращает высоту дерева
        public int Height()
        {
            if (root == null)
            {
                return 0;
            }

            return root.Height();
        }

        // метод устанавливает уровни и позиции
        public void setLevels()
        {
            if (this.root == null)
            {
                return;
            }

            this.root.level = 0;
            this.root.position = 0;

            if (this.root.left != null)
            {
                this.root.left.setLevels();
            }

            if (this.root.right != null)
            {
                this.root.right.setLevels();
            }
        }

        // метод возвращает массив уровня
        public Node[] GetLevel(int level)
        {
            int size = Convert.ToInt32(Math.Pow(2, level));
            Node[] levels = new Node[size];

            if (level == 0)
            {
                levels[0] = this.root;
                return levels;
            }

            this.root.GetLevel(level, ref levels);

            return levels;
        }

        // метод возвращает самый правый лист последнего уровня
        public Node RightSonToReduce()
        {
            Node rightSonToReduce = new Node();
            Node[] lastLevel = this.GetLevel(this.Height() - 1);
            for (int i = lastLevel.Length - 1; i >= 0; --i)
            {
                if (lastLevel[i] != null)
                {
                    rightSonToReduce = lastLevel[i];
                    break;
                }
            }

            return rightSonToReduce;
        }

        // метод возвращает родителя для перемещения
        public Node DestinationParent()
        {
            Node destinationParent = new Node();
            for (int i = this.Height() - 3; i >= 0; ++i)
            {
                bool exit = false;
                Node[] destinationLevel = this.GetLevel(i);
                for (int j = 0; j < destinationLevel.Length; ++j)
                {
                    if (destinationLevel[j] != null && destinationLevel[j].left == null & destinationLevel[j].right == null)
                    {
                        destinationParent = destinationLevel[j];
                        exit = true;
                        break;
                    }
                }
                if (exit)
                {
                    break;
                }
            }

            return destinationParent;
        }

        // метод перемещает последний лист
        public void ReduceNode()
        {
            Node rightSonToReduce = this.RightSonToReduce();
            Node leftSonToReduce = rightSonToReduce.parent.left;
            Node parentToReduce = rightSonToReduce.parent;

            Node destinationParent = this.DestinationParent();

            destinationParent.left = new Node(letter: destinationParent.letter, code: destinationParent.code + "0",
                level: destinationParent.level + 1, position: 2 * destinationParent.position, parent: destinationParent, left: null, right: null);
            destinationParent.right = new Node(letter: leftSonToReduce.letter, code: destinationParent.code + "1",
                level: destinationParent.level + 1, position: 2 * destinationParent.position + 1, parent: destinationParent, left: null, right: null);
            destinationParent.letter = 'x';

            parentToReduce.letter = rightSonToReduce.letter;
            parentToReduce.left = null;
            parentToReduce.right = null;
        }

        // метод перемещает нижний уровень
        public void ReduceLevel()
        {
            int height = this.Height();
            while (this.Height() == height)
            {
                this.ReduceNode();
            }
        }

        // метод возвращает строковое представление дерева
        public override string ToString()
        {
            string s = "";
            int amountOfSpaces = 0;
            int k = 0;

            for (int i = this.Height() - 1; i >= 0; --i)
            {
                int tab = 2 * amountOfSpaces + 1;
                string symbol1 = " ";
                if (this.GetLevel(i)[0] != null)
                {
                    symbol1 = this.GetLevel(i)[0].ToString();
                }
                string si = new string(' ', amountOfSpaces) + symbol1;
                for (int j = 1; j < this.GetLevel(i).Length; ++j)
                {
                    string symbol = " ";
                    if (this.GetLevel(i)[j] != null)
                    {
                        symbol = this.GetLevel(i)[j].ToString();
                    }
                    si += new string(' ', tab) + symbol;
                }
                si += new string(' ', amountOfSpaces);
                si += "\n\n";
                s = si + s;
                amountOfSpaces += Convert.ToInt32(Math.Pow(2, k));
                ++k;
            }

            return s;
        }

        // метод заполняет таблицу кодовых слов
        public void CodingTable(ref Dictionary<char, string> codingTable)
        {
            root.CodingTable(ref codingTable);
        }

        public Node root;
    }
}
