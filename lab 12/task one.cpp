/*
understanding of the task:
we cannot use recursion here we need to implement search, add value, find node, find next larger node, and delete a single node. 
the functions must take a pointer to node as a parameter

how to do the task and the solution steps:
1. for search we will start at the root node while the current node is not null we check if the value matches
if it is smaller we move to the left child. if it is larger we move to the right child

2. for addvalue we will use a trailing pointer to keep track of the parent node we go down the tree until we hit a null spot
then attach the new node to the left or right of the parent

3. for find node it is identical to search but instead of returning true or false we return the pointer to the node itself if found
or null if not found

4. for find next larger node if the node has a right subtree we find the minimum value in that right subtree if it does not have a right subtree
we start from the root and follow the path down to the node keeping track of the last time we turned left

5. for delete node we handle three cases node with no children, node with one child, and node with two children
if it has two children we find its inorder and copy its data and then iteratively delete that successor node

functions to reuse and why:
we can reuse the find node function inside our next larger value or delete logic to safely locate nodes if needed
reducing redundant search iterations

learning from the task:
how to navigate a binary search tree using simple loops instead of recursive calls 

skills developed:
solve complex data arrangement problems without relying on recursive memory overhead
*/

#include <iostream>
#include "Node.h"

using namespace std;

// iterative function to search for a value in the tree
template <class T>
bool search(Node<T>* root, T value) 
{
    // start loop from the root node and run until we hit null
    while (root != nullptr) 
    {
        // if the current node data is equal to the value return true
        if (root->data == value) 
        {
            return true;
        }
        // if the target value is smaller move to the left child
        else if (value < root->data)
        {
            root = root->left;
        }
        // if the target value is larger move to the right child
        else 
        {
            root = root->right;
        }
    }
    // if loop ends without finding the value return false
    return false;
}

// iterative function to add a value into the tree
template <class T>
void addValue(Node<T>*& root, T value) 
{
    // create a new node dynamically using the node structure
    Node<T>* newNode = new Node<T>();
    // set the data of the new node to the value passed
    newNode->data = value;
    // initialize left child pointer of new node to null
    newNode->left = nullptr;
    // initialize right child pointer of new node to null
    newNode->right = nullptr;

    // if the tree is completely empty make the new node the root
    if (root == nullptr) 
    {
        root = newNode;
        return;
    }

    // pointer to traverse the tree starting from root
    Node<T>* current = root;
    // pointer to keep track of the parent node of current
    Node<T>* parent = nullptr;

    // loop to find the correct location for insertion
    while (current != nullptr)
    {
        // update parent to be the current node
        parent = current;
        // if the value is smaller go to the left subtree
        if (value < current->data) 
        {
            current = current->left;
        }
        // if the value is larger or equal go to the right subtree
        else
        {
            current = current->right;
        }
    }

    // link the new node to the parent node based on value comparison
    if (value < parent->data) 
    {
        // if value is smaller link it as the left child
        parent->left = newNode;
    }
    else {
        // if value is larger link it as the right child
        parent->right = newNode;
    }
}

// iterative function to find and return the node containing a specific value
template <class T>
Node<T>* find(Node<T>* root, T value) 
{
    // run loop until root becomes null
    while (root != nullptr) 
    {
        // if data matches, return this node pointer
        if (root->data == value) 
        {
            return root;
        }
        // if value is smaller, move to left child
        else if (value < root->data) 
        {
            root = root->left;
        }
        // if value is larger, move to right child
        else 
        {
            root = root->right;
        }
    }
    // return null if node is not found in the tree
    return nullptr;
}

// iterative function to find the node containing next larger data 
template <class T>
Node<T>* findNextLarger(Node<T>* root, T value) 
{
    // find the target node first using an iterative look up
    Node<T>* current = find(root, value);
    // if the target node does not exist in the tree, return null
    if (current == nullptr) 
    {
        return nullptr;
    }

    // case 1: if the node has a right child successor is the leftmost node in right subtree
    if (current->right != nullptr)
    {
        // move to the right child
        Node<T>* successor = current->right;
        // loop down to find the leftmost deepest leaf
        while (successor->left != nullptr)
        {
            successor = successor->left;
        }
        // return that leftmost node
        return successor;
    }

    // case 2: if there is no right child search from the root down to the target node
    Node<T>* successor = nullptr;
    Node<T>* ancestor = root;
    // loop until we reach the target node location
    while (ancestor != current) 
    {
        // if value is smaller than ancestor, ancestor could be a successor
        if (current->data < ancestor->data) 
        {
            // save this ancestor as potential successor
            successor = ancestor;
            // move left to see if there is a closer successor
            ancestor = ancestor->left;
        }
        else 
        {
            // if value is greater move right without updating successor
            ancestor = ancestor->right;
        }
    }
    // return the tracked successor node
    return successor;
}

// iterative function to delete a single given node from the tree
template <class T>
void deleteNode(Node<T>*& root, T value) 
{
    // initialize current pointer to root
    Node<T>* current = root;
    // initialize parent pointer to null
    Node<T>* parent = nullptr;

    // loop to locate the node to delete and its parent
    while (current != nullptr && current->data != value) 
    {
        // update parent pointer
        parent = current;
        // move left or right depending on the value
        if (value < current->data) 
        {
            current = current->left;
        }
        else 
        {
            current = current->right;
        }
    }

    // if node to delete is not found exit function
    if (current == nullptr) 
    {
        return;
    }

    // case 1 and case 2: node has zero or one child
    if (current->left == nullptr || current->right == nullptr) 
    {
        // pointer to hold the existing single child or null
        Node<T>* newChild = nullptr;
        if (current->left != nullptr)
        {
            newChild = current->left;
        }
        else
        {
            newChild = current->right;
        }

        // if parent is null we are deleting the root node
        if (parent == nullptr) 
        {
            root = newChild;
        }
        // if current is left child of parent, relink parent left to new child
        else if (current == parent->left) 
        {
            parent->left = newChild;
        }
        // if current is right child of parent, relink parent right to new child
        else 
        {
            parent->right = newChild;
        }
        // free memory of the deleted node
        delete current;
    }
    // case 3: node has two children
    else
    {
        // find the inorder successor (leftmost node in right subtree)
        Node<T>* succParent = current;
        Node<T>* successor = current->right;
        // track down the leftmost child
        while (successor->left != nullptr)
        {
            succParent = successor;
            successor = successor->left;
        }

        // copy data of successor node into current node
        current->data = successor->data;

        // link successor child to successor parent
        if (succParent->left == successor) 
        {
            succParent->left = successor->right;
        }
        else 
        {
            succParent->right = successor->right;
        }
        // delete the successor node
        delete successor;
    }
}

// simple iterative inorder display to verify results
template <class T>
void printTree(Node<T>* root) 
{
    if (root == nullptr)
    {
        return;
    }
    printTree(root->left);
    cout << root->data << " ";
    printTree(root->right);
}

int main() 
{
    // initialize empty root pointer
    Node<int>* root = nullptr;

    // add values iteratively
    addValue(root, 50);
    addValue(root, 30);
    addValue(root, 70);
    addValue(root, 20);
    addValue(root, 40);
    addValue(root, 60);
    addValue(root, 80);

    cout << "tree values: ";
    printTree(root);
    cout << endl;

    // test search function
    cout << "search 40: " << (search(root, 40) ? "found" : "not found") << endl;
    cout << "search 90: " << (search(root, 90) ? "found" : "not found") << endl;

    // test find node function
    Node<int>* foundNode = find(root, 30);
    if (foundNode != nullptr) {
        cout << "found node contains: " << foundNode->data << endl;
    }

    // test find next larger function
    Node<int>* nextLarger = findNextLarger(root, 40);
    if (nextLarger != nullptr) {
        cout << "next larger value after 40 is: " << nextLarger->data << endl;
    }

    // test delete function
    cout << "deleting node 30..." << endl;
    deleteNode(root, 30);
    cout << "tree values after deletion: ";
    printTree(root);
    cout << endl;

    return 0;
}