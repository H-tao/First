/* 利用一快一慢两枚指针二分链表，再将链表前一半逆置，最后比较 */
bool isPalindrome(ListNode* head) {
    if(head == NULL || head -> next == NULL)
        return true;
    
    // 二分链表  每次移动两枚指针，一共移动n/2次。Time ：2*O(n/2)
    ListNode *oneStep = head, *twoStep = head -> next;
    while(twoStep -> next != NULL){
        oneStep = oneStep -> next;
        twoStep = twoStep -> next -> next;
    }
    
    // 如果twoStep指向NULL了，代表链表长度为奇数
    bool isOdd = (twoStep == NULL ? true : false);
    twoStep = oneStep -> next;
    
    // 逆置前一半  Time ：4*O(n/2)
    ListNode *first = NULL, *second = head;
    while(second != twoStep){
        ListNode *third = second -> next;
        second -> next = first;
        first = second;
        second = third;
    }
    
    // 比较，此时我们发现first指向被逆置的前一半的头，second指向后一半
    if(isOdd)   // 如果是奇数，那么最中间的数不予比较
        first = first -> next;
    // 比较n/2次，移动2*n/2次。Time ：3*(n/2)
    while(first != NULL){
        if(first -> val != second -> val)
            return false;
        first = first -> next;
        second = second -> next;
    }
    
    return true;
    /* 总的时间复杂度为：9*O(n/2) => O(n)
}