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

    // Helping functions
    Node *rotateLeft(Node *root)
    {
        Node *temp = root->pRight;
        root->pRight = temp->pLeft;
        temp->pLeft = root;
        return temp;
    }
    Node *rotateRight(Node *root)
    {
        Node *temp = root->pLeft;
        root->pLeft = temp->pRight;
        temp->pRight = root;
        return temp;
    }
    Node *leftBalance(Node *root, bool &taller)
    {
        Node *leftTree = root->pLeft;
        if (leftTree->balance == LH)
        {
            root->balance = EH;
            root = rotateRight(root);
            leftTree->balance = EH;
            taller = false;
        }
        else if (leftTree->balance == RH)
        {
            Node *rightTree = leftTree->pRight;
            if (rightTree->balance == EH)
            {
                leftTree->balance = EH;
                root->balance = EH;
            }
            else if (rightTree->balance == LH)
            {
                leftTree->balance = EH;
                root->balance = RH;
            }
            else
            {
                leftTree->balance = LH;
                root->balance = EH;
            }
            rightTree->balance = EH;
            root->pLeft = rotateLeft(leftTree);
            root = rotateRight(root);
            taller = false;
        }
        return root;
    }
    Node *rightBalance(Node *root, bool &taller)
    {
        Node *rightTree = root->pRight;
        if (rightTree->balance == RH)
        {
            root->balance = EH;
            root = rotateLeft(root);
            rightTree->balance = EH;
            taller = false;
        }
        else if (rightTree->balance == LH)
        {
            Node *leftTree = rightTree->pLeft;
            if (leftTree->balance == EH)
            {
                root->balance = EH;
                rightTree->balance = EH;
            }
            else if (leftTree->balance == LH)
            {
                root->balance = EH;
                rightTree->balance = RH;
            }
            else
            {
                root->balance = LH;
                rightTree->balance = EH;
            }
            leftTree->balance = EH;
            root->pRight = rotateRight(rightTree);
            root = rotateLeft(root);
            taller = false;
        }
        return root;
    }
    Node *helper(Node *root, const T &value, bool &taller)
    {
        if (!root)
        {
            root = new Node(value);
            taller = true;
            return root;
        }
        if (root->data > value)
        {
            root->pLeft = helper(root->pLeft, value, taller);
            if (taller)
            {
                if (root->balance == EH)
                {
                    root->balance = LH;
                }
                else if (root->balance == RH)
                {
                    root->balance = EH;
                    taller = false;
                }
                else
                {
                    root = leftBalance(root, taller);
                }
            }
        }
        else
        {
            root->pRight = helper(root->pRight, value, taller);
            if (taller)
            {
                if (root->balance == EH)
                {
                    root->balance = RH;
                }
                else if (root->balance == LH)
                {
                    root->balance = EH;
                    taller = false;
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
        // TODO
        bool taller = false;
        root = helper(root, value, taller);
        return;
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