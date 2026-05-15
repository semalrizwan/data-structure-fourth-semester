/*
1. understanding:
need to find how deep the tree goes count all the nodes
inside it, count only the nodes that have no children make a second
copy of the tree in memory and display the values in a specific order

2. steps:
- to find height: find the height of left and right branches
pick the bigger number and add one for the current spot
- to count nodes: add one to the the results from
calling the same function on my left and right branches
- to count leaves: if there are no children return 1 if there are children
return the sum of leaves found in branches
- to copy: create a new node copy my data into it and then recursively
tell its left and right pointers to point to copies of the branches
- to display: visit the left branch then print data then visit
the right branch.

3. functions:
use the node class provided which contains data a left pointer and
a right pointer every function will call itself to move down the tree

4. learning:
trees are suited for recursion because every single
node acts like the root of its own smaller tree

5. skills:
 non-linear data structures and perform deep copies where
entire memory structures are duplicated instead of just pointers
*/

#include <iostream>
using namespace std;

template <class T>
class Node
{
public:
    T data; // holds the value
    Node* left; // pointer to left child
    Node* right; // pointer to right child
};

// 1. returns height of the tree
int height(Node<int>* treeRoot) 
{
    // if the tree is empty the height is zero
    if (treeRoot == nullptr)
    {
        return 0;
    }
    // get the height of the left side
    int leftH = height(treeRoot->left);
    // get the height of the right side
    int rightH = height(treeRoot->right); 
    // pick the larger height and add one for this level
    if (leftH > rightH)
    {
        return leftH + 1;
    }
    else
    {
        return rightH + 1;
    }
}

// 2. returns number of nodes in the tree
int countNodes(Node<int>* treeRoot)
{
    // if the spot is empty it counts as zero
    if (treeRoot == nullptr)
    {
        return 0;
    }
    // count this node plus everything below it
    return 1 + countNodes(treeRoot->left) + countNodes(treeRoot->right); 
}

// 3. returns number of leaf nodes 
int countLeaves(Node<int>* treeRoot)
{
    // if empty there are no leaves
    if (treeRoot == nullptr)
    {
        return 0;
    }
    // if there are no children this is a leaf
    if (treeRoot->left == nullptr && treeRoot->right == nullptr)
    {
        return 1;
    }
    // otherwise look for leaves in the branches
    return countLeaves(treeRoot->left) + countLeaves(treeRoot->right); 
}

// 4. returns a deep copy of the tree
Node<int>* copyTree(Node<int>* treeRoot)
{
    // if there is nothing to copy return null
    if (treeRoot == nullptr)
    {
        return nullptr;
    }
    // create a new node in the system memory
    Node<int>* newNode = new Node<int>();
    // copy the value from the original node
    newNode->data = treeRoot->data; 
    // recursively copy the left and right branches
    newNode->left = copyTree(treeRoot->left); 
    newNode->right = copyTree(treeRoot->right); 
    // return the new node to the caller
    return newNode; 
}

// 5. display all tree nodes using inorder traversal (left, root, right)
void inorderDisplay(Node<int>* root)
{
    // stop if we hit an empty spot
    if (root == nullptr)
    {
        return;
    }
    // visit the left branch first
    inorderDisplay(root->left); 
    // print the data in the middle
    cout << root->data << " "; 
    // visit the right branch last
    inorderDisplay(root->right); 
}

int main() 
{
    // create a simple tree for testing
    Node<int>* root = new Node<int>(); 
    root->data = 50; 
    root->left = nullptr; 
    root->right = nullptr; 

    // add a left child
    root->left = new Node<int>(); 
    root->left->data = 30; 
    root->left->left = nullptr; 
    root->left->right = nullptr; 

    // add a right child
    root->right = new Node<int>(); 
    root->right->data = 70; 
    root->right->left = nullptr; 
    root->right->right = nullptr; 

    // test the height function
    cout << "tree height is: " << height(root) << endl; 
    // test the node counting function
    cout << "total nodes: " << countNodes(root) << endl; 
    // test the leaf counting function
    cout << "total leaves: " << countLeaves(root) << endl; 

    // test the display function
    cout << "inorder display: "; 
    inorderDisplay(root); 
    cout << endl; 

    // test the copy function
    Node<int>* secondTree = copyTree(root); 
    cout << "copy inorder display: "; 
    inorderDisplay(secondTree); 
    cout << endl; 

    // clean up memory
    return 0; 
}