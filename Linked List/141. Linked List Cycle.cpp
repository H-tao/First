/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    /*
        这个题我开始写超时了，原因我没有考虑部分圈的情况
        整个圈：1 -> 2 -> 3 -> 1
        部分圈：1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 4
        看讨论发现有个好办法就是使用两枚指针，一枚指针每次移动1步，另一枚每次移动2步
        如果有圈，两枚指针终有一刻会相遇
        如果没有圈，移动得快的那一枚就会遇到NULL
    */
    bool hasCycle(ListNode *head) {
        if(head == NULL || head -> next == NULL) return false;
        
        ListNode *oneStep = head, *twoStep = head;
        while(twoStep -> next != NULL && twoStep -> next -> next != NULL){
            oneStep = oneStep -> next;          // 每次移动一步
            twoStep = twoStep -> next -> next;  // 每次移动两步
            if(oneStep == twoStep)  // 相遇代表存在圈 
                return true;       
        }
        return false;       // 遇到了NULL
    }
};