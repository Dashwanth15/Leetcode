#include <iostream>
using namespace std;

// Definition for singly-linked list
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

int main() {
    // Example: list1 = [1,2,4], list2 = [1,3,4]

    // Creating list1
    ListNode* list1 = new ListNode(1);
    list1->next = new ListNode(2);
    list1->next->next = new ListNode(4);

    // Creating list2
    ListNode* list2 = new ListNode(1);
    list2->next = new ListNode(3);
    list2->next->next = new ListNode(4);

    // Dummy node
    ListNode* dummy = new ListNode(0);
    ListNode* tail = dummy;

    // Merge process
    while (list1 && list2) {
        if (list1->val <= list2->val) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    // Attach remaining nodes
    if (list1) tail->next = list1;
    if (list2) tail->next = list2;

    // Result head
    ListNode* merged = dummy->next;

    // Print merged list
    while (merged) {
        cout << merged->val << " ";
        merged = merged->next;
    }
    cout << endl;

    return 0;
}
