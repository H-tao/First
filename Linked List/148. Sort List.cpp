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
    ListNode* sortList(ListNode* head) {
        ListNode *first = head;
        ListNode *second = head;
        if(first == NULL || first -> next == NULL){
            // 为空或只有一个节点则直接返回（递归出口）
            return first;
        }
        while(second -> next != NULL && second -> next -> next != NULL){
            // 利用一块一慢指针二分链表
            first = first -> next;
            second = second -> next -> next;
        }
        if(first -> next != NULL){
            second = first -> next;  // second指针指向二分点
            first -> next = NULL;   // 将整个链表断开为两个
            first = head;           // first指针指向头
        }
        
        return merge(sortList(first), sortList(second));    
    }

private:
    ListNode* merge(ListNode* first, ListNode* second){
        ListNode* current = new ListNode(0); // 建立哨点
        ListNode* head = current;
        
        while(first != NULL && second != NULL){
            if(first -> val < second -> val)   // 取较小的节点
                link(current, first);
            else
                link(current, second);
        }
        
        while(first != NULL)        // 链接剩下的节点
            link(current, first);
        
        while(second != NULL)
            link(current, second);
        
        current = head -> next;     // 释放哨点
        delete head;
        return current;
    }
    
    // 这里必须是引用
    void link(ListNode* &linker, ListNode* &linked){
        linker -> next = linked;
        linker = linker -> next;
        linked = linked -> next;
    }
};