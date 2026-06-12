#include <iostream>
#include "Node.h"

using namespace std;

/*
1. what i understand about the task
this task requires us to implement an avl tree with functions for height balance balance type left rotation right rotation and insertions or deletions for both regular bst and avl trees

2. how i will do the task
i will use recursion to calculate heights and check balance factors if an imbalance happens i will use single or double rotations to fix it based on the balance type values

3. functions reused
height is used inside balance balance is used inside insert and delete rightrotate and leftrotate are used inside insert and delete to rebalance the tree structure after changes
progression of tree nodes can be seen as parent right child right grand child before left rotation and parent becomes left child of right child after left rotation
*/

// function to calculate the height of a node
template <class T>
int height(Node<T>* root)
{
    if (root == nullptr) // if node is null height is zero
    {
        return 0; // return zero for empty tree
    }
    int leftHeight = height(root->left); // recursively get height of left subtree
    int rightHeight = height(root->right); // recursively get height of right subtree
    return 1 + max(leftHeight, rightHeight); // return one plus the maximum of left or right height
}

// function to calculate balance factor of a node
template <class T>
int balance(Node<T>* root)
{
    if (root == nullptr) // if node is null balance is zero
    {
        return 0; // return zero because it is balanced
        return height(root->left) - height(root->right); // subtract right height from left height
    }
}

// function to check type of imbalance after adding a new value
template <class T>
int balanceType(Node<T>* parent, T newValue) 
{
    if (parent == nullptr) // if parent is null there is no imbalance
    {
        return 0; // return zero for balanced
    }
    int bf = balance(parent); // get balance factor of parent
    if (bf > 1 && newValue < parent->left->data) // check if left left case happens
    {
        return 1; // return one for left left imbalance
    }
    if (bf < -1 && newValue > parent->right->data) // check if right right case happens
    {
        return 2; // return two for right right imbalance
    }
    if (bf > 1 && newValue > parent->left->data) // check if left right case happens
    {
        return 3; // return three for left right imbalance
    }
    if (bf < -1 && newValue < parent->right->data) // check if right left case happens
    {
        return 4; // return four for right left imbalance
    }
    return 0; // return zero if tree is balanced
}

// function to perform a left rotation
template <class T>
Node<T>* leftRotate(Node<T>* root)
{
    if (root == nullptr || root->right == nullptr) // check if rotation is possible
    {
        return root; // return root if rotation cannot be done
    }
    Node<T>* rightChild = root->right; // store right child of root
    Node<T>* leftOfRightChild = rightChild->left; // store left child of right child
    rightChild->left = root; // make original root the left child of right child
    root->right = leftOfRightChild; // assign the left child to root right pointer
    return rightChild; // return new root after rotation
}

// function to perform a right rotation
template <class T>
Node<T>* rightRotate(Node<T>* root)
{
    if (root == nullptr || root->left == nullptr) // check if rotation is possible
    {
        return root; // return root if rotation cannot be done
    }
    Node<T>* leftChild = root->left; // store left child of root
    Node<T>* rightOfLeftChild = leftChild->right; // store right child of left child
    leftChild->right = root; // make original root the right child of left child
    root->left = rightOfLeftChild; // assign the right child to root left pointer
    return leftChild; // return new root after rotation
}

// function to insert a node into standard bst
template <class T>
Node<T>* bstInsert(Node<T>* root, T value) 
{
    if (root == nullptr) 
    { // check if tree or subtree is empty
        Node<T>* newNode = new Node<T>(); // allocate space for new node
        newNode->data = value; // set data to new value
        newNode->left = nullptr; // set left child to null
        newNode->right = nullptr; // set right child to null
        return newNode; // return newly created node
    }
    if (value < root->data) // check if value belongs in left subtree
    {
        root->left = bstInsert(root->left, value); // recursively insert into left side
    }
    else if (value > root->data) // check if value belongs in right subtree
    {
        root->right = bstInsert(root->right, value); // recursively insert into right side
    }
    return root; // return unmodified root pointer
}

// function to insert a value into avl tree and keep it balanced
template <class T>
Node<T>* insert(Node<T>* root, T value)
{
    if (root == nullptr)
    { // check if tree or subtree is empty
        Node<T>* newNode = new Node<T>(); // allocate space for new node
        newNode->data = value; // set data to new value
        newNode->left = nullptr; // set left pointer to null
        newNode->right = nullptr; // set right pointer to null
        return newNode; // return the new node
    }
    if (value < root->data) // check if value is smaller than root data
    {
        root->left = insert(root->left, value); // recursively insert left
    }
    else if (value > root->data) // check if value is greater than root data
    {
        root->right = insert(root->right, value); // recursively insert right
    }
    else // if value already exists
    {
        return root; // do nothing and return root
    }
    int bType = balanceType(root, value); // find out type of imbalance at current root
    if (bType == 1) // left left imbalance case
    {
        return rightRotate(root); // fix with single right rotation
    }
    if (bType == 2) // right right imbalance case
    {
        return leftRotate(root); // fix with single left rotation
    }
    if (bType == 3)
    { // left right imbalance case
        root->left = leftRotate(root->left); // do left rotation on left child first
        return rightRotate(root); // then do right rotation on current root
    }
    if (bType == 4)
    { // right left imbalance case
        root->right = rightRotate(root->right); // do right rotation on right child first
        return leftRotate(root); // then do left rotation on current root
    }
    return root; // return current node pointer
}

// function to delete a node from standard bst
template <class T>
Node<T>* bstDelete(Node<T>* n, T value) 
{
    if (n == nullptr) // check if node is null
    {
        return n; // return null pointer
    }
    if (value < n->data) // check if value is in left subtree
    {
        n->left = bstDelete(n->left, value); // search and delete in left child
    }
    else if (value > n->data) // check if value is in right subtree
    {
        n->right = bstDelete(n->right, value); // search and delete in right child
    }
    else 
    { // found node to delete
        if (n->left == nullptr || n->right == nullptr)
        { // node has one or zero children
            Node<T>* temp = n->left ? n->left : n->right; // pick the non null child if any
            if (temp == nullptr) 
            { // zero children case
                temp = n; // point temp to current node
                n = nullptr; // set current node pointer to null
            }
            else // one child case
            {
                *n = *temp; // copy data of child to current node
            }
            delete temp; // delete the old node memory
        }
        else 
        { // node has two children case
            Node<T>* current = n->right; // look for minimum in right subtree
            while (current->left != nullptr) // loop until leftmost leaf is found
            {
                current = current->left; // move to left child
            }
            Node<T>* temp = current; // save inorder successor node
            n->data = temp->data; // copy successor data to current node
            n->right = bstDelete(n->right, temp->data); // delete successor from right subtree
        }
    }
    return n; // return modified node pointer
}

// function to delete a value from avl tree and maintain balance
template <class T>
Node<T>* deleteNode(Node<T>* root, T value) 
{
    if (root == nullptr) // check if tree is empty
    {
        return root; // return null pointer
    }
    if (value < root->data) // check if value is in left subtree
    {
        root->left = deleteNode(root->left, value); // recursively delete from left side
    }
    else if (value > root->data) // check if value is in right subtree
    {
        root->right = deleteNode(root->right, value); // recursively delete from right side
    }
    else 
    { // found node to delete
        if (root->left == nullptr || root->right == nullptr) 
        { // one or zero children case
            Node<T>* temp = root->left ? root->left : root->right; // get existing child
            if (temp == nullptr) 
            { // zero children case
                temp = root; // store current node in temp
                root = nullptr; // set root to null
            }
            else // one child case
                *root = *temp; // copy contents of child node
            delete temp; // delete memory from heap
        }
        else
        { // two children case
            Node<T>* current = root->right; // find inorder successor
            while (current->left != nullptr) // trace down to leftmost child
                current = current->left; // update current pointer
            Node<T>* temp = current; // hold inorder successor
            root->data = temp->data; // replace root data with successor data
            root->right = deleteNode(root->right, temp->data); // remove successor node
        }
    }
    if (root == nullptr) // if tree had only one node and now empty
    {
        return root; // return null
    }
    int bf = balance(root); // check balance factor after deletion
    if (bf > 1 && balance(root->left) >= 0) // left left imbalance case
    {
        return rightRotate(root); // fix with single right rotation
    }
    if (bf > 1 && balance(root->left) < 0) 
    { // left right imbalance case
        root->left = leftRotate(root->left); // rotate left child first
        return rightRotate(root); // rotate root right next
    }
    if (bf < -1 && balance(root->right) <= 0) // right right imbalance case
    {
        return leftRotate(root); // fix with single left rotation
    }
    if (bf < -1 && balance(root->right) > 0) 
    { // right left imbalance case
        root->right = rightRotate(root->right); // rotate right child first
        return leftRotate(root); // rotate root left next
    }
    return root; // return updated root pointer
}

int main() 
{
    Node<int>* avlRoot = nullptr; // start with an empty avl tree root
    cout << "inserting elements 10 20 30 into avl tree" << endl; // status message
    avlRoot = insert(avlRoot, 10); // insert ten into avl tree
    avlRoot = insert(avlRoot, 20); // insert twenty causes left rotation
    avlRoot = insert(avlRoot, 30); // insert thirty into avl tree
    cout << "root data after avl insert is " << avlRoot->data << endl; // should be twenty due to balance
    avlRoot = deleteNode(avlRoot, 10); // test deletion of ten
    cout << "root data after deleting 10 is " << avlRoot->data << endl; // display new root data
    return 0; // exit main successfully
}