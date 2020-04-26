using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.ComponentModel;
using System.ComponentModel.Design.Serialization;
using System.Linq;
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
            // задание 3: рекурсивный метод выозвращает длину самой короткой ветки поддерева и
            // записывает все элементы этой ветки через пробел в переменную s
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
        }
        // свойство для чтения и записи корня дерева
        public Node Root { get; set; }
        // конструктор класса дерева
        public BinaryTree()
        {
            Root = null;
        }
        // рекурсивный метод вычисляет высоту дерева
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
        // задание 1: рекурсивный метод проверяет дерево на сбалансированность
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
        // задание 2: рекурсивный метод вычисляет количество элементов с заданным значением value
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
        // задание 3: рекурсивный метод выозвращает длину самой короткой ветки дерева и
        // записывает все элементы этой ветки через пробел в переменную s
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
        public string ShortestBranch()
        {
            string s = "";
            if (Root == null)
            {
                return s;
            }

            Node temp = Root.ShortestBranchLastNode();
            while (temp.Parent != null)
            {
                s = temp.Data.ToString() + " " + s;
                temp = temp.Parent;
            }
            s = temp.Data.ToString() + " " + s;

            return s;
        }
        
        // задание 6: рекурсивный метод вычисляет количество листьев дерева
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
        
        // задание 7: рекурсивный метод проверяет является ли дерево строгим
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

        // задание 8: рекурсивный метод проверяет является ли дерево полным
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
    }
}
