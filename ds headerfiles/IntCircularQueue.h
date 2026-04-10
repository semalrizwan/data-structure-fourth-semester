class IntCircularQueue {
public:
  IntCircularQueue() : count(0) {}
  IntCircularQueue(const IntCircularQueue & q) : count(q.count) {}
  virtual bool enqueue(int value) = 0;     // Enqueue
  virtual bool dequeue(int &value) = 0; // Dequeue
  virtual void display(ostream &)  = 0;
  bool isEmpty()const;
protected:
  int count;
};

bool IntCircularQueue::isEmpty()const 
  {
        return (count == 0);
  }


