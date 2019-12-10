class Solution {
public:
    /*
        遍历S，求每个字对应的长度之和，每当和多一百则行数加一，
        在每一行记录字母数，如果转到下一行则重新计数
    */
    vector<int> numberOfLines(vector<int>& widths, string S) {
        int s_len = S.size();
        if(s_len == 0) return vector<int>();
        
        int lines = 1, lenOfLast = 0;
        int totalLen = 0;
        for(int i = 0; i < s_len; ++i){
            int letterLen =  widths[S[i] - 'a'];
            totalLen += letterLen;
            lenOfLast += letterLen;
            // 判断是否为新行
            if(totalLen / 100 == lines){
                ++lines;    // 行数加一
                lenOfLast = 0;  // 重新计数新行
                // 判断最后一个字母是否需要转行
                int more = totalLen % 10;
                if(more != 0){
                    totalLen += (letterLen - more); // 补齐 如Example 2 98 units ，最后一个字母长4
                    lenOfLast += letterLen;
                }
            }
        }
        return {lines, lenOfLast};
    }
};