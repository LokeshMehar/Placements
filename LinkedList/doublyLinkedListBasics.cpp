#include <bits/stdc++.h>
using namespace std;

class Node
{
    public:
    int val;
    Node* prev;
    Node* next;

    Node(int val,Node* prev=nullptr,Node* next=nullptr) : 
        val(val),prev(prev),next(next)
            {}
};

Node* makeDLL(vector<int> &arr)
{
    if(arr.size())
    {
        Node* head = new Node(arr[0]);
        Node* prev = head;
        for(int i=1;i<arr.size();i++)
        {
            Node* curr = new Node(arr[i]);
            prev->next = curr;
            curr->prev = prev;
            prev = curr;
        }
        return head;
    }
}


void printDLL(Node* head)
{
    while(head)
    {
        cout << head->val << " ";
        head = head->next;
    }
    return;

}

int main()
{
    vector<int> vc = {1,2,3,4,5};
    Node* head = makeDLL(vc);
    printDLL(head);
}