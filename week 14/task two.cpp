#include <iostream>

using namespace std;

/*
1. what i understand about the task
this task requires implementing a maxheap using an underlying array structure while satisfying standard heap behaviors like heapify buildheap sorting inserting searching and checking if empty or full

2. how i will do the task
i will track array allocation dynamically based on the maxheap constructor capacities insert elements at the end and bubble up and extract or remove elements by replacing with the last item and bubbling down

3. functions reused
maxheapify is reused within buildheap remove and heapsort to fix down the heap order violations whenever elements change position
progression of array values looks like an array index zero connecting to left child index one and right child index two
*/

template <class T>
class MaxHeap 
{
public:
    MaxHeap(); // default constructor declaration
    MaxHeap(int cap); // constructor with max size capacity parameter
    MaxHeap(const MaxHeap& mh); // copy constructor declaration
    const MaxHeap& operator = (const MaxHeap& mh); // assignment operator declaration
    ~MaxHeap(); // destructor declaration
    void insert(const T& value); // insert element method
    void remove(const T& value); // remove element method
    bool search(const T& value) const; // search value method
    void heapsort(); // perform heap sort method
    bool isEmpty() const; // check empty method
    bool isFull() const; // check full method
    void inorderDisplay() const; // visual print method
protected:
    T* array; // array pointer for storing values
    int capacity; // max limit capacity of array
    int size; // active current size of elements
    void maxHeapify(int i); // bubble down item correction method
    void buildHeap(); // structure conversion method
};

// default constructor implementation
template <class T>
MaxHeap<T>::MaxHeap() 
{
    capacity = 10; // assign default allocation limit to ten
    size = 0; // initialize current filled size to zero
    array = new T[capacity]; // allocate heap memory array space
}

// parameterized constructor implementation
template <class T>
MaxHeap<T>::MaxHeap(int cap)
{
    capacity = cap; // set internal capacity limit to user spec
    size = 0; // initialize filled element counter to zero
    array = new T[capacity]; // allocate dynamic chunk size matching capacity
}

// copy constructor implementation
template <class T>
MaxHeap<T>::MaxHeap(const MaxHeap& mh)
{
    capacity = mh.capacity; // mirror allocation capacity limits
    size = mh.size; // match the ongoing count of items
    array = new T[capacity]; // allocate independent chunk of memory
    for (int i = 0; i < size; i++) // iterate up to size bounds
    {
        array[i] = mh.array[i]; // duplicate values into new block
    }
}

// assignment operator implementation
template <class T>
const MaxHeap<T>& MaxHeap<T>::operator = (const MaxHeap& mh) 
{
    if (this != &mh) 
    { // protect against matching address self assigns
        delete[] array; // clear previous allocated dynamic elements
        capacity = mh.capacity; // duplicate source limits capacity
        size = mh.size; // copy exact count tracker properties
        array = new T[capacity]; // establish brand new storage space
        for (int i = 0; i < size; i++) // step across source contents bounds
        {
            array[i] = mh.array[i]; // rewrite positions with source values
        }
    }
    return *this; // return internal reference handle
}

// destructor implementation
template <class T>
MaxHeap<T>::~MaxHeap() 
{
    delete[] array; // reclaim array buffer allocation memory block
}

// bubble down method to keep max heap property intact
template <class T>
void MaxHeap<T>::maxHeapify(int i) 
{
    int left = 2 * i + 1; // get theoretical left child position slot
    int right = 2 * i + 2; // get theoretical right child position slot
    int largest = i; // project current slot as containing highest value
    if (left < size && array[left] > array[largest]) // check if left child value is 
    {
        largest = left; // flag left child position as largest
    }
    if (right < size && array[right] > array[largest]) // check if right child value is larger
    {
        largest = right; // flag right child position as largest
    }
    if (largest != i) 
    { // see if largest element position shifted away from original
        swap(array[i], array[largest]); // swap out out of order values
        maxHeapify(largest); // recursively verify lower levels match rule
    }
}

// method to convert an arbitrary array setup into max heap order
template <class T>
void MaxHeap<T>::buildHeap() 
{
    for (int i = (size / 2) - 1; i >= 0; i--) // start at final non leaf index node
    {
        maxHeapify(i); // sink down mismatched values sequentially
    }
}

// insert element value method
template <class T>
void MaxHeap<T>::insert(const T& value) 
{
    if (isFull()) // guard check against overflowing available capacity
    {
        return; // stop execution path
    }
    array[size] = value; // populate the final empty node boundary point
    int current = size; // grab current index of value
    size++; // slide size metric tracker upwards one step
    while (current != 0 && array[(current - 1) / 2] < array[current]) 
    { // bubble up smaller parent items
        swap(array[current], array[(current - 1) / 2]); // correct locations via standard swap values
        current = (current - 1) / 2; // climb up tracker pointer position to parent index
    }
}

// remove element value method
template <class T>
void MaxHeap<T>::remove(const T& value
    {
    int index = -1; // baseline missing element target code marker
    for (int i = 0; i < size; i++
    { // cross across all valid indexes
        if (array[i] == value)
        { // check if array position matches search term
            index = i; // save active target match loop index
            break; // escape tracking iteration sequence
        }
    }
    if (index == -1) // check if item was found
    {
        return; // exit function path safely
    }
    array[index] = array[size - 1]; // overlay current position with final item bounds
    size--; // compress effective size scope window limits down
    maxHeapify(index); // re balance elements downwards starting at index
}

// standard lookup match query search method
template <class T>
bool MaxHeap<T>::search(const T& value) const 
{
    for (int i = 0; i < size; i++) 
    { // look through active indexes positions
        if (array[i] == value) // confirm if equality condition holds true
        {
            return true; // confirm tracking success match
        }
    }
    return false; // return false for missing values
}

// sort method on heap items
template <class T>
void MaxHeap<T>::heapsort() 
{
    int backupSize = size; // preserve current counter state variables
    for (int i = size - 1; i > 0; i--) 
    { // process boundaries backward step lengths
        swap(array[0], array[i]); // send highest active index value back
        size--; // scale down structural boundaries dynamically
        maxHeapify(0); // re clear top node constraint bounds
    }
    size = backupSize; // reinstall full structural range sizes
}

// check if heap is empty method
template <class T>
bool MaxHeap<T>::isEmpty() const
{
    return size == 0; // evaluate base emptiness condition state
}

// check if heap is full method
template <class T>
bool MaxHeap<T>::isFull() const 
{
    return size == capacity; // evaluate boundary threshold match state
}

// inline inorder tree representation traversal display method
template <class T>
void MaxHeap<T>::inorderDisplay() const 
{
    for (int i = 0; i < size; i++) // cycle indices bounds range
    {
        cout << array[i] << " "; // print current items separated by space
    }
    cout << endl; // close off the console streams
}

int main() 
{
    MaxHeap<int> heap(10); // make max heap object instance
    heap.insert(40); // place forty inside max heap structure
    heap.insert(50); // place fifty inside max heap structure
    heap.insert(30); // place thirty inside max heap structure
    cout << "heap elements ordered layout are " << endl; // status line trace message
    heap.inorderDisplay(); // show elements inside max heap structure layout
    heap.heapsort(); // process ascending sort order sequencing run
    cout << "heap elements sorted layout are " << endl; // status line trace message
    heap.inorderDisplay(); // output elements sequence order layout results
    return 0; // return successfully
}