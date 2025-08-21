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

Node* deletePosition(Node* head,int position)
{
    if(!head )return nullptr;
    if(position == 1)return head->next;
    int idx  = 2;
    Node* prev = head;
    Node* curr = head->next;
    while(curr && idx<=position)
    {
        if(idx == position)
        {
            prev->next = curr->next;
            // delete curr;
            break;
        }
        idx++;
        prev = curr;
        curr=curr->next;
    }
    return head;
}


Node* deleteValue(Node* head,int val)
{
    if(!head )return nullptr;
    while(head && head->val == val)
        head =  head->next;
    

    if(!head )return nullptr;
    Node* prev = head;
    Node* curr = head->next;
    while(curr)
    {
        while(curr && curr->val == val)
        {
            curr = curr->next;
        }
        prev->next = curr;
        if(curr)
        {
            prev = curr;
            curr = curr->next;
        }
        else
            break;
    }
    return head;
}


Node* insertHead(Node* head,int value)
{
    Node* newHead = new Node(value);
    newHead->next = head;
    return newHead;
}

Node* insertTail(Node* head,int value)
{
    if(!head)
    {
        Node* newHead = new Node(value);
        return newHead;
    }
    Node* curr = head;
    while(curr->next)curr= curr->next;
    Node* newTail = new Node(value);
    curr->next = newTail;
    return head;
}

Node* insertAtK(Node* head,int k)
{
    
}


int main()
{
    vector<int> arr = {5,5,3,2,5};
    Node* head = makeLinkedList(arr);
	head = insertTail(head,2);

	printLinkedList(head);
	cout << endl;
    return 0;
}