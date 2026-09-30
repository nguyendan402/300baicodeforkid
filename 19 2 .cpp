class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head || !head->next) return head; // empty or single node

        ListNode* newHead = reverseList(head->next);
        head->next->next = head; // next node points back to head
        head->next = nullptr;    // head becomes the tail
        return newHead;
    }
};