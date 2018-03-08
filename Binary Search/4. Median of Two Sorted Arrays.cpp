double findMedianSortedArrays(vector<int>& A, vector<int>& B) {
    int m = A.size(), n = B.size();
    if(m > n)   return findMedianSortedArrays(B, A);    // make sure m <= n ==> j = (m + n + 1)/2 - i >= 0  
    if(n == 0)  return 0;   // m == 0 and n == 0
    
    int i = 0, imin = 0, imax = m;
    int half_len = (m + n + 1) / 2;    
    int j = 0;
    while(imin <= imax){
        i = (imin + imax) / 2; // binary search i, make it perfect
        j = half_len - i;   // i + j == n + m + 1- i - j, make sure left_size == right_size
        
        //make sure A[i] > B[j - 1] and A[i - 1] < B[j]
        if(i > 0 && A[i-1] > B[j])    // i is too big
            imax = i - 1;
        else if(i < m && A[i] < B[j-1])      // i is too small
            imin = i + 1;
        else /*if((i == 0 || j == n || A[i] > B[j-1]) 
                && (i == m || j == 0 || A[i-1] < B[j]))   // i is perfect*/
                break;
    }
    
    int max_left = 0, min_right = 0;
    if(i == 0)  max_left = B[j-1];
    else if(j == 0)  max_left = A[i-1];
    else  max_left = max(A[i-1], B[j-1]);
    if((m + n) & 1) return max_left;
    
    if(i == m)  min_right = B[j];
    else if(j == n)  min_right = A[i];
    else  min_right = min(A[i], B[j]);
    return  (max_left + min_right) / 2.0;
}