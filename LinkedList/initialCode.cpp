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


Node* makeLinkedList(vector<int> arr)
{
    Node* head = new Node(arr[0]);
    Node* moving = head;
    for(int i=1;i<arr.size();i++)
    {
        Node* temp = new Node(arr[i]);
        moving->next = temp;
        moving = temp;
    }
    return head;
}

void printLinkedList(Node* head)
{
    while(head)
    {
        cout << head-> val << " ";
        head = head->next;
    }
}

bool searchNode(Node* head,int target)
{
    while(head)
    {
        if(head->val == target)return true;
        head = head->next;
    }
    return false;
}

int lengthLinkedList(Node* head)
{
	int ret = 0;
	while(head)
	{
		ret++;head = head->next;
	}
	return ret;
}

Node* deleteHead(Node* head)
{
	if(!head || !head->next)return nullptr;
	return head->next;
}


Node* deleteTail(Node* head)
{
	if(!head || !head->next)return nullptr;
	Node* real = head;
	while(head->next->next)
	{
		head = head->next;
	}
	head->next = nullptr;
	return real;
}


int main()
{
    vector<int> arr = {1,2,3,4,5};
    Node* head = makeLinkedList(arr);
	head = deleteTail(head);
	printLinkedList(head);
	cout << endl;
    return 0;
}