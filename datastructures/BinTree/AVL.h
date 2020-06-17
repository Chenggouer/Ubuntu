#ifndef AVL_H_
#define AVL_H_
#include "BST.h"

#define Balanced(x) (stature((x).lc) == stature((x).rc))
#define Balfactor(x) (stature((x).lc) - stature((x).rc)) //平衡因子
#define AVLBalanced(x) ((-2 < Balfactor(x)) && (Balfactor(x) < 2)) //AVL树平衡条件
template<typename T>
class AVL : public BST<T>
{
public:
	BinNode<T>* insert(const T&);
	bool remove(const T&);
};

template<typename T>
BinNode<T>* tallerchild(BinNode<T>* v)
{
	if(!v) return nullptr;
	return stature(v->rc) - stature(v->lc) >= 0? v->rc : v->lc;
}

template<typename T>
BinNode<T>* FormParentTo(BinNode<T> v)
{
	if(!v.parent)
	{
		BinNode<T>* r = v.parent = new BinNode<T>;
		return r;
	}
	return v.parent; 
}
template<typename T>
BinNode<T>* AVL<T>::insert(const T& e)
{
	BinNode<T>*& x = search(e);
	if(x) return x;
	BinNode<T>* xx = x = new BinNode<T>(e, BinTree<T>::_hot);
	BinTree<T>::_size++;

	for(BinNode<T>* g =BinTree<T>::_hot; g; g = g->parent)
	{
		if(!AVLBalanced(*g))
		{
			FormParentTo(*g) = rotateAt(tallerchild(tallerchild(g)));
			break;
		}
		else //没有失衡
		  updateHeight(g);
	}
}

template<typename T>
bool AVL<T>::remove(const T& e)
{
	BinNode<T>*& x = search(e);
	if(!x) return false;
	removeAt(x, BinTree<T>::_hot);
	BinTree<T>::_size--;
	for(BinNode<T>* g = BinTree<T>::_hot; g; g = g->parent)
	{
		if(!AVLBalanced(*g))
		  g = FormParentTo(*g) = rotateAt(tallerchild(tallerchild(g)));
		updateHeight(g);
	}

	return true;
}


#endif
