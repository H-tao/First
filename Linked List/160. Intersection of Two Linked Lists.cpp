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
        看了讨论，发现很聪明的办法：同时遍历A、B，当任意遍历A、B的指针为空后，指向B、A重新开始遍历
        (1) 如果有交叉点，则有一刻会指向交叉点
        (2) 如果没有交叉点，则有一刻会同时指空
    1.        a1 -> a2
                     ↘  
                      c1 -> c2 -> c3
                     ↗ 
        b1 -> b2 -> b3
        p1遍历次序 ：a1 -> a2 -> NU -> c1 -> c2 -> c3 -> NU -> b1 -> b2 -> b3 -> c1
        p2遍历次序 ：b1 -> b2 -> b3 -> NU -> c1 -> c2 -> c3 -> NU -> a1 -> a2 -> c1
        
    2.  a1 -> a2 -> a3
        b1 -> b2 -> b3
        p1遍历次序 ：a1 -> a2 -> a3 -> NULL
        p2遍历次序 ：b1 -> b2 -> b3 -> NULL
        
    
    3.  a1 -> a2 -> a3
        b1 -> b2 -> b3 -> b4
        p1遍历次序 ：a1 -> a2 -> a3 -> NU -> b1 -> b2 -> b3 -> b4 -> NULL
        p2遍历次序 ：b1 -> b2 -> b3 -> b4 -> NU -> a1 -> a2 -> a3 -> NULL
        
    4.  a1(b1) -> a2(b2) 就是同一条链表
        
    */
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA == NULL || headB == NULL) return NULL;
        
        ListNode* p1 = headA, *p2 = headB;
        while(p1 != NULL && p2 != NULL && p1 != p2){
            p1 = p1 -> next;
            p2 = p2 -> next;
            if(p1 == p2) return p1;     // 相遇
            if(p1 == NULL) p1 = headB;
            if(p2 == NULL) p2 = headA;
        }
        // headA == headB
        return p1;
    }
};