//
//  main.cpp
//  Бинарное дерево выражений
//
//  Created by Хто Я on 22.12.2022.
//

#include <iostream>
#include <stack>
#include <sstream>
#include <string>

using namespace std;
 
struct Node
{
    string data;
    Node *left, *right;
 
    Node(char data)
    {
        this -> data = data;
        this -> left = this -> right = nullptr;
    };
 
    Node(char data, Node *left, Node *right)
    {
        this -> data = data;
        this -> left = left;
        this -> right = right;
    };
};
 
//--ПЕРЕВОД В ПОСТФИКС--//

bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool priority(char leftOperator, char rightOperator)
{
    if (leftOperator == '*' || leftOperator == '/')
        return true;
    else if (rightOperator == '*' || rightOperator == '/')
        return false;

    return true;
}

string convertToPostfix(const string& infix)
{
    stringstream postfix;
    stack<char> stack;
    stack.push('(');

    for (size_t i = 0, l = infix.size(); i < l; ++i)
    {
        const char current = infix[i];
    
        if (isalnum(current) || '.' == current)
            postfix << current;
        
        else if ('(' == current)
            stack.push(current);
        
        else if (isOperator(current))
        {
            char rightOperator = current;
            while (!stack.empty() && isOperator(stack.top()) && priority(stack.top(), rightOperator))
            {
                postfix << stack.top();
                stack.pop();
            }
            stack.push(rightOperator);
        }
        
        else if (')' == current)
        {
            while (!stack.empty() && '(' != stack.top())
            {
                postfix << stack.top();
                stack.pop();
            }
            stack.pop();
        }
    }

    while (!stack.empty() && '(' != stack.top())
    {
        postfix << stack.top();
        stack.pop();
    }
    stack.pop();

    return postfix.str();
}

//--СОЗДАНИЕ И ВЫВОД ДЕРЕВА--//

Node* constructBinaryTree(string postfix)
{
    stack<Node*> stack;
    
    if (postfix.length() == 0)
        return nullptr;
    
    for (char c: postfix)
    {
        if (isOperator(c))
        {
            Node* x = stack.top();
            stack.pop();
            Node* y = stack.top();
            stack.pop();
            Node* node = new Node(c, y, x);
            stack.push(node);
        }
        else
            stack.push(new Node(c));
    }
 
    return stack.top();
}

void printBinaryTree(Node* tree, int level)
{
    if (tree)
    {
        printBinaryTree(tree -> left, level + 1);
        
        for(int i = 0; i < level; i++)
            cout << "  ";
        
        cout << tree -> data << endl;
        printBinaryTree(tree -> right, level + 1);
    }
}

//--ЗАДАНИЕ 1--//

void currentLevel(Node* root, int level, int& countOper)
{
    if (root == NULL)
        return;
    
    if (level == 1)
        countOper++;
    else if (level > 1)
    {
        currentLevel(root -> left, level - 1, countOper);
        currentLevel(root -> right, level - 1, countOper);
    }
}

//--ЗАДАНИЕ 2--//

bool isLeaf(Node* node)
{
    return (node -> left == nullptr) && (node -> right == nullptr);
}
 
double process(string op, double x, double y)
{
    if (op == "+")
        return x + y;
    if (op == "-")
        return x - y;
    if (op == "*")
        return x * y;
    if (op == "/")
        return x / y;
 
    return 0;
}
 
double evaluate(Node* root, double& valLeftSide)
{
    if (root == nullptr)
        return 0;
    
    if (isLeaf(root))
        return stod(root->data);
    
    double x = evaluate(root -> left, valLeftSide);
    double y = evaluate(root -> right, valLeftSide);
    
    valLeftSide = y;
 
    return process(root->data, x, y);
}

//--ЗАДАНИЕ 3--//

void preorder(Node* root)
{
    if (root == NULL)
       return;
    
    cout << root -> data;
    preorder(root -> left);
    preorder(root -> right);
}

void prefixLeftSidePrint(Node* root)
{
    if (root == NULL)
       return;

    preorder(root -> right);
}
 
int main()
{
    int level = 3;
    int countOperator = 0;
    double valLeftSide = 0;
    string infix = "(1+2)*(3*(4+5))";
    string postfix = convertToPostfix(infix);
    Node* tree = constructBinaryTree(postfix);
    
    cout << "Вывод дерева: " << endl;
    printBinaryTree(tree, 6);
 
    cout << endl << "Постфиксная форма: ";
    cout << postfix << endl;
 
    cout << endl << "Инфиксная форма: ";
    cout << infix << endl;
    
    cout << endl << "Всего узлов (уровня " << level << "): ";
    currentLevel(tree, level, countOperator);
    cout << countOperator << endl;
    
    cout << endl << "Итог вычисления всего выражения: ";
    cout << evaluate(tree, valLeftSide) << endl;
    
    cout << endl << "Итог вычисления левого поддерева: ";
    cout << valLeftSide << endl;
    
    cout << endl << "Префиксная форма левого поддерева: ";
    prefixLeftSidePrint(tree);
    cout << endl << endl;
 
    return 0;
}
