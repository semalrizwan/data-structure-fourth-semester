#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

/*
1. what i understand about the task
this task requires creating a hashtable that resolves collisions by storing entries inside binary search trees rather than using simple linked lists

2. how i will do the task
i will use the string hash calculation function to find the array index slot and then invoke standard bst insert find or remove routines on that specific tree root pointer

3. functions reused
the custom string hashing logic is reused across add search and remove to locate the exact array bucket index before manipulating its tree nodes
progression sequence traces to selecting an index and editing the specific bst attached at that position
*/

// duplication of alphanumeric string hash algorithm calculation logic
int getTask5Hash(string str) 
{
    int sum = 0; // establish initial sum aggregation baseline fields variables
    for (size_t i = 0; i < str.size(); i++) // step across string characters limit sizes
    {
        sum += (int)str[i]; // map ascii character positions value components inside total sums
    }
    if (str.size() == 0)
    {
        return 0; // check for empty strings
    }
    return sum % str.size(); // give back balanced index code numbers loops
}

// helper routine to insert string value into target bst structure
Node<string>* insertBst(Node<string>* r, string val) 
{
    if (r == nullptr) 
    { // evaluate empty tree leaf condition triggers
        Node<string>* n = new Node<string>(); // reserve heap allocation space segments
        n->data = val; // map user data values inputs
        n->left = nullptr; // assign initial zero empty links tracks
        n->right = nullptr; // assign initial zero empty links tracks
        return n; // send back active node tracking handle details
    }
    if (val < r->data
        {
            r->left = insertBst(r->left, val); // branch left recursively
        }
    else if (val > r->data)
    {
        r->right = insertBst(r->right, val); // branch right 
    }
    return r; // return modified node pointer reference
}

// helper routine to search string value inside target bst structure
bool searchBst(Node<string>* r, string val) 
{
    if (r == nullptr)
    {
        return false; // stop queries on missing leaf traces
    }
    if (r->data == val)
    {
        return true; // validate matches success lookups tags
    }
    if (val < r->data)
    {
        return searchBst(r->left, val); // check lower bounds branches paths
    }
    return searchBst(r->right, val); // check upper bounds branches paths
}

// helper routine to erase matching string nodes inside target bst structure
Node<string>* removeBst(Node<string>* r, string val, bool& success)
{
    if (r == nullptr)
    {
        return r; // escape empty structure tracks runs
    }
    if (val < r->data)
    {
        r->left = removeBst(r->left, val, success); // continue search recursively left
    }
    else if (val > r->data)
    {
        r->right = removeBst(r->right, val, success); // continue search recursively right
    }
    else 
    { // current node data matches target string
        success = true; // raise boolean validation tracking flags indicators
        if (r->left == nullptr || r->right == nullptr) 
        { // check for single child or leaf states
            Node<string>* t = r->left ? r->left : r->right; // capture existing valid branches paths
            if (t == nullptr)
            {
                t = r; r = nullptr; 
            }
            else
            {
                *r = *t; // safely shift tracking targets properties
            }
            delete t; // wipe allocated heap objects blocks records
        }
        else 
        { // handle dual children node states scenarios
            Node<string>* c = r->right; // jump right side
            while (c->left != nullptr)
            {
                c = c->left; // slide left to bottom child
            }
            r->data = c->data; // replace value metrics attributes
            r->right = removeBst(r->right, c->data, success); // prune duplicate records paths
        }
    }
    return r; // return updated tree pointer reference
}

// method to assign and insert string items inside bst hash table buckets
void add(Node<string>** a, int size, string str) 
{
    int idx = getTask5Hash(str) % size; // pull structural index targets codes ranges
    a[idx] = insertBst(a[idx], str); // append text entries via recursive insertion helpers
}

// method to search string items inside bst hash table buckets
bool search(Node<string>** a, int size, string str) 
{
    int idx = getTask5Hash(str) % size; // figure target lookup bucket indexes locations
    return searchBst(a[idx], str); // run structural query lookups functions
}

// method to remove string items from bst hash table buckets
string remove(Node<string>** a, int size, string str) 
{
    int idx = getTask5Hash(str) % size; // trace specific data bucket array lanes
    bool flag = false; // set baseline entry identification checker logs
    a[idx] = removeBst(a[idx], str, flag); // drop components items out of structural paths
    if (flag)
    {
        return str; // return erased string on delete success
    }
    return "not found"; // return missing flags tags messages logs
}

int main() 
{
    int tableSize = 5; // specify maximum array tracking boundaries caps limits
    Node<string>** bstTable = new Node<string>*[tableSize]; // open dynamic array block pointers trackers
    for (int i = 0; i < tableSize; i++) bstTable[i] = nullptr; // seed rows buffers locations with nulls values

    add(bstTable, tableSize, "test"); // add test item inside tables list arrays
    add(bstTable, tableSize, "apple"); // add apple item inside tables list arrays

    cout << "searching apple inside hash table returns: " << search(bstTable, tableSize, "apple") << endl; // show lookup trace details
    cout << "removing apple entry: " << remove(bstTable, tableSize, "apple") << endl; // process data items removal request lines

    for (int i = 0; i < tableSize; i++) 
    { // look across table size allocations to clean up
        while (bstTable[i] != nullptr) 
        { // clear existing tree contents blocks
            bool clearFlag = false; // dummy loop parameter
            bstTable[i] = removeBst(bstTable[i], bstTable[i]->data, clearFlag); // clear active node root item
        }
    }
    delete[] bstTable; // release table storage array structure memory allocations
    return 0; // return successfully
}