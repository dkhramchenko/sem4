using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba4
{
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
                Node node = new Node(letter: el.Key, frequency: el.Value);
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
                Node node = new Node(letter: 'x', frequency: l.frequency + r.frequency);
                node.left = l;
                node.right = r;
                node.left.parent = node;
                node.right.parent = node;
                queue.Add(node);
                queue.Sort((n1, n2) => Comp(n1, n2));
            }
            Tree HaffMannTree = new Tree(queue[0]);
            HaffMannTree.setLevels();

            // создаём словарь кодов символов
            Dictionary<char, string> codingTable0 = new Dictionary<char, string>();
            HaffMannTree.CodingTable(ref codingTable0);

            // выводим таблицу частот и вероятности для кода без ограничения на длину
            using (StreamWriter table0 = new StreamWriter(File.Open("table0.txt", FileMode.Create)))
            {
                var sortedDictionary = new SortedDictionary<char, int>(dictionary);
                foreach (var el in sortedDictionary)
                {
                    string symbol = el.Key.ToString();
                    string frequency = el.Value.ToString();
                    double f = Convert.ToDouble(el.Value);
                    double p = f / originalBook.Length;
                    string probability = p.ToString();
                    string code = codingTable0[el.Key];

                    table0.WriteLine(String.Format("symbol = {0}; frequency = {1};" +
                        " probability = {2}; code = {3}; codeLength = {4}",
                        symbol, frequency, probability, code, code.Length));
                }
            }

            //foreach (var el in codingTable)
            //{
            //    Console.WriteLine(String.Format("symbol = {0}; code = {1}", el.Key, el.Value));
            //}

            // кодируем книгу без ограничения на длину кода
            using (StreamWriter encodedbook = new StreamWriter(File.Open("encodedBook0.txt", FileMode.Create)))
            {
                foreach (var symbol in originalBook)
                {
                    encodedbook.Write(codingTable0[symbol]);
                }
            }

            // раскодируем книгу
            FileStream fileToDecodeInput = new FileStream("encodedBook0.txt", FileMode.Open);
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

            // кодируем книгу, уменьшив длину кода на 1
            HaffMannTree.ReduceLevel();
            Dictionary<char, string> codingTable1 = new Dictionary<char, string>();
            HaffMannTree.CodingTable(ref codingTable1);
            using (StreamWriter encodedbook = new StreamWriter(File.Open("encodedBook1.txt", FileMode.Create)))
            {
                foreach (var symbol in originalBook)
                {
                    encodedbook.Write(codingTable1[symbol]);
                }
            }

            // выводим таблицу частот и вероятности, уменьшив максимальную длину кода на 1
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
                    string code = codingTable1[el.Key];

                    table1.WriteLine(String.Format("symbol = {0}; frequency = {1};" +
                        " probability = {2}; code = {3}; codeLength = {4}",
                        symbol, frequency, probability, code, code.Length));
                }
            }

            // кодируем книгу, уменьшив длину кода на 2
            HaffMannTree.ReduceLevel();
            Dictionary<char, string> codingTable2 = new Dictionary<char, string>();
            HaffMannTree.CodingTable(ref codingTable2);
            using (StreamWriter encodedbook = new StreamWriter(File.Open("encodedBook2.txt", FileMode.Create)))
            {
                foreach (var symbol in originalBook)
                {
                    encodedbook.Write(codingTable2[symbol]);
                }
            }

            // выводим таблицу частот и вероятности, уменьшив максимальную длину кода на 2
            using (StreamWriter table2 = new StreamWriter(File.Open("table2.txt", FileMode.Create)))
            {
                var sortedDictionary = new SortedDictionary<char, int>(dictionary);
                foreach (var el in sortedDictionary)
                {
                    string symbol = el.Key.ToString();
                    string frequency = el.Value.ToString();
                    double f = Convert.ToDouble(el.Value);
                    double p = f / originalBook.Length;
                    string probability = p.ToString();
                    string code = codingTable2[el.Key];

                    table2.WriteLine(String.Format("symbol = {0}; frequency = {1};" +
                        " probability = {2}; code = {3}; codeLength = {4}",
                        symbol, frequency, probability, code, code.Length));
                }
            }

            // кодируем книгу, уменьшив длину кода на 3
            HaffMannTree.ReduceLevel();
            Dictionary<char, string> codingTable3 = new Dictionary<char, string>();
            HaffMannTree.CodingTable(ref codingTable3);
            using (StreamWriter encodedbook = new StreamWriter(File.Open("encodedBook3.txt", FileMode.Create)))
            {
                foreach (var symbol in originalBook)
                {
                    encodedbook.Write(codingTable3[symbol]);
                }
            }

            // выводим таблицу частот и вероятности, уменьшив максимальную длину кода на 3
            using (StreamWriter table3 = new StreamWriter(File.Open("table3.txt", FileMode.Create)))
            {
                var sortedDictionary = new SortedDictionary<char, int>(dictionary);
                foreach (var el in sortedDictionary)
                {
                    string symbol = el.Key.ToString();
                    string frequency = el.Value.ToString();
                    double f = Convert.ToDouble(el.Value);
                    double p = f / originalBook.Length;
                    string probability = p.ToString();
                    string code = codingTable3[el.Key];

                    table3.WriteLine(String.Format("symbol = {0}; frequency = {1};" +
                        " probability = {2}; code = {3}; codeLength = {4}",
                        symbol, frequency, probability, code, code.Length));
                }
            }

            Console.ReadKey();
        }
    }
}
