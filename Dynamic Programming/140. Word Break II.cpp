/*
第一次提交的时候遇到了，发现如果s中不存在b，那么整个串是不可分割的，所以为了避免不必要的搜索我们先看子串是否能被分割
Time Limit Exceeded：
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
["a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"]
*/
class Solution {
public:
    bool isCanWordBreak(string s, vector<string>& wordDict) {
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
                    if((pos <= len) && s.substr(i, wordLen) == word){    
                        dp[pos] = true;
                    }
                }
            }
        }

        return dp[len];
    }
    
    void backtracking(string& s, string substr, int begin, vector<string>& wordDict, vector<string>& result, vector<bool>& dp){
        int len = s.size();
        if(begin == len){
            result.push_back(substr);
            return;
        }
        if(begin > len) 
            return;
        
        for(int i = begin; i <= len; ++i){     
            for(int j = 0; j < wordDict.size() ; ++j){   
                if(dp[i]){
                    string word = wordDict[j];
                    int wordLen = word.size();
                    int pos = wordLen + i;
                    if((pos <= len) && s.substr(i, wordLen) == word){    
                       // substr += word;
                        dp[pos] = true;
                        backtracking(s, (substr.empty() ? word : substr + " " + word), pos, wordDict, result, dp);
                        dp[pos] = false;
                        //substr -= word;
                    }
                }
            }
        }
    }
    
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        int dictSize = wordDict.size();
        if(dictSize == 0 || !isCanWordBreak(s, wordDict)) return vector<string> ();

        vector<string> result;
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;
        backtracking(s, "", 0, wordDict, result, dp);
        return result;
    }
};