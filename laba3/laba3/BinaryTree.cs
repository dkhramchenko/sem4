using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.ComponentModel;
using System.ComponentModel.Design.Serialization;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace laba3
{
    public class BinaryTree
    {
        // класс узла дерева(сучки или листья)
        public class Node
        {
            // конструктор класса узла
            public Node(int data)
            {
                Data = data;
                Left = null;
                Right = null;
                Parent = null;
            }

            // конструктор класса узла без параметров
            public Node()
            {
                Left = null;
                Right = null;
                Parent = null;
            }

            // свойство для чтения и записи данных узла
            public int Data { get; set; }
            
            // свойство для чтения и записи левого потомка
            public Node Left { get; set; }
            
            // свойство для чтения и записи правого потомка
            public Node Right { get; set; }
            
            // свойство для чтения и записи родителя
            public Node Parent { get; set; }

            // рекурсивный метод вычисляет высоту поддерева
            public int Height()
            {
                // выход из рекурсии. Случай листа(нет потомков)
                if (Left == null && Right == null)
                {
                    return 1;
                }
                // случай сучка(есть только правый потомок)
                if (Left == null && Right != null)
                {
                    return Right.Height() + 1;
                }
                // случай сучка(есть только левый потомок)
                if (Left != null && Right == null)
                {
                    return Left.Height() + 1;
                }
                // случай сучка(есть оба потомка)
                if (Left != null && Right != null)
                {
                    return Math.Max(Left.Height(), Right.Height()) + 1;
                }
                // сюда программа дойти не может, поскольку разобраны всевозможные случаи
                return -1;
            }

            // Задание 1: рекурсивный метод проверяет поддерево на сбалансированность
            public bool Balanced()
            {
                // выход из рекурсии. Случай листа(нет потомков)
                if (Left == null && Right == null)
                {
                    return true;
                }
                // случай сучка(есть только правый потомок)
                if (Left == null && Right != null)
                {
                    return Right.Balanced();
                }
                // случай сучка(есть только левый потомок)
                if (Left != null && Right == null)
                {
                    return Left.Balanced();
                }
                // случай сучка(есть оба потомка)
                if (Left != null && Right != null)
                {
                    return (Left.Height() == Right.Height()) && Left.Balanced() && Right.Balanced();
                }
                // сюда программа дойти не может, поскольку разобраны всевозможные случаи
                return true;
            }

            // Задание 2: рекурсивный метод возвращает количество элементов с заданным значением в поддереве
            public int AmountOfValue(int value)
            {
                // если данное значение есть в рассматриваемой вершине
                int current = 0;
                if (Data == value)
                {
                    ++current;
                }
                // выход из рекурсии. Случай листа(нет потомков)
                if (Left == null && Right == null)
                {
                    return current;
                }
                // случай сучка(есть только правый потомок)
                if (Left != null && Right == null)
                {
                    return current + Left.AmountOfValue(value);
                }
                // случай сучка(есть только левый потомок)
                if (Left == null && Right != null)
                {
                    return current + Right.AmountOfValue(value);
                }
                // случай сучка(есть оба потомка)
                if (Left != null && Right != null)
                {
                    return current + Left.AmountOfValue(value) + Right.AmountOfValue(value);
                }
                // сюда программа дойти не может, поскольку разобраны всевозможные случаи
                return -1;
            }

            // задание 3: рекурсивный метод выозвращает длину самой короткой ветки поддерева
            public int ShortestBranchHeight()
            {
                // выход из рекурсии. Случай листа(нет потомков)
                if (Left == null && Right == null)
                {
                    return 1;
                }
                // случай сучка(есть только правый потомок)
                if (Left == null && Right != null)
                {
                    return Right.ShortestBranchHeight() + 1;
                }
                // случай сучка(есть только левый потомок)
                if (Left != null && Right == null)
                {
                    return Left.ShortestBranchHeight() + 1;
                }
                // случай сучка(есть оба потомка)
                if (Left != null && Right != null)
                {
                    return Math.Min(Left.ShortestBranchHeight(), Right.ShortestBranchHeight()) + 1;
                }
                // сюда программа дойти не может, поскольку разобраны всевозможные случаи
                return -1;
            }

            // рекурсивный метод возвращает лист(конец) самой короткой ветки поддерева
            public Node ShortestBranchLastNode()
            {
                // выход из рекурсии. Случай листа(нет потомков)
                if (Left == null && Right == null)
                {
                    return this;
                }
                // случай сучка(есть только правый потомок)
                if (Left == null && Right != null)
                {
                    return Right.ShortestBranchLastNode();
                }
                // случай сучка(есть только левый потомок)
                if (Left != null && Right == null)
                {
                    return Left.ShortestBranchLastNode();
                }
                // случай сучка(есть оба потомка)
                if (Left != null && Right != null)
                {
                    if (Left.ShortestBranchHeight() <= Right.ShortestBranchHeight())
                    {
                        return Left.ShortestBranchLastNode();
                    }
                    else
                    {
                        return Right.ShortestBranchLastNode();
                    }
                }
                // сюда программа дойти не может, поскольку разобраны всевозможные случаи
                return null;
            }

            // задание 4: рекурсивный метод возвращает лист(конец) самой длинной ветки поддерева
            public Node LongestBranchLastNode()
            {
                // выход из рекурсии. Случай листа(нет потомков)
                if (Left == null && Right == null)
                {
                    return this;
                }
                // случай сучка(есть только правый потомок)
                if (Left == null && Right != null)
                {
                    return Right.LongestBranchLastNode();
                }
                // случай сучка(есть только левый потомок)
                if (Left != null && Right == null)
                {
                    return Left.LongestBranchLastNode();
                }
                // случай сучка(есть оба потомка)
                if (Left != null && Right != null)
                {
                    if (Left.Height() >= Right.Height())
                    {
                        return Left.LongestBranchLastNode();
                    }
                    else
                    {
                        return Right.LongestBranchLastNode();
                    }
                }
                // сюда программа дойти не может, поскольку разобраны всевозможные случаи
                return null;
            }

            // Задание 6: рекурсивный метод возвращает количество листьев в поддереве
            public int AmountOfLeaves()
            {
                // выход из рекурсии. Случай листа(нет потомков)
                if (Left == null && Right == null)
                {
                    return 1;
                }
                // случай сучка(есть только левый потомок)
                if (Left != null && Right == null)
                {
                    return Left.AmountOfLeaves();
                }
                // случай сучка(есть только правый потомок)
                if (Left == null && Right != null)
                {
                    return Right.AmountOfLeaves();
                }
                // случай сучка(есть оба потомка)
                if (Left != null && Right != null)
                {
                    return Left.AmountOfLeaves() + Right.AmountOfLeaves();
                }
                // сюда программа дойти не может, поскольку разобраны всевозможные случаи
                return -1;
            }
            
            // Задание 7: рекурсивный метод, проверяет является ли поддерево строгим
            public bool Strict()
            {
                // выход из рекурсии. Случай листа(нет потомков)
                if (Left == null && Right == null)
                {
                    return true;
                }
                // случай сучка(есть только левый потомок)
                if (Left != null && Right == null)
                {
                    return false;
                }
                // случай сучка(есть только правый потомок)
                if (Left == null && Right != null)
                {
                    return false;
                }
                // случай сучка(есть оба потомка)
                if (Left != null && Right != null)
                {
                    return Left.Strict() && Right.Strict();
                }
                // сюда программа дойти не может, поскольку разобраны всевозможные случаи
                return true;
            }
            
            // Задание 8: рекурсивный метод, проверяет является ли поддерево полным
            public bool Full()
            {
                // выход из рекурсии. Случай листа(нет потомков)
                if (Left == null && Right == null)
                {
                    return true;
                }
                // случай сучка(есть только левый потомок)
                if (Left != null && Right == null)
                {
                    return false;
                }
                // случай сучка(есть только правый потомок)
                if (Left == null && Right != null)
                {
                    return false;
                }
                // случай сучка(есть оба потомка)
                if (Left != null && Right != null)
                {
                    return Left.Full() && Right.Full() && Left.Height() == Right.Height();
                }
                // сюда программа дойти не может, поскольку разобраны всевозможные случаи
                return true;
            }

            // Задание 9: рекурсивный метод добавляет в переданный ему список листы поддерева 
            public void ListOfLeaves(ref List<int> l)
            {
                // выход из рекурсии. Случай листа(нет потомков)
                if (Left == null && Right == null)
                {
                    l.Add(this.Data);
                    return;
                }
                // случай сучка(есть только левый потомок)
                if (Left != null && Right == null)
                {
                    Left.ListOfLeaves(ref l);
                    return;
                }
                // случай сучка(есть только правый потомок)
                if (Left == null && Right != null)
                {
                    Right.ListOfLeaves(ref l);
                    return;
                }
                // случай сучка(есть оба потомка)
                if (Left != null && Right != null)
                {
                    Left.ListOfLeaves(ref l);
                    Right.ListOfLeaves(ref l);
                    return;
                }
                // сюда программа дойти не может, поскольку разобраны всевозможные случаи
                return;
            }
        }

        // свойство для чтения и записи корня дерева
        public Node Root { get; set; }
        
        // конструктор класса дерева
        public BinaryTree()
        {
            Root = null;
        }
        
        // вычисляет высоту дерева
        public int Height()
        {
            if (Root == null)
            {
                return 0;
            }
            else
            {
                return Root.Height();
            }
        }
        
        // задание 1: проверяет дерево на сбалансированность
        public bool Balanced()
        {
            if (Root == null)
            {
                return true;
            }
            else
            {
                return Root.Balanced();
            }
        }
        
        // задание 2: вычисляет количество элементов с заданным значением value
        public int AmountOfValue(int value)
        {
            if (Root == null)
            {
                return 0;
            }
            else
            {
                return Root.AmountOfValue(value);
            }
        }
        
        // возвращает лист(конец) самой короткой ветки дерева
        public Node ShortestBranchLastNode()
        {
            if (Root == null)
            {
                return null;
            }
            else
            {
                return Root.ShortestBranchLastNode();
            }
        }

        // задание 3: возвращает строку, состоящую из элементов самой короткой ветки дерева
        public string ShortestBranch()
        {
            string s = "";
            // случай пустого дерева
            if (Root == null)
            {
                return s;
            }

            // случай непустого дерева
            Node temp = Root.ShortestBranchLastNode();
            // поднимаемся от последнего элемента самой короткой ветки, пока не достигнем корня
            while (temp.Parent != null)
            {
                s = temp.Data.ToString() + " " + s;
                temp = temp.Parent;
            }
            s = temp.Data.ToString() + " " + s;

            return s;
        }

        // возвращает лист(конец) самой длинной ветки дерева
        public Node LongestBranchLastNode()
        {
            if (Root == null)
            {
                return null;
            }
            else
            {
                return Root.LongestBranchLastNode();
            }
        }

        // задание 4: возвращает строку, состоящую из элементов самой длинной ветки дерева
        public string LongestBranch()
        {
            string s = "";
            // случай пустого дерева
            if (Root == null)
            {
                return s;
            }

            // случай непустого дерева
            Node temp = Root.LongestBranchLastNode();
            // поднимаемся от последнего элемента самой короткой ветки, пока не достигнем корня
            while (temp.Parent != null)
            {
                s = temp.Data.ToString() + " " + s;
                temp = temp.Parent;
            }
            s = temp.Data.ToString() + " " + s;

            return s;
        }

        // задание 5:
        public int MaxLevel()
        {
            if (Root == null)
            {
                return 0;
            }

            int h = this.Height();
            List<Node>[] x = new List<Node>[h];
            x[0].Add(Root);
            for (int i = 1; i < h; ++i)
            {
                foreach (var n in x[i - 1])
                {
                    if (n.Left != null)
                    {
                        x[i].Add(n.Left);
                    }
                    if (n.Right != null)
                    {
                        x[i].Add(n.Right);
                    }
                }
            }

            int maxLength = 0;
            int indexOfMaxLevel = -1;
            for (int i = 0; i < h; ++i)
            {
                if (x[i].Count() > maxLength)
                {
                    maxLength = x[i].Count();
                    indexOfMaxLevel = i;
                }
            }

            return indexOfMaxLevel + 1;
        }

        // задание 6: вычисляет количество листьев дерева
        public int AmountOfLeaves()
        {
            if (Root == null)
            {
                return 0;
            }
            else
            {
                return Root.AmountOfLeaves();
            }
        }
        
        // задание 7: проверяет является ли дерево строгим
        public bool Strict()
        {
            if (Root == null)
            {
                return true;
            }
            else
            {
                return Root.Strict();
            }
        }

        // задание 8: проверяет является ли дерево полным
        public bool Full()
        {
            if (Root == null)
            {
                return true;
            }
            else
            {
                return Root.Full();
            }
        }

        // Задание 9: рекурсивный метод добавляет в переданный ему список листы поддерева
        public string Leaves()
        {
            string s = "";

            // случай пустого дерева
            if (Root == null)
            {
                return s;
            }

            // заполним список для листов
            List<int> l = new List<int>();
            Root.ListOfLeaves(ref l);

            // отсортируем список для листов
            l.Sort();
            // скопируем его элементы в строку
            foreach (var n in l)
            {
                s += n.ToString() + " ";
            }

            return s;
        }
    }
}
