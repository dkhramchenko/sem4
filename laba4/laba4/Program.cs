using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laba4
{
    // класс узла
    public class Node
    {
        // конструктор
        public Node(char letter = 'x', int frequency = 0)
        {
            this.letter = letter;
            this.frequency = frequency;
            this.code = "";
            this.level = 0;
            this.left = null;
            this.right = null;
            this.parent = null;
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

        // метод расставляет уровни
        public void setLevels()
        {
            this.level = this.parent.level + 1;

            if (left != null)
            {
                left.setLevels();
            }

            if (right != null)
            {
                right.setLevels();
            }
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

        // метод возвращает список вершин уровня
        public void Level(int i, ref List<Node> level)
        {
            if (this.level == i)
            {
                level.Add(this);
                return;
            }

            if (left != null && right == null)
            {
                left.Level(i, ref level);
                return;
            }

            if (left == null && right != null)
            {
                right.Level(i, ref level);
                return;
            }

            if (left != null && right != null)
            {
                left.Level(i, ref level);
                right.Level(i, ref level);
                return;
            }

            return;
        }

        // поля
        public char letter;
        public int frequency;
        public string code;
        public int level;
        public Node left;
        public Node right;
        public Node parent;
    }
    // класс узла
    public class Tree
    {
        // конструктор
        public Tree(Node root = null)
        {
            this.root = root;
        }

        public void CodingTable(ref Dictionary<char, string> codingTable)
        {
            root.CodingTable(ref codingTable);
        }

        public void setLevels()
        {
            if (root != null)
            {
                root.level = 1;
                root.left.setLevels();
                root.right.setLevels();
            }
        }

        public int Height()
        {
            if (root == null)
            {
                return 0;
            }
            return root.Height();
        }

        public List<Node> Level(int i)
        {
            if (root == null)
            {
                return null;
            }

            List<Node> level = new List<Node>();
            root.Level(i, ref level);
            return level;
        }


        public void replaceLastNode()
        {
            int destinationLevel = 0;
            for (int i = Height() - 1; i > 0; --i)
            {
                if (Level(i).Count < Convert.ToInt32(Math.Pow(2, i - 1)))
                {
                    destinationLevel = i;
                }
            }

            List<Node> l = new List<Node>();
            int k = 0;
            l = Level(destinationLevel - 1);
            for (int i = 0; i < l.Count; ++i)
            {
                if (l[i].left == null && l[i].right == null)
                {
                    k = i;
                    break;
                }
            }

            Node ln = l[k];
            Node rn = ln.parent.right;

            ln.left = new Node(ln.letter, ln.frequency);
            ln.left.level = ln.level + 1;
            ln.left.code = ln.code + "0";
            ln.left.parent = ln;

            Node R = Level(Height()).Last();
            ln.right = new Node(R.parent.letter, R.parent.frequency);
            ln.right.level = ln.level + 1;
            ln.right.code = ln.code + "1";
            ln.right.parent = ln;

            rn.left = new Node(rn.letter, rn.frequency);
            rn.left.code = rn.code + "0";
            rn.left.parent = rn;
            rn.left.level = rn.level + 1;

            rn.right = new Node(R.parent.left.letter, R.parent.left.frequency);
            rn.right.code = rn.code + "1";
            rn.right.level = rn.level + 1;
            rn.right.parent = rn;

            R.parent.letter = R.letter;
            R.parent.frequency = R.frequency;
            Node temp = R.parent;
            temp.left = null;
            temp.right = null;
        }

        public void decreaseCodes()
        {
            
        }

        public Node root;
    }

    class Program
    {
        // метод для сравнения листов дерева
        static int Comp(Node n1, Node n2)
        {
            if (n1.frequency == n2.frequency)
            {
                return 0;
            }

            if (n1.frequency > n2.frequency)
            {
                return 1;
            }

            return -1;
        }

        // основной алгоритм
        static void Main(string[] args)
        {
            // записываем книгу в строку
            FileStream inputFile = new FileStream("originalBook.txt", FileMode.Open);
            StreamReader bookInput = new StreamReader(inputFile, Encoding.Default);
            string originalBook = bookInput.ReadToEnd();
            bookInput.Close();
            inputFile.Close();

            // создаём словарь с частотами символов
            Dictionary<char, int> dictionary = new Dictionary<char, int>();
            foreach (var symbol in originalBook)
            {
                if (dictionary.ContainsKey(symbol))
                {
                    ++dictionary[symbol];
                }
                else
                {
                    dictionary.Add(symbol, 1);
                }
            }

            // выводим таблицу частот и вероятности
            using (StreamWriter probabilityAndFrequencyTable = new StreamWriter(File.Open("frequencyAndProbability.txt", FileMode.Create)))
            {
                var sortedDictionary = new SortedDictionary<char, int>(dictionary);
                foreach (var el in sortedDictionary)
                {
                    string symbol = el.Key.ToString();
                    string frequency = el.Value.ToString();
                    double f = Convert.ToDouble(el.Value);
                    double p = f / originalBook.Length;
                    string probability = p.ToString();

                    probabilityAndFrequencyTable.WriteLine(String.Format("symbol = {0}; frequency = {1};" +
                        " probability = {2}", symbol, frequency, probability));
                }
            }

            // создаём список листов дерева
            List<Node> queue = new List<Node>();
            foreach (var el in dictionary)
            {
                Node node = new Node(el.Key, el.Value);
                queue.Add(node);
            }

            // строим дерево Хаффмана
            queue.Sort((n1, n2) => Comp(n1, n2));
            while (queue.Count != 1)
            {
                Node l = queue[0];
                Node r = queue[1];
                queue.RemoveAt(0);
                queue.RemoveAt(0);
                Node node = new Node('x', l.frequency + r.frequency);
                node.left = l;
                node.right = r;
                node.left.parent = node;
                node.right.parent = node;
                queue.Add(node);
                queue.Sort((n1, n2) => Comp(n1, n2));
            }
            Tree HaffMannTree = new Tree(queue[0]);

            // создаём словарь кодов символов
            Dictionary<char, string> codingTable = new Dictionary<char, string>();
            HaffMannTree.CodingTable(ref codingTable);

            // выводим таблицу частот и вероятности
            using (StreamWriter table1 = new StreamWriter(File.Open("table1.txt", FileMode.Create)))
            {
                var sortedDictionary = new SortedDictionary<char, int>(dictionary);
                foreach (var el in sortedDictionary)
                {
                    string symbol = el.Key.ToString();
                    string frequency = el.Value.ToString();
                    double f = Convert.ToDouble(el.Value);
                    double p = f / originalBook.Length;
                    string probability = p.ToString();
                    string code = codingTable[el.Key];

                    table1.WriteLine(String.Format("symbol = {0}; frequency = {1};" +
                        " probability = {2}; code = {3}; codeLength = {4}",
                        symbol, frequency, probability, code, code.Length));
                }
            }

            //foreach (var el in codingTable)
            //{
            //    Console.WriteLine(String.Format("symbol = {0}; code = {1}", el.Key, el.Value));
            //}

            // кодируем книгу
            using (StreamWriter encodedbook = new StreamWriter(File.Open("encodedBook.txt", FileMode.Create)))
            {
                foreach (var symbol in originalBook)
                {
                    encodedbook.Write(codingTable[symbol]);
                }
            }

            // раскодируем книгу
            FileStream fileToDecodeInput = new FileStream("encodedBook.txt", FileMode.Open);
            StreamReader bookToDecodeInput = new StreamReader(fileToDecodeInput, Encoding.Default);
            string bookToDecode = bookToDecodeInput.ReadToEnd();
            bookToDecodeInput.Close();
            fileToDecodeInput.Close();
            using (StreamWriter decodedBookOutput = new StreamWriter(File.Open("decodedBook.txt", FileMode.Create)))
            {
                for (int i = 0; i < bookToDecode.Length; ++i)
                {
                    Node temp = HaffMannTree.root;
                    while (temp.left != null || temp.right != null)
                    {
                        if (bookToDecode[i] == '0')
                        {
                            temp = temp.left;
                        }
                        if (bookToDecode[i] == '1')
                        {
                            temp = temp.right;
                        }
                        ++i;
                    }
                    decodedBookOutput.Write(temp.letter);
                    --i;
                }
            }

            // 

            Console.ReadKey();
        }
    }
}
