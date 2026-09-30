class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr) {
            ListNode* next = curr->next; // save next node
            curr->next = prev;           // reverse the pointer
            prev = curr;                 // move prev forward
            curr = next;                 // move curr forward
        }
        return prev; // new head
    }
};