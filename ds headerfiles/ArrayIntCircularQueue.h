class ArrayIntCircularQueue : public IntCircularQueue
{
public:
  ArrayIntCircularQueue(int size) : IntCircularQueue(size)
  {
    arr = new int[this->maxCapacity];
  }
  ArrayIntCircularQueue(const ArrayIntCircularQueue &);
  ~ArrayIntCircularQueue() ;
  bool enqueue(int value) override;
  bool dequeue(int &value) override;
  void display(ostream & W) const;
private:
  int *arr;
};

ArrayIntCircularQueue::ArrayIntCircularQueue(const ArrayIntCircularQueue & cq)
  : IntCircularQueue(cq)
  {
    arr = new T[this->maxCapacity];
    for(int i = 0; i < this->maxCapacity; i++)
      {
	arr[i] = cq.arr[i];
      }
  }

ArrayIntCircularQueue::~ArrayIntCircularQueue() {
    if(arr != nullptr)
      {
	delete[] arr;
	arr = nullptr;
      }
  }

bool ArrayIntCircularQueue::enqueue(int value) {
    if (IntCircularQueue::isFull()) {
      cout << "IntCircularQueue is FULL! Cannot enqueue " << value << endl;
      return false;
    }
    
    if (IntCircularQueue::isEmpty()) {
      this->startOfQIndex = 0;
      this->topOfQIndex = 0;
    } else {
      this->startOfQIndex= (this->startOfQIndex + 1) % this->maxCapacity;
    }
    
    arr[this->startOfQIndex] = value;
    IntCircularQueue::count++;
    return true;
  }

bool ArrayIntCircularQueue::dequeue(int &value) {
    if (IntCircularQueue::isEmpty()) {
      cout << "IntCircularQueue is EMPTY! Cannot dequeue.\n";
      return false;
    }

    value = arr[this->topOfQIndex];
	
    if (this->startOfQIndex == this->topOfQIndex) {
      this->startOfQIndex = this->topOfQIndex = -1;
    } else {
      this->topOfQIndex = (this->topOfQIndex + 1) % this->maxCapacity;
    }
    IntCircularQueue::count--;
    return true;
  }

void ArrayIntCircularQueue::display(ostream & W) const {
    //W << " ";
     W <<"startOfQIndex: " << IntCircularQueue::startOfQIndex
       <<", topOfQIndex: " << IntCircularQueue::topOfQIndex
       <<", maxCapacity: " << IntCircularQueue::maxCapacity
       <<", count: " << IntCircularQueue::count << endl;
    if (IntCircularQueue::isEmpty()) {
      //cout << "IntCircularQueue is EMPTY!" << endl;
      W << "-----\n";
      W << "-----\n";

      return;
    }

    //cout << "IntCircularQueue elements: ";
    W <<"----------------------------\n";
    int i = this->topOfQIndex;
    while (true) {
      W << arr[i];
      if(i != this->topOfQIndex || i != this->startOfQIndex)
	{
	  W << " -> ";
	}
      if (i == this->startOfQIndex)
	{
	  break;
	}
      i = (i + 1) % this->maxCapacity;
    }
    W << endl;
    W <<"----------------------------\n";
  }
