using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba31
{
    // основной класс дерева
    class BinaryTree
    {
        // класс узла дерева(сучки или листья)
        public class Node
        {
            // свойство для чтения и записи данных узла
            public int Data { get; set; }

            // свойство для чтения и записи левого потомка
            public Node Left { get; set; }

            // свойство для чтения и записи правого потомка
            public Node Right { get; set; }

            // конструктор класса узла
            public Node(int data)
            {
                Data = data;
                Left = null;
                Right = null;
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
        }

        // свойство для чтения и записи корня дерева
        public Node Root { get; set; }

        // конструктор класса дерева
        public BinaryTree()
        {
            Root = null;
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
    }
}
