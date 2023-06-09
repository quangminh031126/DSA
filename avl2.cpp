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

    void insert(const T &value)
    {
        // TODO
        root = insertNode(root, value);
    }
    Node *rotateLeft(Node *node)
    {
        Node *pivot = node->pRight;
        node->pRight = pivot->pLeft;
        pivot->pLeft = node;
        node->balance = EH;
        pivot->balance = EH;
        node = pivot;
        return node;
    }
    Node *rotateRight(Node *node)
    {
        Node *pivot = node->pLeft;
        node->pLeft = pivot->pRight;
        pivot->pRight = node;
        node->balance = EH;
        pivot->balance = EH;
        node = pivot;
        return node;
    }
    Node *rotateLeftRight(Node *node)
    {
        node->pLeft = rotateLeft(node->pLeft);
        node = rotateRight(node);
        return node;
    }

    Node *rotateRightLeft(Node *node)
    {
        node->pRight = rotateRight(node->pRight);
        node = rotateLeft(node);
        return node;
    }
    Node *rebalance(Node *node)
    {
        if (static_cast<int>(node->balance) < -1)
        {
            if (static_cast<int>(node->pLeft->balance) <= -1)
            {
                node = rotateRight(node);
            }
            else if (static_cast<int>(node->pLeft->balance) >= 1)
            {
                node = rotateLeftRight(node);
            }
        }
        else if (static_cast<int>(node->balance) > 1)
        {
            if (static_cast<int>(node->pRight->balance) >= 1)
            {
                node = rotateLeft(node);
            }
            else if (static_cast<int>(node->pRight->balance) <= -1)
            {
                node = rotateRightLeft(node);
            }
        }
        return node;
    }
    Node *insertNode(Node *node, const T &value)
    {
        if (node == NULL)
        {
            Node *newNode = new Node(value);
            return newNode;
        }

        if (value < node->data)
        {
            node->pLeft = insertNode(node->pLeft, value);
            node->balance = static_cast<BalanceValue>(node->balance - 1);
            node = rebalance(node);
        }
        else
        {
            node->pRight = insertNode(node->pRight, value);
            node->balance = static_cast<BalanceValue>(node->balance + 1);
            node = rebalance(node);
        }
        return node;
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
    for (int i = 0; i < 9; i++)
    {
        avl.insert(i);
    }
    avl.printTreeStructure();
}