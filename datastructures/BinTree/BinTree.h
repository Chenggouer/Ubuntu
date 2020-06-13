#ifndef BINTREE_H_
#define BINTREE_H_
#include "BinNode.h"
#include<cmath>

template<typename T>
class BinTree
{
protected:
	int _size;
	BinNode<T>* _root;
	virtual int updateHeight(BinNode<T>*);
	void updateHeightAbove(BinNode<T>*); //更新节点及其祖先的高度
public:
	BinTree() : _size{0}, _root{nullptr} {}
	~BinTree() {if(0 < _size) remove( _root);}
	int size() const {return _size;}
	bool isEmpty() const {return !_root;}
	BinNode<T>* root() const {return _root;}
	BinNode<T>* insertAsRoot(const T& e); //作为根插入
	BinNode<T>* insertAsLc(BinNode<T>* x, const T& e); //作为左孩子插入
	BinNode<T>* insertAsRc(BinNode<T>* x, const T& e);
	BinNode<T>* attachAsLc(BinNode<T>* x, BinTree<T>*& t); //t作为x的左子树插入
	BinNode<T>* attachAsRc(BinNode<T>* x, BinTree<T>*& t);
	int remove(BinNode<T>* x); //删除以x节点为根的子树，返回该子树的规模
    //二叉子树分离，将X子树封装为新的树返回
	BinTree<T>* secede(BinNode<T>* x);
	template<typename VST>
	void travLevel(VST& visit) {if(_root) _root->travLevel(visit);}
	template<typename VST>
	void travPre_r(VST& visit) {if(_root) _root->travPre_r(visit);}
	template<typename VST>
	void travPost_r(VST& visit) {if(_root) _root->travPost_r(visit);}
	template<typename VST>
	void travIn_r(VST& visit) {if(_root) _root->travIn_r(visit);}

	bool operator<(const BinTree<T>* t)
	{
		return _root && t->_root && (_size < t->size());
	}
	bool operator>(const BinTree<T>* t)
	{
		return _root && t->_root && (_size > t->size());
	}
	bool operator==(const BinTree<T>* t)
	{
		return _root && t->_root && (_size = t->size());
	}

};

template<typename T>
int BinTree<T>::updateHeight(BinNode<T>* x)
{
	return x->height = 1 + max(stature(x->lc), stature(x->rc));
}
template<typename T>
void BinTree<T>::updateHeightAbove(BinNode<T>* x)
{
	while(x)
	{
		updateHeight(x);
		x = x->parent;
	}
}

template<typename T>
BinNode<T>* BinTree<T>::insertAsRoot(const T& e)
{
	_size = 1;
	return _root = new BinNode<T>(e);
}

template<typename T>
BinNode<T>* BinTree<T>::insertAsLc(BinNode<T>* x, const T& e)
{
	_size++;
	x->insertAsLc(e);
	updateHeightAbove(x);
	return x->lc;
}

template<typename T>
BinNode<T>* BinTree<T>::insertAsRc(BinNode<T>* x, const T& e)
{
	_size++;
	x->insertAsRc(e);
	updateHeightAbove(x);
	return x->rc;
}

template<typename T>
BinNode<T>* BinTree<T>::attachAsLc(BinNode<T>* x, BinTree<T>*& t)
{
	if(x->lc) return nullptr;
	x->lc = t->_root;
	t->_root->parent = x;
	_size += t->_size;
	updateHeightAbove(x);
	t->_size = 0;  //子树置空
	t->_root = nullptr;
	release(t); //释放t
	t = nullptr; 

	return x; //返回接入位置
}

template<typename T>
BinNode<T>* BinTree<T>::attachAsRc(BinNode<T>* x, BinTree<T>*& t)
{
	if(x->rc) return nullptr;
	x->rc = t->_root;
	x->_root->parent = x;
	_size += t->_size;
	updateHeightAbove(x);
	t->_size = 0;
	t->_root = nullptr;
	release(t);
	t = nullptr;
}

template<typename T>
int BinTree<T>::remove(BinNode<T>* x)
{
	//切断x的来自父节点
	if(x->isRchild()) x->parent->rc = nullptr;
	if(x->isLchild()) x->parent->lc = nullptr;
	updateHeightAbove(x->parent);
	int n = removeAt(x);
	_size -= n;
	return n;
}
template<typename T>
static int removeAt(BinNode<T>* x)
{
	if(!x) return 0;
	int n = 1 + removeAt(x->lc) + removeAt(x->rc);
	release(x->data);
	release(x);
	return n;
}

template<typename T>
BinTree<T>* BinTree<T>::secede(BinNode<T>* x)
{
	if(x->isRchild) x->parent->rc = nullptr;
	if(x->isLchild) x->parent->lc = nullptr;
	updateHeightAbove(x->parent);
	BinTree<T>* s = new BinTree<T>;
	s->_root = x;
	x->parent = nullptr;
	s->_size = x->size();
	_size -= s->_size; //更新原树的规模
	return s;
}

#endif
