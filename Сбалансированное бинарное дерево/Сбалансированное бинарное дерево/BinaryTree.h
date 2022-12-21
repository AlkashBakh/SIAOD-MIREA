//
//  BinaryTree.h
//  5_Сбалансированное бинарное дерево
//
//  Created by Хто Я on 22.10.2022.
//

#ifndef BinaryTree_h
#define BinaryTree_h

#include <iostream>

using namespace std;

class BST
{
public:
    struct BSTNode
    {
        string data;
        int fileNumber;
        BSTNode* left;
        BSTNode* right;
    };

private:
    BSTNode* root;

    BSTNode* makeEmpty(BSTNode* t)
    {
        if(t == NULL)
            return NULL;
        else
        {
            makeEmpty(t -> left);
            makeEmpty(t -> right);
            delete t;
        }
        return NULL;
    }

    BSTNode* insert(string x, int fileNumber, BSTNode* t)
    {
        if(t == NULL)
        {
            t = new BSTNode;
            t -> data = x;
            t -> fileNumber = fileNumber;
            t -> left = t -> right = NULL;
        }
        else if(x < t -> data)
            t -> left = insert(x, fileNumber, t -> left);
        else if(x > t->data)
            t -> right = insert(x, fileNumber, t -> right);
        return t;
    }

    BSTNode* findMin(BSTNode* t)
    {
        if(t == NULL)
            return NULL;
        else if(t -> left == NULL)
            return t;
        else
            return findMin(t -> left);
    }

    BSTNode* remove(string x, BSTNode* t)
    {
        BSTNode* temp;
        if(t == NULL)
            return NULL;
        else if(x < t -> data)
            t -> left = remove(x, t -> left);
        else if(x > t -> data)
            t -> right = remove(x, t -> right);
        else if(t -> left && t -> right)
        {
            temp = findMin(t -> right);
            t -> data = temp -> data;
            t -> right = remove(t -> data, t -> right);
        }
        else
        {
            temp = t;
            if(t -> left == NULL)
                t = t -> right;
            else if(t -> right == NULL)
                t = t -> left;
            delete temp;
        }

        return t;
    }
    
    int search(BSTNode* t, string key)
    {
        if(t == NULL)
            return NULL;
        else if(key < t -> data)
            return search(t -> left, key);
        else if(key > t -> data)
            return search(t -> right, key);
        else
            return t -> fileNumber;
    }
    
    void printBinaryTree(BSTNode* t, int level)
    {
        if (t)
        {
            printBinaryTree(t -> right, level + 1);
            
            for(int i = 0; i < level; i++)
                cout << "  ";
            
            cout << t -> data << endl;
            printBinaryTree(t -> left, level + 1);
        }
    }


public:
    BST() {
        root = NULL;
    }

    ~BST() {
        root = makeEmpty(root);
    }

    void insert(string element, int fileNumber) {
        root = insert(element, fileNumber, root);
    }

    void remove(string element) {
        root = remove(element, root);
    }

    void printBinaryTree() {
        printBinaryTree(root, 0);
    }

    int search(string key)
    {
        int res;
        res = search(root, key);
        return ++res;
    }
};

#endif /* BinaryTree_h */
