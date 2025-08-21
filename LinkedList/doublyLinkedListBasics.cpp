#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int val;
    Node* prev;
    Node* next;

    Node(int val, Node* prev=nullptr, Node* next=nullptr)
        : val(val), prev(prev), next(next) {}
};

// ========================
// Construction / Printing
// ========================
Node* makeDLL(const vector<int>& arr) {
    if (arr.empty()) return nullptr;

    Node* head = new Node(arr[0]);
    Node* prev = head;
    for (int i = 1; i < arr.size(); i++) {
        Node* curr = new Node(arr[i], prev);
        prev->next = curr;
        prev = curr;
    }
    return head;
}

void printDLL(Node* head) {
    while (head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << "\n";
}

// ========================
// Utility Functions
// ========================
bool searchNode(Node* head, int target) {
    while (head) {
        if (head->val == target) return true;
        head = head->next;
    }
    return false;
}

int lengthLinkedList(Node* head) {
    int ret = 0;
    while (head) {
        ret++;
        head = head->next;
    }
    return ret;
}

// ========================
// Deletion Operations
// ========================
Node* deleteHead(Node* head) {
    if (!head) return nullptr;
    Node* temp = head;
    head = head->next;
    if (head) head->prev = nullptr;
    delete temp;
    return head;
}

Node* deleteTail(Node* head) {
    if (!head) return nullptr;
    if (!head->next) { delete head; return nullptr; }

    Node* curr = head;
    while (curr->next) curr = curr->next; // last node
    curr->prev->next = nullptr;
    delete curr;
    return head;
}

Node* deletePosition(Node* head, int position) {
    if (!head || position <= 0) return head;

    if (position == 1) return deleteHead(head);

    Node* curr = head;
    int idx = 1;
    while (curr && idx < position) {
        curr = curr->next;
        idx++;
    }
    if (!curr) return head; // position > length

    curr->prev->next = curr->next;
    if (curr->next) curr->next->prev = curr->prev;
    delete curr;
    return head;
}

Node* deleteValue(Node* head, int val) {
    while (head && head->val == val) {
        Node* temp = head;
        head = head->next;
        delete temp;
        if (head) head->prev = nullptr;
    }
    if (!head) return nullptr;

    Node* curr = head->next;
    Node* prev = head;
    while (curr) {
        if (curr->val == val) {
            Node* temp = curr;
            curr = curr->next;
            prev->next = curr;
            if (curr) curr->prev = prev;
            delete temp;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    return head;
}

// ========================
// Insertion Operations
// ========================
Node* insertHead(Node* head, int value) {
    Node* newHead = new Node(value);
    if (head) {
        head->prev = newHead;
        newHead->next = head;
    }
    return newHead;
}

Node* insertTail(Node* head, int value) {
    if (!head) return new Node(value);

    Node* curr = head;
    while (curr->next) curr = curr->next;
    Node* newTail = new Node(value, curr);
    curr->next = newTail;
    return head;
}

Node* insertAtK(Node* head, int k, int value) {
    if (k <= 1 || !head) return insertHead(head, value);

    Node* curr = head;
    int idx = 1;
    while (curr && idx < k) {
        curr = curr->next;
        idx++;
    }
    if (!curr) return insertTail(head, value); // k > length → insert at tail

    Node* newNode = new Node(value, curr->prev, curr);
    curr->prev->next = newNode;
    curr->prev = newNode;
    return head;
}

// ========================
// Cleanup
// ========================
void freeList(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// ========================
// Demo
// ========================
int main() {
    vector<int> vc = {1,2,3,4,5};
    Node* head = makeDLL(vc);

    cout << "Original list: ";
    printDLL(head);

    head = deleteHead(head);
    cout << "After deleting head: ";
    printDLL(head);

    head = deleteTail(head);
    cout << "After deleting tail: ";
    printDLL(head);

    head = insertHead(head, 10);
    cout << "After inserting at head: ";
    printDLL(head);

    head = insertTail(head, 20);
    cout << "After inserting at tail: ";
    printDLL(head);

    head = insertAtK(head, 3, 15);
    cout << "After inserting 15 at position 3: ";
    printDLL(head);

    head = deleteValue(head, 3);
    cout << "After deleting value 3: ";
    printDLL(head);

    freeList(head); // cleanup memory
    return 0;
}
