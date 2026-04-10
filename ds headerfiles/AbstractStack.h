class AbstractStack
{
 public:
  AbstractStack():count(0){}
  AbstractStack(const AbstractStack & AA);
  virtual void push(int v) = 0; // increments currentIndex and add value if not full
  virtual bool pop(int & value) = 0; // if not empty returns the value at the currentIndex and decrements currentIndex
  bool isEmpty( );
 protected:
  int count;
};

AbstractStack::AbstractStack(const AbstractStack & s): count(s.count){}

bool AbstractStack::isEmpty( )
{
  return (count == 0);
}

