#include <iostream>
#include <math.h>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int &n)
{
    cout << n << " ";
}

template <class T>
class AVLTree
{
public:
    class Node;

private:
    Node *root;

protected:
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() {}
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }
    void printTreeStructure()
    {
        int height = this->getHeight();
        if (this->root == NULL)
        {
            cout << "NULL\n";
            return;
        }
        queue<Node *> q;
        q.push(root);
        Node *temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode)
            {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height)
                return;
        }
    }
    Node *rotateRight(Node *node)
    {
        Node *newRoot = node->pLeft;
        node->pLeft = newRoot->pRight;
        newRoot->pRight = node;

        // Update balance factors
        if (newRoot->balance == RH)
        {
            node->balance = EH;
            newRoot->balance = EH;
        }
        else
        {
            node->balance = RH;
            newRoot->balance = LH;
        }

        return newRoot;
    }

    Node *rotateLeft(Node *node)
    {
        Node *newRoot = node->pRight;
        node->pRight = newRoot->pLeft;
        newRoot->pLeft = node;

        // Update balance factors
        if (newRoot->balance == LH)
        {
            node->balance = EH;
            newRoot->balance = EH;
        }
        else
        {
            node->balance = LH;
            newRoot->balance = RH;
        }

        return newRoot;
    }
    Node *rightBalance(Node *&root, bool &taller)
    {
        Node *rightTree = root->pRight;
        if (rightTree->balance == RH)
        {
            root = rotateLeft(root);
            root->balance = EH;
            rightTree->balance = EH;
            taller = false;
        }
        else
        {
            Node *leftTree = rightTree->pLeft;
            if (leftTree->balance == RH)
            {
                root->balance = EH;
                rightTree->balance = LH;
            }
            else if (leftTree->balance == EH)
            {
                root->balance = EH;
                rightTree->balance = EH;
            }
            else
            {
                root->balance = RH;
                rightTree->balance = EH;
            }
            leftTree->balance = EH;
            root->pRight = rotateRight(rightTree);
            root = rotateLeft(root);
            taller = false;
        }
        return root;
    }

    Node *leftBalance(Node *&root, bool &taller)
    {
        Node *leftTree = root->pLeft;
        if (leftTree->balance == LH)
        {
            root = rotateRight(root);
            root->balance = EH;
            leftTree->balance = EH;
            taller = false;
        }
        else
        {
            Node *rightTree = leftTree->pRight;
            if (rightTree->balance == LH)
            {
                root->balance = EH;
                leftTree->balance = RH;
            }
            else if (rightTree->balance == EH)
            {
                root->balance = EH;
                leftTree->balance = EH;
            }
            else
            {
                root->balance = LH;
                leftTree->balance = EH;
            }
            rightTree->balance = EH;
            root->pLeft = rotateLeft(leftTree);
            root = rotateRight(root);
            taller = false;
        }
        return root;
    }

    Node *AVLInsert(Node *root, Node *newPtr, bool &taller)
    {
        if (root == NULL)
        {
            root = newPtr;
            taller = true;
        }
        else if (newPtr->data < root->data)
        {
            root->pLeft = AVLInsert(root->pLeft, newPtr, taller);
            if (taller)
            {
                if (root->balance == LH)
                {
                    root = leftBalance(root, taller);
                }
                else if (root->balance == EH)
                {
                    root->balance = LH;
                }
                else
                {
                    root->balance = EH;
                    taller = false;
                }
            }
        }
        else if (newPtr->data > root->data || newPtr->data == root->data)
        {
            root->pRight = AVLInsert(root->pRight, newPtr, taller);
            if (taller)
            {
                if (root->balance == LH)
                {
                    root->balance = EH;
                    taller = false;
                }
                else if (root->balance == EH)
                {
                    root->balance = RH;
                }
                else
                {
                    root = rightBalance(root, taller);
                }
            }
        }
        return root;
    }
    void insert(const T &value)
    {
        Node *newNode = new Node(value);
        bool taller = true;
        if (this->root == NULL)
        {
            this->root = newNode;
            taller = false;
        }
        else
        {
            this->root = AVLInsert(this->root, newNode, taller);
        }
    }

    class Node
    {
    private:
        T data;
        Node *pLeft, *pRight;
        BalanceValue balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };
};
int main()
{
    AVLTree<int> avl;
    int arr[] = {17, 51, 88, 35, 42, 89, 74, 37, 48, 35, 56, 19, 69, 25, 52, 88, 86, 92};
    for (int i = 0; i < 18; i++)
    {
        avl.insert(arr[i]);
        cout << endl
             << i + 1 << " insert: " << endl;
        avl.printTreeStructure();
    }
}