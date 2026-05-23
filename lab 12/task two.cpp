/*
understanding of the task:
 fully implement the public functions specified in the binarysearchtree class

how to do the task and the solution steps:
1. we write the helper recursive functions for inserting, removing, and searching values because the binarysearchtree class functions must 
interface with the internal root pointer

2. the insert function will check if root is null, create a node, or pass the request down based on left or right values

3. the remove function handles the three primary deletion states of structural nodes

4. treeheight, treenodecount, and treeleavescount will traverse the child pointers to calculate and return aggregate metric counts

5. assignment operator will clear the existing left and right branches and duplicate the target tree object completely

functions to reuse and why:
 reuse private recursive functions like deletetree inside the destructor and assignment operator to safely release heap allocations 
 without replicating the teardown code block

learning from the task:
class structures wrap around node structures. using recursive functions 

skills developed:
inheritance structures, pure virtual method resolution, and tracking inside dynamic binary tree
*/

#include <iostream>
#include "Node.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"

using namespace std;

// recursive helper function to safely delete all nodes from a tree root
template <class T>
void destroyTreeHelper(Node<T>* node)
{
    if (node != nullptr)
    {
        // delete left subtree recursively
        destroyTreeHelper(node->left);
        // delete right subtree recursively
        destroyTreeHelper(node->right);
        // free memory of current node
        delete node;
    }
}

// deletes the entire tree structure to clear memory
template <class T>
void BinaryTree<T>::deleteTree() 
{
    destroyTreeHelper(root);
    root = nullptr;
}

// recursive helper function to copy nodes from one tree structure to another
template <class T>
Node<T>* copyTreeHelper(const Node<T>* otherNode) 
{
    if (otherNode == nullptr)
    {
        return nullptr;
    }
    // allocate a new node structure in memory
    Node<T>* newNode = new Node<T>();
    newNode->data = otherNode->data;
    // copy left sub branch structures
    newNode->left = copyTreeHelper(otherNode->left);
    // copy right sub branch structures
    newNode->right = copyTreeHelper(otherNode->right);
    return newNode;
}

// copies the data tree structure from a source tree object
template <class T>
void BinaryTree<T>::copyTree(const BinaryTree<T>* otherTree) 
{
    if (otherTree != nullptr) 
    {
        root = copyTreeHelper(otherTree->root);
    }
    else 
    {
        root = nullptr;
    }
}

// assignment operator overloaded for base binary tree class objects
template <class T>
const BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& other) 
{
    if (this != &other)
    {
        // clear old memory structure
        deleteTree();
        // duplicate tracking path nodes
        copyTree(&other);
    }
    return *this;
}

// recursive helper function to determine height of tree node structure
template <class T>
int heightHelper(Node<T>* node)
{
    if (node == nullptr)
    {
        return 0;
    }
    int leftH = heightHelper(node->left);
    int rightH = heightHelper(node->right);
    // return greater path height plus one for current level
    if (leftH > rightH) 
    {
        return leftH + 1;
    }
    else 
    {
        return rightH + 1;
    }
}

// returns total height of current tree 
template <class T>
int BinaryTree<T>::treeHeight() const 
{
    return heightHelper(root);
}

// recursive helper to count nodes within tree
template <class T>
int countNodesHelper(Node<T>* node) 
{
    if (node == nullptr)
    {
        return 0;
    }
    // add self to sum of node structures on left and right sides
    return 1 + countNodesHelper(node->left) + countNodesHelper(node->right);
}

// returns overall number count of nodes 
template <class T>
int BinaryTree<T>::treeNodeCount() const 
{
    return countNodesHelper(root);
}

// recursive helper to look up leaf nodes that have zero child
template <class T>
int countLeavesHelper(Node<T>* node)
{
    if (node == nullptr) 
    {
        return 0;
    }
    if (node->left == nullptr && node->right == nullptr) 
    {
        return 1;
    }
    // return combined leaves counted inside sub branches
    return countLeavesHelper(node->left) + countLeavesHelper(node->right);
}

// returns total leaf items inside binary tree structure
template <class T>
int BinaryTree<T>::treeLeavesCount() const 
{
    return countLeavesHelper(root);
}


// assignment operator for binary search tree objects
template <class T>
const BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree<T>& other)
{
    if (this != &other) 
    {
        // base function deletion
        this->deleteTree();
        // copy
        this->copyTree(&other);
    }
    return *this;
}

// recursive helper to handle insertions inside search
template <class T>
void insertHelper(Node<T>*& node, const T& value)
{
    if (node == nullptr) 
    {
        node = new Node<T>();
        node->data = value;
        node->left = nullptr;
        node->right = nullptr;
    }
    else if (value < node->data)
    {
        insertHelper(node->left, value);
    }
    else
    {
        insertHelper(node->right, value);
    }
}

// inserts specific element values into positions
template <class T>
void BinarySearchTree<T>::insert(const T& value) 
{
    insertHelper(this->root, value);
}

// recursive helper that deletes individual nodes
template <class T>
void removeHelper(Node<T>*& node, const T& value)
{
    if (node == nullptr) 
    {
        return;
    }
    if (value < node->data) 
    {
        removeHelper(node->left, value);
    }
    else if (value > node->data)
    {
        removeHelper(node->right, value);
    }
    else 
    {
        // target node
        if (node->left == nullptr && node->right == nullptr) 
        {
            delete node;
            node = nullptr;
        }
        else if (node->left == nullptr)
        {
            Node<T>* temp = node;
            node = node->right;
            delete temp;
        }
        else if (node->right == nullptr) 
        {
            Node<T>* temp = node;
            node = node->left;
            delete temp;
        }
        else 
        {
            // node with multiple child
            Node<T>* temp = node->right;
            while (temp->left != nullptr) 
            {
                temp = temp->left;
            }
            node->data = temp->data;
            removeHelper(node->right, temp->data);
        }
    }
}

// removes chosen item attributes
template <class T>
void BinarySearchTree<T>::remove(const T& value) 
{
    removeHelper(this->root, value);
}

// recursive helper for validation 
template <class T>
bool searchHelper(Node<T>* node, const T& value)
{
    if (node == nullptr)
    {
        return false;
    }
    if (node->data == value) 
    {
        return true;
    }
    else if (value < node->data)
    {
        return searchHelper(node->left, value);
    }
    else 
    {
        return searchHelper(node->right, value);
    }
}

// looks up target data
template <class T>
bool BinarySearchTree<T>::search(const T& value) const 
{
    return searchHelper(this->root, value);
}

// returns validation
template <class T>
bool BinarySearchTree<T>::isEmpty() const 
{
    return this->root == nullptr;
}

// inordee
template <class T>
void displayInorder(Node<T>* node)
{
    if (node != nullptr)
    {
        displayInorder(node->left);
        cout << node->data << " ";
        displayInorder(node->right);
    }
}

// outputs 
template <class T>
void BinarySearchTree<T>::display() const 
{
    displayInorder(this->root);
    cout << endl;
}

// implementing abstract functions
template <class T> void BinaryTree<T>::inorderDisplay() const {}
template <class T> void BinaryTree<T>::preorderDisplay() const {}
template <class T> void BinaryTree<T>::postorderDisplay() const {}

int main()
{
    // create object
    BinarySearchTree<int> bst;

    // add information 
    bst.insert(45);
    bst.insert(25);
    bst.insert(65);
    bst.insert(15);
    bst.insert(35);

    cout << "tree data: ";
    bst.display();

    cout << "total internal node count: " << bst.treeNodeCount() << endl;
    cout << "calculated depth height metrics: " << bst.treeHeight() << endl;
    cout << "tracked total dynamic leaves: " << bst.treeLeavesCount() << endl;

    // test removal functions
    cout << "removing value 25 from data structure..." << endl;
    bst.remove(25);
    cout << "updated tree content values: ";
    bst.display();

    return 0;
}