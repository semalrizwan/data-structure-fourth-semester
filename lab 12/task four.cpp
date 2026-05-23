/*
understanding of the task:
binarysearchtree storing string values to read a plain paragraph from an external text file

how to do the task and the solution steps:
1. create an ifstream object linked to para.txt file to extract raw string characters word by word

2. feed individual parsed text elements into our binary search tree object

3. input simple string queries, perform search operations and change characters into uppercase using standard
looping mechanics

functions to reuse and why:
 basic stream functions alongside binary search tree insert and remove implementations 

learning from the task:
 how text data merge cleanly with binary structures

skills developed:
file stream management skills with binary tree
*/

#include <iostream>
#include <fstream>
#include <string>
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
    destroyTreeHelper(root);
    root = nullptr;
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
            Node<T>* t = node; 
            node = node->right;
            delete t; 
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
    }if (node->data == value)
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


int main() 
{
    
    BinarySearchTree<string> tree;

    // open file pointer path to extract source paragraph text
    ifstream file("para.txt");
    if (!file) 
    {
        cout << "error opening para.txt file container context" << endl;
        return 1;
    }

    string word;
    // extract individual word items 
    while (file >> word)
    {
        tree.insert(word);
    }
    file.close();

    // display
    cout << "sentences loaded inside tracking tree: ";
    tree.display();

    // specific word and conversion
    cout << "\nenter an english word to search: ";
    string searchWord;
    cin >> searchWord;

    if (tree.search(searchWord))
    {
        cout << "word found inside dataset structure." << endl;
        // loop through and convert word characters to uppercase
        for (int i = 0; i < searchWord.length(); i++) 
        {
            if (searchWord[i] >= 'a' && searchWord[i] <= 'z') 
            {
                searchWord[i] = searchWord[i] - 32;
            }
        }
        cout << "uppercase text transformation result: " << searchWord << endl;
    }
    else 
    {
        cout << "word does not exist inside current storage tree nodes." << endl;
    }

    // test a
    cout << "\nenter a word to insert: ";
    string insertWord;
    cin >> insertWord;
    tree.insert(insertWord);
    cout << "updated search tree components display: ";
    tree.display();

    // test deletion 
    cout << "\nenter a word to delete from the tracking tree structural space: ";
    string deleteWord;
    cin >> deleteWord;
    tree.remove(deleteWord);
    cout << "final modified search tree components tracking layout: ";
    tree.display();

    return 0;
}