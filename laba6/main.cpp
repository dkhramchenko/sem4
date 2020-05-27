//! класс дерева
class RBtree {
	struct node_st { node_st* p1, * p2; int value; bool red; }; // структура узла
	node_st* tree_root;					// корень
	int nodes_count;					// число узлов дерева
private:
	node_st* NewNode(int value);		// выделение новой вешины
	void DelNode(node_st*);				// удаление вершины
	node_st* Rotate21(node_st*);		// вращение влево
	node_st* Rotate12(node_st*);		// вращение вправо
	void BalanceInsert(node_st**);		// балансировка вставки
	bool BalanceRemove1(node_st**);		// левая балансировка удаления
	void print();                       // печать
	bool BalanceRemove2(node_st**);		// правая балансировка удаления
	bool Insert(int, node_st**);		// рекурсивная часть вставки
	bool Remove(node_st**, int);		//рекурсивная часть удаления
	int getElementByKey(int key);       // поиск элемента по ключу
	int getElementHeightByKey(int key); // высота элемента по ключу
};
// выделение новой вешины
RBtree::node_st* RBtree::NewNode(int value)
{
	nodes_count++;
	node_st* node = new node_st;
	node->value = value;
	node->p1 = node->p2 = 0;
	node->red = true;
	return node;
}

// удаление вершины
void RBtree::DelNode(node_st* node)
{
	nodes_count--;
	delete node;
}

// вращение влево
RBtree::node_st* RBtree::Rotate21(node_st* node)
{
	node_st* p2 = node->p2;
	node_st* p21 = p2->p1;
	p2->p1 = node;
	node->p2 = p21;
	return p2;
}

// вращение вправо
RBtree::node_st* RBtree::Rotate12(node_st* node)
{
	node_st* p1 = node->p1;
	node_st* p12 = p1->p2;
	p1->p2 = node;
	node->p1 = p12;
	return p1;
}

// балансировка вершины
void RBtree::BalanceInsert(node_st** root)
{
	node_st* p1, * p2, * px1, * px2;
	node_st* node = *root;
	if (node->red) return;
	p1 = node->p1;
	p2 = node->p2;
	if (p1 && p1->red) {
		px2 = p1->p2;
		if (px2 && px2->red) p1 = node->p1 = Rotate21(p1);
		px1 = p1->p1;
		if (px1 && px1->red) {
			node->red = true;
			p1->red = false;
			if (p2 && p2->red) {
				px1->red = true;
				p2->red = false;
				return;
			}
			*root = Rotate12(node);
			return;
		}
	}
	// тоже самое в другую сторону
	if (p2 && p2->red) {
		px1 = p2->p1;
		if (px1 && px1->red) p2 = node->p2 = Rotate12(p2);
		px2 = p2->p2;
		if (px2 && px2->red) {
			node->red = true;
			p2->red = false;
			if (p1 && p1->red) {
				px2->red = true;
				p1->red = false;
				return;
			}
			*root = Rotate21(node);
			return;
		}
	}
}


bool RBtree::BalanceRemove1(node_st** root)
{
	node_st* node = *root;
	node_st* p1 = node->p1;
	node_st* p2 = node->p2;
	if (p1 && p1->red) {
		p1->red = false; return false;
	}
	if (p2 && p2->red) {
		node->red = true;
		p2->red = false;
		node = *root = Rotate21(node);
		if (BalanceRemove1(&node->p1)) node->p1->red = false;
		return false;
	}
	unsigned int mask = 0;
	node_st* p21 = p2->p1;
	node_st* p22 = p2->p2;
	if (p21 && p21->red) mask |= 1;
	if (p22 && p22->red) mask |= 2;
	switch (mask)
	{
	case 0:

		p2->red = true;
		return true;
	case 1:
	case 3:
		p2->red = true;
		p21->red = false;
		p2 = node->p2 = Rotate12(p2);
		p22 = p2->p2;
	case 2:
		p2->red = node->red;
		p22->red = node->red = false;
		*root = Rotate21(node);
	}
	return false;
}

int RBtree::getElementByKey(int key)
{
	node_st* node = *root;
	if (!node)*root = NewNode(value);
	else {
		if (value == node->value) return true;
		if (Insert(value, value < node->value ? &node->p1 : &node->p2)) return true;
		BalanceInsert(root);
	}
	return el;
}

int RBtree::getElementHeightByKey(int key)
{
	node_st* p1, * p2, * px1, * px2;
	node_st* node = *root;
	if (node->red) return;
	p1 = node->p1;
	p2 = node->p2;
	if (p1 && p1->red) {
		px2 = p1->p2;
		if (px2 && px2->red) p1 = node->p1 = Rotate21(p1);
		px1 = p1->p1;
		if (px1 && px1->red) {
			node->red = true;
			p1->red = false;
			if (p2 && p2->red) {
				px1->red = true;
				p2->red = false;
				return;
			}
			*root = Rotate12(node);
			return;
		}
	}
	return h;
}

bool RBtree::BalanceRemove2(node_st** root)
{
	node_st* node = *root;
	node_st* p1 = node->p1;
	node_st* p2 = node->p2;
	if (p2 && p2->red) { p2->red = false; return false; }
	if (p1 && p1->red) { // случай 1
		node->red = true;
		p1->red = false;
		node = *root = Rotate12(node);
		if (BalanceRemove2(&node->p2)) node->p2->red = false;
		return false;
	}
	unsigned int mask = 0;
	node_st* p11 = p1->p1;
	node_st* p12 = p1->p2;
	if (p11 && p11->red) mask |= 1;
	if (p12 && p12->red) mask |= 2;
	switch (mask) {
	case 0:
		p1->red = true;
		return true;
	case 2:
	case 3:
		p1->red = true;
		p12->red = false;
		p1 = node->p1 = Rotate21(p1);
		p11 = p1->p1;
	case 1:
		p1->red = node->red;
		p11->red = node->red = false;
		*root = Rotate12(node);
	}
	return false;
}

// рекурсивная часть вставки
bool RBtree::Insert(int value, node_st** root)
{
	node_st* node = *root;
	if (!node)*root = NewNode(value);
	else {
		if (value == node->value) return true;
		if (Insert(value, value < node->value ? &node->p1 : &node->p2)) return true;
		BalanceInsert(root);
	}
	return false;
}

// рекурсивная часть удаления
bool RBtree::Remove(node_st** root, int value)
{
	node_st* t, * node = *root;
	if (!node) return false;
	if (node->value < value) {
		if (Remove(&node->p2, value))	return BalanceRemove2(root);
	}
	else if (node->value > value) {
		if (Remove(&node->p1, value))	return BalanceRemove1(root);
	}
	else {
		bool res;
		if (!node->p2) {
			*root = node->p1;
			res = !node->red;
		}
		else {
			res = GetMin(&node->p2, root);
			t = *root;
			t->red = node->red;
			t->p1 = node->p1;
			t->p2 = node->p2;
			if (res) res = BalanceRemove2(root);
		}
		DelNode(node);
		return res;
	}
}

#include <iostream>
using namespace std;

int main()
{
	RBtree t;
	cout << "tree:" << endl << endl;
	t.print();
	cout << endl;
	cout << "element with key 5 = " << t.getElementByKey(5) << endl << endl;
	cout << "height = " << t.getElementHeightByKey(5) << endl;
	return 0;
}
