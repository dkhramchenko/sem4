using System;
using System.Collections.Generic;
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
            }
            // свойство для чтения и записи данных узла
            public int Data { get; set; }
            // свойство для чтения и записи левого потомка
            public Node Left { get; set; }
            // свойство для чтения и записи правого потомка
            public Node Right { get; set; }
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
            // рекурсивный метод проверяет поддерево на сбалансированность
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
            // рекурсивный метод 
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
            public int MinBranchLength()
            {
                if (Left == null && Right == null)
                {
                    return 1;
                }

                if (Left != null && Right == null)
                {
                    return 1 + Left.MinBranchLength();
                }

                return 0;
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
        // рекурсивный метод проверяет дерево на сбалансированность
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
        // рекурсивный метод вычисляет количество элементов с заданным значением value
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
    }
}
