#ifndef QUEUE_H_
#define QUEUE_H_

class Customer
{
private:
	long arrive;
	int processtime;
public:
	Customer()  {arrive = processtime = 0;}
	void set(long when);
	long when() const {return arrive;}
	int ptime() const {return processtime;}
};

typedef Customer Item;

class Queue
{
private:
	enum {Q_size = 10};
	struct Node
	{
		Item item;
		struct Node* next;
	};
	Node* front;
	Node* rear;
	int items;
	const int qsize;
	Queue(const Queue& q) :qsize{0} {}
	Queue& operator=(const Queue& q) {return *this;}
public:
	Queue(int qs = Q_size);
	~Queue();
	bool isEmpty() const;
	bool isFull() const;
	int QueueCount() const;
	bool enqueue(const Item& item);
	bool dequeue(Item& item);
};

#endif
