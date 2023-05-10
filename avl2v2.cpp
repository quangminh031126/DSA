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
    Node *rotateLeft(Node *root)
    {
        Node *pivot = root->pRight;
        root->pRight = pivot->pLeft;
        pivot->pLeft = root;
        return pivot;
    }
    Node *rotateRight(Node *root)
    {
        Node *pivot = root->pLeft;
        root->pLeft = pivot->pRight;
        pivot->pRight = root;
        return pivot;
    }
    Node *leftBalance(Node *root, bool &taller)
    {
        Node *leftTree = root->pLeft;
        // Case 1: Left of left. Single rotation right.
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
            if (rightTree == NULL)
            {
                root->balance = EH;
                leftTree->balance = RH;
            }
            else
            {
                if (rightTree->balance == LH)
                {
                    root->balance = RH;
                    leftTree->balance = EH;
                }
                else if (rightTree->balance == EH)
                {
                    leftTree->balance = EH;
                }
                else
                {
                    root->balance = EH;
                    leftTree->balance = LH;
                }
                rightTree->balance = EH;
                root->pLeft = rotateLeft(leftTree);
            }
            root = rotateRight(root);
            taller = false;
        }
        return root;
    }
    Node *rightBalance(Node *root, bool &taller)
    {
        Node *rightTree = root->pRight;
        // Case 1: Right of right. Single rotation left.
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
            if (leftTree == NULL)
            {
                root->balance = EH;
                rightTree->balance = LH;
            }
            else
            {
                if (leftTree->balance == RH)
                {
                    root->balance = LH;
                    rightTree->balance = EH;
                }
                else if (leftTree->balance == EH)
                {
                    rightTree->balance = EH;
                }
                else
                {
                    root->balance = EH;
                    rightTree->balance = RH;
                }
                leftTree->balance = RH;
                root->pRight = rotateRight(rightTree);
            }
            root = rotateLeft(root);
            taller = false;
        }
        return root;
    }
    Node *insertRec(Node *root, Node *newNode, bool &taller)
    {
        if (root == NULL)
        {
            root = newNode;
            taller = true;
            return root;
        }
        if (newNode->data < root->data)
        {
            root->pLeft = insertRec(root->pLeft, newNode, taller);
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
        else
        {
            root->pRight = insertRec(root->pRight, newNode, taller);
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
        // TODO
        bool taller = false;
        Node *newNode = new Node(value);
        this->root = insertRec(this->root, newNode, taller);
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
    int arr[] = {14, 2, 80, 55, 47, 43, 94, 88, 72, 30, 11, 87, 87, 29, 39};
    for (int i = 0; i < 15; i++)
    {
        avl.insert(arr[i]);
        cout << endl
             << i + 1 << " insert: " << endl;
        avl.printTreeStructure();
    }
}