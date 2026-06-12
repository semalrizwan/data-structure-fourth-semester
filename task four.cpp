#include <iostream>
#include <string>
#include <cmath>

using namespace std;

/*
1. what i understand about the task
this task requires building various modular hash equation indexing lookup math functions alongside primitive storage array insertion lookups using quadratic and alphanumeric custom algorithms

2. how i will do the task
i will calculate the formulas step by step like linear offset math quadratic offset power calculations and looping character sets summation routines

3. functions reused
getindex is reused inside getlinearkey getquardkey and getcode to process final array modulus wrapping limits safely
progression sequence changes position mappings smoothly depending on changing offset numbers values
*/

// basic index wrapper division method
int getIndex(int value, int size) 
{
    return value % size; // return calculated base index remainder value
}

// linear key index wrapper division method
int getLinearKey(int value, int size, int offset)
{
    return getIndex(value + offset, size); // add offset and reuse getindex function wrapper
}

// quadratic key index wrapper division method
int getQuardKey(int value, int size, int offset)
{
    int base = getIndex(value, size); // retrieve standard index baseline position slot
    return (base + (offset * offset)) % size; // blend quadratic squares and return position index
}

// secondary complex hash combination method
int getCode(int value, int size, int offset)
{
    int base = getIndex(value, size); // resolve initial standard indexing baseline index point
    int quad = getQuardKey(value, size, 2); // invoke secondary quadratic reference calculation metrics
    return (base + (offset * quad)) % size; // merge values via modular math definitions bounds
}

// custom string code parsing hash calculator method
int getHashCode(char* str) 
{
    int sum = 0; // initialize baseline accumulative tally variables count
    int len = 0; // initialize string position tracking counters registers
    while (str[len] != '\0')
    { // iterate until terminal blank array character tags
        sum += (int)str[len]; // append character value inside integer totalizers bounds
        len++; // increment index tracker position
    }
    if (len == 0)
    {
        return 0; // prevent divide by zero exceptions
    }
    return sum % len; // return modular string index parameters values balance
}

// insert element into integer array using quadratic key calculation
void insert(int* a, int size, int offset, int value) 
{
    int idx = getQuardKey(value, size, offset); // query unique quadratic key position target slot
    a[idx] = value; // assign value inside calculated array slot position
}

// retrieve element from integer array using quadratic key calculation
int retrieve(int* a, int size, int offset) 
{
    int idx = getQuardKey(0, size, offset); // assume default test base parameter values zero indices
    return a[idx]; // give back content item located at target cell index
}

// insert string element into string array using hash code calculation
void insert(string* a, int size, int offset, string str) 
{
    char* writable = new char[str.size() + 1]; // allocate temporary dynamic character string container space
    for (size_t i = 0; i < str.size(); i++) // walk across whole user input string bounds
        writable[i] = str[i]; // clone independent array character indexes elements
    writable[str.size()] = '\0'; // inject terminal string boundary symbols
    int idx = getHashCode(writable); // query string unique code value metrics allocations
    a[idx % size] = str; // assign value inside safe array index boundary ranges
    delete[] writable; // release temporary dynamic char buffer layout blocks
}

// retrieve string element from string array using hash code calculation
string retrieve(string* a, int size, int offset) 
{
    return a[offset % size]; // perform primitive cell content index retrieval requests
}

int main() 
{
    int intTable[10] = { 0 }; // create primitive integer storage test tables structure
    insert(intTable, 10, 1, 99); // place ninety nine with offset one inside array bounds
    cout << "calculated index lookups code maps are: " << getIndex(99, 10) << endl; // print trace data outputs
    string strTable[5] = { "" }; // configure simple array of text string rows records
    insert(strTable, 5, 0, "hello"); // register data item string value entries
    cout << "string content item tracking values are: " << strTable[2] << endl; // dump raw index information logs
    return 0; // close execution processes safely
}