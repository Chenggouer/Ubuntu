#ifndef BST_H_
#define BST_H_
#include "BinTree.h"
template<typename T>
class BST : public BinTree<T>
{
public:
	virtual BinNode<T>*& search(const T&);
	virtual BinNode<T>* insert(const T&);
	virtual bool remove(const T&);
protected:
	BinNode<T>* _hot; //命中节点的父亲
	BinNode<T>* rotateAt(BinNode<T>* x); 
	//连接三个节点四棵子树
	BinNode<T>* connect34(BinNode<T>*, BinNode<T>*, BinNode<T>*,
				BinNode<T>*, BinNode<T>*, BinNode<T>*, 
				BinNode<T>*);

};

template<typename T>
void swap(T& t1, T& t2)
{
	T temp = t1;
	t1 = t2;
	t2 = temp;
}
template<typename T>
BinNode<T>*& BST<T>::search(const T& e)
{
	return searchIn(BinTree<T>::_root, e, _hot = nullptr);
}

template<typename T>
static BinNode<T>*& searchIn(BinNode<T>* v, T e, BinNode<T>*& _hot)
{
	if(!v || (e == v->data)) return v;
	_hot = v;
	//返回时，返回值指向命中节点（或假想的通配哨兵），hot指向其父亲（退化时为初始值nullptr）
	return searchIn(((e < v->data)? v->lc : v->rc), e, _hot);
}

template<typename T>
BinNode<T>* BST<T>::insert(const T& e)
{
	BinNode<T>* x = search(e);
	if(x)  return x;
	x = new BinNode<T>(e, _hot);//BinNode的构造函数
	BinTree<T>::_size++;
	updateHeightAbove(x);
}

template<typename T>
bool BST<T>::remove(const T& e)
{
	BinNode<T>*& x = search(e);
	if(!x)  return false;
	removeAt(x, _hot);
	BinTree<T>::_size--;
	updateHeightAbove(_hot);
	return true;
}

template<typename T>
static BinNode<T>* removeAt(BinNode<T>*& x, BinNode<T>*& hot)
{
	BinNode<T>* w = x; //x 为要删除的节点
	BinNode<T>* succ = nullptr;  //要删除节点的接替节点
	if(!HasLchild(*x))  succ = x = x->rc;
	else if(!HasRchild(*x)) succ = x = x->lc;
	//双分支情况
	else
	{
		w = w->succ();
		swap(x->data, w->data);
		BinNode<T>* u = w->parent;
		((u == x)? u->rc : u->lc) = succ = w->rc; //隔离要删除的节点
	}
	hot = w->parent;
	if(succ) succ->parent = hot;
	release(w->data);
	release(w);
	return succ;
}
//3+4重构，设计动态操作之后的局部平衡重构算法
template<typename T>
BinNode<T>* BST<T>::connect34(BinNode<T>* a, BinNode<T>* b, BinNode<T>* c, BinNode<T>* T0, BinNode<T>* T1, BinNode<T>* T2, BinNode<T>* T3)
{
	a->lc = T0; if(T0) T0->parent = a;
	a->rc = T1; if(T1) T1->parent = a; updateHeight(a);
	c->lc = T2; if(T2) T2->parent = c;
	c->rc = T3; if(T3) T3->parent = c; updateHeight(c);
	b->lc = a; a->parent = b;
	b->rc = c; c->parent = b;
	return b;  //返回重组之后的局部树根
}
//旋转操作
template<typename T>
BinNode<T>* BST<T>::rotateAt(BinNode<T>* v)
{
	BinNode<T>* p = v->parent;
	BinNode<T>* g = p->parent;
	if(isLchild(*p))  //zig
	{
		if(isLchild(*v)) //zig-zig
		{
			p->parent = g->parent;
			return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
		}
		else  //zig -zag
		{
			v->parent = g->parent;
			return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
		}
	}
	else //zag
	{
		if(isRchild(*v))  //zag-zag
		{
			p->parent = g->parent;
			return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
		}
		else //zag-zig
		{
			v->parent = g->parent;
			return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
		}
	}
}
#endif
