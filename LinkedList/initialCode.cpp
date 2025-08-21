#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int val;
    Node* next;
public:

    int getVal()
    {
        return this->val;
    }

    Node* getNext()
    {
        return this->next;
    }

    void setVal(int n)
    {
        this->val = n;
    }

    void  setNext(Node* nx)
    {
        this->next = nx;
    }

    Node(int val){
        this->val = val;
        next = nullptr;
    }
    ~Node();
};


int main()
{
    int arr[5] = {1,2,3,4,5};
    Node* head = new Node(arr[0]);
    Node* moving = head;
    for(int i=1;i<5;i++)
    {
        Node* temp = new Node(arr[i]);
        moving->setNext(temp);
        moving = temp;
    }

    while(head)
    {
        cout << head->getVal() << " ";
        head = head->getNext();
    }
    return 0;
}