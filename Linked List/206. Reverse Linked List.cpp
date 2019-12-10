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
        这个题我们可以利用三个指针：
        NULL 1 -> 2 -> 3 -> 4 -> 5
         ↑   ↑↑
         a   bc
         
        (1)c = b->next;               (2)b->next = a;               (3)a = b;                     (4)b = c;
        NULL 1 -> 2 -> 3 -> 4 -> 5    NULL <- 1  2 -> 3 -> 4 -> 5   NULL <- 1  2 -> 3 -> 4 -> 5   NULL <- 1  2 -> 3 -> 4 -> 5
         ↑   ↑    ↑                    ↑      ↑  ↑                         ↑↑  ↑                          ↑  ↑↑
         a   b    c                    a      b  c                         ab  c                          a  bc
        
        (1)c = b->next;               (2)b->next = a;               (3)a = b;                     (4)b = c;
        NULL <- 1  2 -> 3 -> 4 -> 5    NULL <- 1 <- 2  3 -> 4 -> 5   NULL <- 1 <- 2  3 -> 4 -> 5   NULL <- 1 <- 2  3 -> 4 -> 5
                ↑  ↑    ↑                      ↑    ↑  ↑                         ↑↑  ↑                          ↑  ↑↑
                a  b    c                      a    b  c                         ab  c                          a  bc     
        
        (1)c = b->next;               (2)b->next = a;               (3)a = b;                     (4)b = c;                  
        NULL <- 1 <- 2  3 -> 4 -> 5   NULL <- 1 <- 2 <- 3  4 -> 5    NULL <- 1 <- 2 <- 3  4 -> 5   NULL <- 1 <- 2 <- 3  4 -> 5
                     ↑  ↑    ↑                     ↑    ↑  ↑                          ↑↑  ↑                          ↑  ↑↑
                     a  b    c                     a    b  c                          ab  c                          a  bc          
        
        (1)c = b->next;               (2)b->next = a;               (3)a = b;                     (4)b = c;                  
        NULL <- 1 <- 2 <- 3  4 -> 5   NULL <- 1 <- 2 <- 3 <- 4  5    NULL <- 1 <- 2 <- 3 <- 4  5   NULL <- 1 <- 2 <- 3 <- 4  5
                          ↑  ↑    ↑                     ↑    ↑  ↑                          ↑↑  ↑                          ↑  ↑↑
                          a  b    c                     a    b  c                          ab  c                          a  bc  
        
        (1)c = b->next;               (2)b->next = a;               (3)a = b;                      (4)b = c;     
        NULL <- 1 <- 2 <- 3 <- 4  5   NULL <- 1 <- 2 <- 3 <- 4 <- 5  NULL <- 1 <- 2 <- 3 <- 4 <- 5  NULL <- 1 <- 2 <- 3 <- 4 <- 5
                               ↑  ↑ ↑                        ↑    ↑ ↑                           ↑↑ ↑                            ↑  ↑↑
                               a  b c                        a    b c                           ab c                            a  bc  
        
    */
    ListNode* reverseList(ListNode* head) {
        if(head == NULL || head -> next == NULL) 
            return head;
        
        ListNode* first = NULL;
        ListNode* second = head;
        ListNode* third = second;
        while(third != NULL){
            third = second -> next;
            second -> next = first;
            first = second;
            second = third;
        }
        return first;
    }
};