/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        //we can create a list using a head and tail pointer where
        ListNode* head = nullptr;
        ListNode* tail = nullptr;
        int carry = 0, sum = 0;
        //while l1 or l2 havent ended or carry isnt 0
        //construct the list
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            //sum is sum of l1 val and l2 val plus carry
            sum = (l1 != nullptr ? l1->val : 0) + (l2 != nullptr ? l2->val : 0) + carry;
            //carry is sum / 10
            carry = sum / 10;
            
            //create our new node for the list
            //its val will be sum mod 10 in case of a carry
            ListNode* new_node = new ListNode(sum % 10);

            //initialize the list
            if (head == nullptr) {
                head = tail = new_node;
            }
            else {
                tail->next = new_node;
                tail = new_node;
            }

            //iterate through the lists
            if (l1 != nullptr) l1 = l1->next;
            if (l2 != nullptr) l2 = l2->next;
        }
        return head;
    }
};