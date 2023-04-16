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

    void updateBalance(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        rebalance(node);
        int lh = getHeightRec(node->pLeft);
        int rh = getHeightRec(node->pRight);
        node->balance = static_cast<BalanceValue>(rh - lh);
        rebalance(node);

        updateBalance(node->pLeft);
        rebalance(node);

        updateBalance(node->pRight);
        rebalance(node);
    }

    void rebalance(Node *node)
    {
        if (node->balance == LH)
        {
            if (node->pLeft->balance == LH)
            {
                rotateRight(node);
            }
            else if (node->pLeft->balance == RH)
            {
                rotateLeftRight(node);
            }
            else
                return;
        }
        else if (node->balance == RH)
        {
            if (node->pRight->balance == RH)
            {
                rotateLeft(node);
            }
            else if (node->pRight->balance == LH)
            {
                rotateRightLeft(node);
            }
            else
                return;
        }
    }

    void rotateLeft(Node *node)
    {
        Node *pivot = node->pRight;
        node->pRight = pivot->pLeft;
        pivot->pLeft = node;
        node->balance = EH;
        pivot->balance = EH;
        node = pivot;
    }

    void rotateRight(Node *node)
    {
        Node *pivot = node->pLeft;
        node->pLeft = pivot->pRight;
        pivot->pRight = node;
        node->balance = EH;
        pivot->balance = EH;
        node = pivot;
    }

    void rotateLeftRight(Node *node)
    {
        rotateLeft(node->pLeft);
        rotateRight(node);
    }

    void rotateRightLeft(Node *node)
    {
        rotateRight(node->pRight);
        rotateLeft(node);
    }

    void insert(const T &value)
    {
        if (root == nullptr)
        {
            root = new Node(value);
            return;
        }
        Node *currentNode = root;
        Node *parentNode = nullptr;
        while (currentNode != nullptr)
        {
            parentNode = currentNode;
            if (value < currentNode->data)
            {
                currentNode = currentNode->pLeft;
            }
            else
            {
                currentNode = currentNode->pRight;
            }
        }
        if (value == parentNode->data)
        {
            currentNode = new Node(value);
            parentNode->pRight = currentNode;
        }
        else if (value < parentNode->data)
        {
            currentNode = new Node(value);
            parentNode->pLeft = currentNode;
        }
        else
        {
            currentNode = new Node(value);
            parentNode->pRight = currentNode;
        }
        // update balance factors
        updateBalance(root);
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