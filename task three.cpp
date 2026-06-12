#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

/*
1. what i understand about the task
we must combine maxheap and avl trees to build a storage unit tracking user ids inside a maxheap and actual user password array pairs matching inside an avl tree

2. how i will do the task
i will wrap task one and task two behaviors together building menu hooks for inserting removing searching and rendering user info lines

3. functions reused
the custom avl insert and custom maxheap insert are reused when generating entries user deletion reuses custom avl delete and custom maxheap remove
progression sequence looks like option selection loops until shutdown choices are input
*/

// forward dummy declaration representing max heap behaviors
class SystemHeap
{
public:
    string arr[100]; // define static flat storage buffer range
    int sz = 0; // initialize item size offset count
    void addId(string id)
    { // baseline append routine helper
        arr[sz] = id; // map text input string item
        sz++; // shift boundaries forward
    }
    void removeId(string id) 
        // baseline matching deletion helper
        for (int i = 0; i < sz; i++) 
        { // traverse through current limit index
            if (arr[i] == id) 
            { // find matching position slot
                arr[i] = arr[sz - 1]; // overlay position with end value
                sz--; // deduct overall range index limits
                break; // stop traversal loops
            }
        }
    }
};

// simple text string array matching definition structure for node pairs
struct UserPair
{
    string id; // field property holding user identification name
    string pass; // field property holding matching passcode text
    bool operator < (const UserPair& o) const { return id < o.id; } // evaluation shortcut operator overloads
    bool operator > (const UserPair& o) const { return id > o.id; } // evaluation shortcut operator overloads
    bool operator == (const UserPair& o) const { return id == o.id; } // evaluation shortcut operator overloads
};

// forward inline local custom avl implementation support routines
int getAvlh(Node<UserPair>* r
    { 
        return r == nullptr ? 0 : 1 + max(getAvlh(r->left), getAvlh(r->right));
    } // node height query helper
int getAvlb(Node<UserPair>* r) 
    { 
        return r == nullptr ? 0 : getAvlh(r->left) - getAvlh(r->right);
    } // node balance query helper

Node<UserPair>* rRot(Node<UserPair>* r)
{ // right side single tree tilt helper
    Node<UserPair>* lc = r->left; // switch boundaries nodes
    r->left = lc->right; // reassign target left branch
    lc->right = r; // reset parent hierarchy node
    return lc; // give back root target references
}

Node<UserPair>* lRot(Node<UserPair>* r) 
{ // left side single tree tilt helper
    Node<UserPair>* rc = r->right; // switch boundaries nodes
    r->right = rc->left; // reassign target right branch
    rc->left = r; // reset parent hierarchy node
    return rc; // give back root target references
}

Node<UserPair>* addAvl(Node<UserPair>* r, UserPair pair)
{ // insert values method inside matching structures
    if (r == nullptr) 
    { // verify empty reference leaf points
        Node<UserPair>* n = new Node<UserPair>(); // allocate dynamic node storage
        n->data = pair; // copy value items records
        n->left = nullptr; // zero left child node pointer references
        n->right = nullptr; // zero right child node pointer references
        return n; // return new base tree pointer reference
    }
    if (pair.id < r->data.id)
    {
        r->left = addAvl(r->left, pair); // branch left recursively
    }
    else if (pair.id > r->data.id)
    {
        r->right = addAvl(r->right, pair); // branch right recursively
    }
    else
    {
        return r; // escape duplicates entry tasks
    }
    int b = getAvlb(r); // retrieve balance level factors
    if (b > 1 && pair.id < r->left->data.id)
    {
        return rRot(r); // left left adjustment corrections
    }
    if (b < -1 && pair.id > r->right->data.id)
    {
        return lRot(r); // right right adjustment 
    }
    if (b > 1 && pair.id > r->left->data.id) 
    {
        r->left = lRot(r->left); return rRot(r); 
    } // left right corrections
    if (b < -1 && pair.id < r->right->data.id) 
    {
        r->right = rRot(r->right); return lRot(r); 
    } // right left corrections
    return r; // return modified node pointer reference
}

Node<UserPair>* remAvl(Node<UserPair>* r, string id) 
{ // delete matching structural records
    if (r == nullptr)
    {
        return r; // return null pointer reference
    }
    if (id < r->data.id)
    {
        r->left = remAvl(r->left, id); // search left branch structures recursively
    }
    else if (id > r->data.id)
    {
        r->right = remAvl(r->right, id); // search right branch structures recursively
    }
    else
    { // target node matches deletion lookup values
        if (r->left == nullptr || r->right == nullptr
        { // single child or leaf states handles
            Node<UserPair>* t = r->left ? r->left : r->right; // isolate replacement item
            if (t == nullptr) { t = r; r = nullptr; }
            else *r = *t; // wipe reference locations
            delete t; // flush old node heap slots allocations
        }
        else
        { // dual tree branch children scenarios handling
            Node<UserPair>* c = r->right; // jump right side
            while (c->left != nullptr) c = c->left; // slide left to bottom child
            r->data = c->data; // override root entry details
            r->right = remAvl(r->right, c->data.id); // clean duplicate child node fields
        }
    }
    if (r == nullptr)
    {
        return r; // check if tree is empty now
    }
    int b = getAvlb(r); // get balance level factors
    if (b > 1 && getAvlb(r->left) >= 0)
    {
        return rRot(r); // handle left left balancing corrections
    }
    if (b > 1 && getAvlb(r->left) < 0) 
    {
        r->left = lRot(r->left); return rRot(r);
    } // handle left right corrections
    if (b < -1 && getAvlb(r->right) <= 0)
    {
        return lRot(r); // handle right right balancing corrections
    }
    if (b < -1 && getAvlb(r->right) > 0) 
    {
        r->right = rRot(r->right); return lRot(r); 
    } // handle right left corrections
    return r; // return modified node pointer reference
}

Node<UserPair>* searchAvl(Node<UserPair>* r, string id) 
{ // lookup key identifiers records
    if (r == nullptr || r->data.id == id)
    {
        return r; // handle trivial match exits
    }
    if (id < r->data.id)
    {
        return searchAvl(r->left, id); // check left branches trees recursively
    }
    return searchAvl(r->right, id); // check right branches trees recursively
}

void printAvl(Node<UserPair>* r) 
{ // output structural tables layout lines
    if (r != nullptr) 
    { // check tracking conditions bounds
        printAvl(r->left); // explore left branches trees recursively
        cout << r->data.id << "\t\t" << r->data.pass << endl; // write text data line outputs
        printAvl(r->right); // explore right branches trees recursively
    }
}

int main() 
{
    SystemHeap idHeap; // instantiate internal mockup heap system layout structures
    Node<UserPair>* passTree = nullptr; // initialize base user records avl pointer track
    int choice = 0; // allocate integer variable capturing numeric menu select option
    while (choice != 5)
    { // process input loops till termination codes matching five
        cout << "1 add user\n2 remove user\n3 search user\n4 display table\n5 exit\nchoice: "; // print option logs
        cin >> choice; // read input options choices selection parameters
        if (choice == 1) 
        { // insert item path execution block matching choice one
            string u, p; // allocate local working textual string buffers fields
            cout << "enter id: "; 
            cin >> u; // capture identity strings values parameters
            cout << "enter pass: "; 
            cin >> p; // capture passcode strings values parameters
            idHeap.addId(u); // push key string records inside internal index tracking blocks
            UserPair np = { u, p }; // create user pair record
            passTree = addAvl(passTree, np); // update matching relational links trees blocks
        }
        else if (choice == 2)
        { // processing item cleanup sequence path matching choice two
            string u; // declare target label tracking string holders
            cout << "enter id to remove: ";
            cin >> u; // acquire target labels characters codes
            idHeap.removeId(u); // clear index item inside heap array list trackers
            passTree = remAvl(passTree, u); // unlink structural reference pointers rows tracks records
        }
        else if (choice == 3) 
        { // lookup single credentials records block matching choice three
            string u; // configure working query name tag fields strings
            cout << "enter id to search: "; cin >> u; // parse target identity code lines string
            Node<UserPair>* res = searchAvl(passTree, u); // perform internal lookup searches routines
            if (res)
            {
                cout << "found password: " << res->data.pass << endl; // echo back matched items text string keys
            }
            else
            {
                cout << "user not found" << endl; // drop missing record error messages lines
            }
        }
        else if (choice == 4) 
        { // draw full tabular summary reports matching choice four
            cout << "userid\t\tpassword\n--------------------" << endl; // write clear summary chart columns headers
            printAvl(passTree); // render individual nested nodes attributes line details
        }
    }
    return 0; // close main program thread workflows execution
}