//
//  BalanceBinaryTree.h
//  5_Сбалансированное бинарное дерево
//
//  Created by Хто Я on 22.10.2022.
//

#ifndef BalanceBinaryTree_h
#define BalanceBinaryTree_h

#include <iostream>
#include <vector>
#include <ctime>

#define MAX_VALUE 65536

using namespace std;

class BSTRand
{
public:
    struct RBSTNode
    {
        RBSTNode *left, *right;
        int priority, fileNumber;
        string data;
        
        RBSTNode()
        {
            this -> data = "";
            this -> fileNumber = 0;
            this -> left = this;
            this -> right = this;
            this -> priority = MAX_VALUE;
        }
           
        RBSTNode(string ele, int fileNumber) {
            RBSTNode(ele, fileNumber, NULL, NULL);
        }
            
        RBSTNode(string ele, int fileNumber, RBSTNode *left, RBSTNode *right)
        {
            srand((unsigned int)time(NULL));
            this -> data = ele;
            this -> fileNumber = fileNumber;
            this -> left = left;
            this -> right = right;
            this -> priority = rand() % 100 + 1;
        }
    };

private:
    RBSTNode *root;
    
    RBSTNode *insert(string element, int fileNumber, RBSTNode *t, int &counter)
    {
        if (t == NULL)
            return new RBSTNode(element, fileNumber, NULL, NULL);
        else if (element < t -> data)
        {
            counter++;
            t -> left = insert(element, fileNumber, t -> left, counter);
            if (t -> left -> priority < t -> priority)
            {
                RBSTNode *Left = t -> left;
                t -> left = Left -> right;
                Left -> right = t;
                return Left;
            }
        }
        else if (element > t -> data)
        {
            counter++;
            t -> right = insert(element, fileNumber, t -> right, counter);
            if (t -> right -> priority < t -> priority)
            {
                RBSTNode *Right = t -> right;
                t -> right = Right -> left;
                Right -> left = t;
                return Right;
            }
        }
        
        return t;
    }
    
    RBSTNode* makeEmpty(RBSTNode* t)
    {
        if(t == NULL)
            return NULL;
        {
            makeEmpty(t -> left);
            makeEmpty(t -> right);
            delete t;
        }
        return NULL;
    }
    
    RBSTNode* findMin(RBSTNode* t)
    {
        if(t == NULL)
            return NULL;
        else if(t -> left == NULL)
            return t;
        else
            return findMin(t -> left);
    }
    
    RBSTNode* remove(string x, RBSTNode* t)
    {
        RBSTNode* temp;
        if (t == NULL)
            return NULL;
        else if (x < t -> data)
            t -> left = remove(x, t -> left);
        else if (x > t -> data)
            t -> right = remove(x, t -> right);
        else if (t -> left && t -> right)
        {
            temp = findMin(t -> right);
            t -> data = temp -> data;
            t -> right = remove(t -> data, t -> right);
        }
        else
        {
            temp = t;
            if (t -> left == NULL)
                t = t -> right;
            else if (t -> right == NULL)
                t = t -> left;
            delete temp;
        }

        return t;
    }
    
    int search(RBSTNode* t, string key)
    {
        if (t == NULL)
            return NULL;
        else if (key < t -> data)
            return search(t -> left, key);
        else if (key > t -> data)
            return search(t -> right, key);
        else
            return t -> fileNumber;
    }
    
    void printBinaryTree(RBSTNode* t, int level)
    {
        if (t)
        {
            printBinaryTree(t -> right, level + 1);
            
            for (int i = 0; i < level; i++)
                cout << "  ";
            
            cout << t -> data << endl;
            printBinaryTree(t -> left, level + 1);
        }
    }
    
public:
    BSTRand() {
        root = NULL;
    }
    
    ~BSTRand() {
        root = makeEmpty(root);
    }
 
    void insert(string element, int fileNumber, int &counter) {
        root = insert(element, fileNumber, root, counter);
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
 
#endif /* BalanceBinaryTree_h */
