/*
understanding of the task:
three global functions that process binary search trees split breaks down a tree into smaller left and right segmens
insert takes another entire tree object and transfers all its elements into a destination tree
deletetreefromnode cuts off and deletes a whole subtree based on a selected value match

how to do the task and the solution steps:
1. for split function if the primary tree is not empty we extract data values from its left pointer nodes into btleft and data values
from its right pointer structural nodes into btright

2. for insert function we traverse the secondary tree using an inorder technique and continuously invoke the tree insert process inside the primary tree 

3. for deletetreefromnode function we track down the specific node that contains the targeted keyword item data once located
we delete all child paths connected to that node

learning from the task:
how to treat separate complete class structures as single entities and modify them using references

skills developed:
object parsing mechanisms and subtree extraction skills without producing errors
*/

#include <iostream>
#include "Node.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"

using namespace std;

// copy implementations from task 2
template <class T> void destroyTreeHelper(Node<T>* node) 
{
    if (node != nullptr) 
    {
        destroyTreeHelper(node->left);
        destroyTreeHelper(node->right);
        delete node;
    }
}
template <class T> void BinaryTree<T>::deleteTree() 
{
    destroyTreeHelper(root); root = nullptr; 
}
template <class T> Node<T>* copyTreeHelper(const Node<T>* otherNode)
{
    if (otherNode == nullptr)
    {
        return nullptr;
    }
    Node<T>* newNode = new Node<T>();
    newNode->data = otherNode->data;
    newNode->left = copyTreeHelper(otherNode->left);
    newNode->right = copyTreeHelper(otherNode->right);
    return newNode;
}
template <class T> void BinaryTree<T>::copyTree(const BinaryTree<T>* otherTree) 
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
template <class T> const BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& other) 
{
    if (this != &other) 
    {
        deleteTree(); 
        copyTree(&other); 
    } 
    return *this;
}
template <class T> int heightHelper(Node<T>* node)
{
    if (node == nullptr)
    {
        return 0;
    }
    int l = heightHelper(node->left);
    int r = heightHelper(node->right);
    return (l > r ? l : r) + 1;
}
template <class T> int BinaryTree<T>::treeHeight() const 
{
    return heightHelper(root);
}
template <class T> int countNodesHelper(Node<T>* node) 
{
    return node == nullptr ? 0 : 1 + countNodesHelper(node->left) + countNodesHelper(node->right);
}
template <class T> int BinaryTree<T>::treeNodeCount() const 
{
    return countNodesHelper(root);
}
template <class T> int countLeavesHelper(Node<T>* node)
{
    if (node == nullptr)
    {
        return 0;
    }
    if (node->left == nullptr && node->right == nullptr)
    {
        return 1;
    }
    return countLeavesHelper(node->left) + countLeavesHelper(node->right);
}
template <class T> int BinaryTree<T>::treeLeavesCount() const 
{
    return countLeavesHelper(root);
}
template <class T> const BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree<T>& other)
{
    if (this != &other)
    {
        this->deleteTree(); 
        this->copyTree(&other);
    }
    return *this;
}
template <class T> void insertHelper(Node<T>*& node, const T& value) 
{
    if (node == nullptr) 
    {
        node = new Node<T>(); 
        node->data = value;
        node->left = node->right = nullptr; 
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
template <class T> void BinarySearchTree<T>::insert(const T& value)
{
    insertHelper(this->root, value); 
}
template <class T> void removeHelper(Node<T>*& node, const T& value)
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
        if (node->left == nullptr && node->right == nullptr) 
        {
            delete node; node = nullptr; 
        }
        else if (node->left == nullptr) 
        {
            Node<T>* t = node; node = node->right; delete t; 
        }
        else if (node->right == nullptr)
        {
            Node<T>* t = node;
            node = node->left;
            delete t;
        }
        else 
        {
            Node<T>* t = node->right; 
            while (t->left != nullptr)
            {
                t = t->left;
            }
            node->data = t->data; 
            removeHelper(node->right, t->data);
        }
    }
}
template <class T> void BinarySearchTree<T>::remove(const T& value) 
{
    removeHelper(this->root, value); 
}
template <class T> bool searchHelper(Node<T>* node, const T& value) 
{
    if (node == nullptr)
    {
        return false;
    }
    if (node->data == value)
    {
        return true;
    }
    return value < node->data ? searchHelper(node->left, value) : searchHelper(node->right, value);
}
template <class T> bool BinarySearchTree<T>::search(const T& value) const 
{
    return searchHelper(this->root, value); 
}
template <class T> bool BinarySearchTree<T>::isEmpty() const
{
    return this->root == nullptr;
}
template <class T> void displayInorder(Node<T>* node) 
{
    if (node != nullptr) 
    { 
        displayInorder(node->left);
        cout << node->data << " ";
        displayInorder(node->right);
    }
}
template <class T> void BinarySearchTree<T>::display() const 
{
    displayInorder(this->root);
    cout << endl; 
}
template <class T> void BinaryTree<T>::inorderDisplay() const {}
template <class T> void BinaryTree<T>::preorderDisplay() const {}
template <class T> void BinaryTree<T>::postorderDisplay() const {}

// recursive helper to copy splits into tree
template <class T>
void populateTree(Node<T>* sourceNode, BinarySearchTree<T>& targetTree)
{
    if (sourceNode != nullptr)
    {
        // insert current data element into target tree 
        targetTree.insert(sourceNode->data);
        // traverse left branches
        populateTree(sourceNode->left, targetTree);
        // traverse right branches
        populateTree(sourceNode->right, targetTree);
    }
}

// splits a search tree completely into isolated left and right branch 
template <class T>
void split(BinarySearchTree<T> bt, BinarySearchTree<T>& btLeft, BinarySearchTree<T>& btRight) 
{
    // navigate tree elements from root position
    Node<T>* rootNode = bstPrivateAccess::getRoot(bt);
    if (rootNode == nullptr)
    {
        return;
    }
    // pull items on left components into sub trees
    if (rootNode->left != nullptr) 
    {
        populateTree(rootNode->left, btLeft);
    }
    // pull items on right components into sub trees
    if (rootNode->right != nullptr) 
    {
        populateTree(rootNode->right, btRight);
    }
}

// helper routine to insert all elements from source node to target tree
template <class T>
void insertTreeHelper(Node<T>* nodeToCopy, BinarySearchTree<T>& destinationTree)
{
    if (nodeToCopy != nullptr)
    {
        destinationTree.insert(nodeToCopy->data);
        insertTreeHelper(nodeToCopy->left, destinationTree);
        insertTreeHelper(nodeToCopy->right, destinationTree);
    }
}

template <class T>
void insert(BinarySearchTree<T>& bt, BinarySearchTree<T> toInsert) 
{
    Node<T>* sourceRoot = bstPrivateAccess::getRoot(toInsert);
    insertTreeHelper(sourceRoot, bt);
}

// recursive helper function to delete target child
template <class T>
Node<T>* pruneSubtree(Node<T>* node, const T& value)
{
    if (node == nullptr) 
    {
        return nullptr;
    }
    if (node->data == value)
    {
        // match confirmed
        destroyTreeHelper(node);
        return nullptr;
    }
    if (value < node->data)
    {
        node->left = pruneSubtree(node->left, value);
    }
    else 
    {
        node->right = pruneSubtree(node->right, value);
    }
    return node;
}

// erases all deeper child 
template <class T>
void deleteTreeFromNode(BinarySearchTree<T>& bt, const T& value)
{
    Node<T>* rootNode = bstPrivateAccess::getRoot(bt);
    rootNode = pruneSubtree(rootNode, value);
    bstPrivateAccess::setRoot(bt, rootNode);
}


int main() 
{
    BinarySearchTree<int> mainTree;
    mainTree.insert(50);
    mainTree.insert(30);
    mainTree.insert(70);
    mainTree.insert(20);
    mainTree.insert(40);

    cout << "main baseline tree: ";
    mainTree.display();

    BinarySearchTree<int> leftSub;
    BinarySearchTree<int> rightSub;

    // test split operations
    split(mainTree, leftSub, rightSub);
    cout << "extracted left sub-tree: ";
    leftSub.display();
    cout << "extracted right sub-tree: ";
    rightSub.display();

    // test subtree deletion operation
    cout << "deleting all subtree nodes starting from value 30..." << endl;
    deleteTreeFromNode(mainTree, 30);
    cout << "main tree after subtree pruning: ";
    mainTree.display();

    return 0;
}