#ifndef BINNODE_H_
#define BINNODE_H_
#include<queue>
#include<iostream>

//定义树高
#define stature(p) ((p)? (p)->height : -1)

using std::endl;
using std::cout;
using std::queue;
enum RBcolor{RB_RED, RB_BLACK};

//约束模板友元
template<typename TT> bool HasLchild(const TT&);
template<typename TT> bool HasRchild(const TT&);
template<typename TT> bool isLchild(const TT&);
template<typename TT> bool isRchild(const TT&);
template<typename TT> void release(TT&); //把释放当做友元

template<typename T>
class BinNode
{
private:
	BinNode<T>* parent;
	BinNode<T>* lc;
	BinNode<T>* rc;
	T data;
	int height;
	int npl;
	RBcolor color;
public:
	BinNode() : parent{nullptr}, lc{nullptr}, rc{nullptr},
		height{0}, npl{1},color{RB_RED} {}
	BinNode(T e, BinNode<T>* p = nullptr, BinNode<T>* l = nullptr,
				BinNode<T>* r = nullptr, int h = 0, int n = 1,
				RBcolor c = RB_RED)
		: data{e}, parent{p}, lc{l}, rc{r},height{h},
		npl{n}, color{c} {}
	~BinNode();
	int size() const; //记录当前节点后代规模
	void visit(T e) {cout << e << "\t";}
	BinNode<T>* insertAsLc(const T&);
	BinNode<T>* insertAsRc(const T&);
	BinNode<T>* succ(); //取当前节点的直接后继
	template<typename VST> void travLevel(VST&);
	//递归实现先序遍历
	template<typename VST> void travPre_r(BinNode<T>*, VST&);
	//递归实现中序遍历
	template<typename VST> void travIn_r(BinNode<T>*, VST&);
	//递归实现后学遍历
	template<typename VST> void travPost_r(BinNode<T>*, VST&);
	bool operator<(const BinNode& bn) {return (data < bn.data);}
	bool operator>(const BinNode& bn) {return (data > bn.data);}
	bool operator==(const BinNode& bn) {return (data == bn.data);}
	BinNode<T> operator=(const BinNode<T>& bn);
	//BinNode<T> operator=(const T& e);
    friend bool HasLchild<>(const BinNode<T>& bn) ;
	friend bool HasRchild<>(const BinNode<T>& bn) ;
	friend bool isRchild<>(const BinNode<T>& bn) ;//<>可有参数推导出模板类型参数
	friend bool isLchild<BinNode<T>>(const BinNode<T>& bn) ;
	friend void release<BinNode<T>>(BinNode<T>&);
};

template<typename T>
int BinNode<T>::size() const
{
	int s = 1;
	if(lc) {s += lc->size();}
	if(rc) {s += rc->size();}

	return s;
}
/*
template<typename T>
void BinNode<T>::visit(T e)
{
	cout << e << "\t" ;
}
*/
//实现约束友元函数
template<typename TT>
bool HasLchild(const TT& bn)
{
	return bn.lc == nullptr? false : true;
}

template<typename TT>
bool HasRchild(const TT& bn)
{
	return bn.rc == nullptr? false : true;
}

template<typename TT>
bool isRchild(const TT& bn)
{
	return (bn.parent)->rc == &bn? true : false; 
}

template<typename TT>
bool isLchild(const TT& bn)
{
	return (bn.parent)->lc == &bn? true : false;
}

template<typename TT>
void release(TT x)
{
	if(x)
	{
		release(x->lc);
		release(x->rc);
		delete x;
	}
}
template<typename T>
BinNode<T>* BinNode<T>::insertAsLc(const T& e) 
{
	return lc = new BinNode(e);
}

template<typename T>
BinNode<T>* BinNode<T>::insertAsRc(const T& e)
{
	return rc = new BinNode(e);
}

template<typename T>
BinNode<T>* BinNode<T>::succ()
{
	BinNode<T>* s = this;
	if(rc)
	{
		s = rc;
		while(HasLchild(*s)) {s = s->lc;}
	}
	else
	{
		while(isRchild(*s)) {s = s->parent;}
		s = s->parent;
	}
}
template<typename T>
  template<typename VST>
    void BinNode<T>::travLevel(VST& visit)
{
	queue<BinNode<T>> Q;
	Q.push(this);
	while(!Q.empty())
	{
		BinNode<T>* x = Q.front();//返回队列首元素
		Q.pop(); //队列首元素出队列
		visit(x->data);
		if(HasLchild(*x)) {Q.push(x->lc);}
		if(HasRchild(*x)) {Q.push(x->rc);}
	}
}

template<typename T>
  template<typename VST>
  void BinNode<T>::travPre_r(BinNode<T>* x, VST& visit)
{
	if(!x) return;
	visit(x->data);
	travPre_r(x->lc, visit);
	travPre_r(x->rc, visit);
}

template<typename T>
  template<typename VST>
  void BinNode<T>:: travIn_r(BinNode<T>* x, VST& visit)
{
	if(!x) return;
	travIn(x->lc, visit);
	visit(x->data);
	travIn(x->rc, visit);
}

template<typename T>
  template<typename VST>
  void BinNode<T>::travPost_r(BinNode<T>* x, VST& visit)
{
	if(!x) return;
	travPost_r(x->lc, visit);
	travPost_r(x->rc, visit);
	visit(x->data);
}

template<typename T>
BinNode<T> BinNode<T>::operator=(const BinNode<T>& bn)
{
	this->data = bn.data;
	return *this;
}


#endif
