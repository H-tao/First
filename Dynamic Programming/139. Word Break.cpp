/* 
 * 我们可以用dp[i]记录[0,i)是否可以被分割，则dp[s.len]代表整个s能否被分割
 * 易知，如果s长度为0可以被分割，dp[0] = true;
 * 从s的第0个位置开始到n，取存在于字典里单词word，并与s第0个位置开始word长度的子串比较，
 * 如果s的子串[0,word.len) == word，说明s[0,word.len)是一个单词，s[0,word.len)可以被分割
 * 同理：
 * 如果s[0,i)已经可以被分割，对于字典里的单词word，s的子串[i,word.len) == word，
 * 那么说明[0,i+word.len)可以被分割
 * 以此类递归可以求得结果.
*/
bool wordBreak(string s, vector<string>& wordDict) {
    int dictSize = wordDict.size();
    if(dictSize == 0) return false;

    int len = s.size();
    vector<bool> dp(len + 1, false);
    dp[0] = true;
    
    for(int i = 0; i <= len; ++i){     
        for(int j = 0; j < dictSize ; ++j){   
        	if(dp[i]){
	            string word = wordDict[j];
	            int wordLen = word.size();
	            int pos = wordLen + i;
	            if(dp[i] && (pos <= len) && s.substr(i, wordLen) == word){    
	                dp[pos] = true;
	            }
	        }
        }
    }
    
    return dp[len];
}

/* 
// 另一种解决方法，逆推
bool wordBreak(string s, vector<string>& wordDict) {
    if(wordDict.size() == 0) return false;

    unordered_set<string> dict(wordDict.begin(), wordDict.end());
    vector<bool> dp(s.size() + 1, false);
    dp[0] = true;

    // 查看从[1,n) 的每个子串是否能被分割
    for(int i = 1; i <= s.size(); ++i){
        // 查看子串的子串是否能被分割
        for(int j = i - 1; j >= 0; --j){
            // 如果[0,j)能被分割
            if(dp[j]){
                // 判断 [j,i) 能否被分割
                string word = s.substr(j, i - j);   // 子串[j,i)
                if(dict.find(word) != dict.end()){  // [j,i)存在于字典中
                    dp[i] = true;
                    break;  //查看下一个i
                }
            }
        }
    }
    return dp[s.size()];
}
*/

/*
// The optimized Code:
    bool wordBreak(string s, vector<string>& wordDict) {
        if(wordDict.size() == 0) return false;

        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        int len = s.size();
        vector<bool> dp(len + 1, false);
        dp[0] = true;

        // 查看从[1,n) 的每个子串是否能被分割
        for(int i = 1; i <= len; ++i){
            // 查看子串的子串是否能被分割
            for(int j = i - 1; j >= 0; --j){
                // 如果[0,j)能被分割 =>  判断 [j,i) 能否被分割 => 判断子串[j,i)存在于字典中
                if(dp[j] && dict.find(s.substr(j, i - j)) != dict.end()){
                    dp[i] = true;
                    break;  //查看下一个i
                }
            }
        }

        return dp[len];
    }
*/
