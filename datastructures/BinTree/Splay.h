#ifndef SPLAY_H_
#define SPLAY_H_
#include "BST.h"
template<typename T>
class Splay : public BST<T>
{
protected:
	BinNode<T>* splay(BinNode<T>* v);

public:
	BinNode<T>*& search(const T& e);
	BinNode<T>* insert(const T& e);
	bool remove(const T& e);

};
template<typename T>
inline void attachAsLchild(BinNode<T>* p, BinNode<T>* lc)
{
	p->lc = lc;
	if(lc)
	  lc->parent = p;
}

template<typename T>
inline void attachAsRchild(BinNode<T>* p, BinNode<T>* rc)
{
	p->rc = rc;
	if(rc)
	  rc->parent = p;
}

template<typename T>
BinNode<T>* splay(BinNode<T>* v)  //splay树伸展算法，双层伸展
{
	if(!v) return nullptr;
	BinNode<T>* p;
	BinNode<T>* g;
	while((p = v->parent) && (g = p->parent))
	{
		BinNode<T>* gg = g->parent; //保留外部指向伸展局部的指针
		if(isLchild(*v))
		{
			if(isLchild(*p)) //zig-zig
			{
				attachAsLchild(g, p->rc);
				attachAsLchild(p, v->rc);
				attachAsRchild(p, g);
				attachAsRchild(v, p);
			}
			else //zig-zag
			{
				attachAsLchild(p, v->rc);
				attachAsLchild(v, g);
				attachAsRchild(g, v->lc);
				attachAsRchild(v, p);
			}
		}
		else if(isRchild(*p))   //zag-zag
		{
			attachAsLchild(p, g);
			attachAsLchild(v, p);
			attachAsRchild(g, p->lc);
			attachAsRchild(p, v->lc);
		}
		else  //zag-zig
		{
			attachAsLchild(g, v->rc);
			attachAsLchild(v, p);
			attachAsRchild(p, v->lc);
			attachAsRchild(v, g);
		}
		if(!gg) v->parent = nullptr; //v已经伸展到root
		else  //否则 *gg应该以*v作为左/右孩子
		{
			(g == gg->lc) ? attachAsLchild(gg, v) : attachAsRchild(gg, v);
		}
		updateHeight(g);
		updateHeight(p);
		updateHeight(v);
	} //双伸展结束，必有g == nullptr，但p可能不是空，对应树高为奇数情况
	if(p == v->parent)
	{
		if(isLchild(*v)) {attachAsLchild(p, v->rc); attachAsRchild(v, p);}
		else             {attachAsRchild(p, v->lc); attachAsLchild(v, p);}
		updateHeight(p);
		updateHeight(v);
	}
	v->parent = nullptr;
	return v; //返回被伸展的节点，即现在的root(v)节点
}

template<typename T>
BinNode<T>*& Splay<T>::search(const T& e)  //在伸展树中查找e
{
	BinNode<T>* p = searcIn(BinTree<T>::_root, e, BST<T>::_hot = nullptr);
	BinTree<T>::_root = splay(p ? p: BST<T>::_hot);  //将最后一个被访问的节点伸展至root
	return BinTree<T>::_root;
} //与其他BST不同，无论查找是否成功，_root都指向最后被访问到的节点

template<typename T>
BinNode<T>* Splay<T>::insert(const T& e)
{
	if(!BinTree<T>::_root)
	{
		BinTree<T>::_size++;
		BinTree<T>::_root = new BinNode<T>(e);
	}
	if(e == search(e)->data) return BinTree<T>::_root; //e关键码存在返回原root
	BinTree<T>::_size++;
	BinNode<T>* t = BinTree<T>::_root;
	if(BinTree<T>::_root->data < e) //e节点作为root的右孩子，再伸展，结果为插入新根，以 t和t->rc为其左右孩子
	{
		t->parent = BinTree<T>::_root = new BinNode<T>(e, nullptr, t, t->rc);
		if(HasRchild(*t)) {t->rc->parent = BinTree<T>::_root; t->rc = nullptr;}
	}
	else //插入新根，以t->lc,和t为左右孩子
	{
		t->parent = BinTree<T>::_root = new BinNode<T>(e, nullptr, t->lc, t);
		if(HasLchild(*t)) {t->lc->parent = BinTree<T>::_root; t->lc = nullptr;}
	}

	updateHeightAbove(t);

	return BinTree<T>::_root; //新节点处于树根
}

template<typename T>
bool Splay<T>::remove(const T& e)
{
	if(!BinTree<T>::_root || (e != search(e)->data))
	  return false;
	BinNode<T>* w = BinTree<T>::_root; //e经过search已经成为树根节点
	if(!HasLchild(*BinTree<T>::_root)) //若无左子树，直接删除
	{
	  BinTree<T>::_root = BinTree<T>::_root->rc;
	  if(BinTree<T>::_root)  BinTree<T>::_root->parent = nullptr;
	}
	else if(!HasRchild(*BinTree<T>::_root))
	{
		BinTree<T>::_root = BinTree<T>::_root->lc;
		if(BinTree<T>::_root) BinTree<T>::_root->parent = nullptr;
	}
	else //左右子树都存在
	{
		BinNode<T>* lTree = BinTree<T>::_root->lc;
		lTree->parent = nullptr;
		BinTree<T>::_root->lc = nullptr; //切除左子树
		BinTree<T>::_root = BinTree<T>::_root->rc;
		BinTree<T>::_root->paent = nullptr;
		search(w->data); //以原树根为目标做一次必定失败的search
		//至此，右子树中最小节点必然伸展至根，且其左子树为空
		BinTree<T>::_root->lc = lTree;
		lTree->parent = BinTree<T>::_root; //将左子树接回
	}
	release(w->data);
	release(w);
	BinTree<T>::_size--;
	if(BinTree<T>::_root) 
	  updateHeight(BinTree<T>::_root);
	return true;
}

#endif
