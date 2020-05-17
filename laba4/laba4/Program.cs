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
        public Node(char letter, int frequency)
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
            root.level = 0;
            root.left.setLevels();
            root.right.setLevels();
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
