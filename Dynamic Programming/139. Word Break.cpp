/* 
 * ���ǿ�����dp[i]��¼[0,i)�Ƿ���Ա��ָ��dp[s.len]��������s�ܷ񱻷ָ�
 * ��֪�����s����Ϊ0���Ա��ָdp[0] = true;
 * ��s�ĵ�0��λ�ÿ�ʼ��n��ȡ�������ֵ��ﵥ��word������s��0��λ�ÿ�ʼword���ȵ��Ӵ��Ƚϣ�
 * ���s���Ӵ�[0,word.len) == word��˵��s[0,word.len)��һ�����ʣ�s[0,word.len)���Ա��ָ�
 * ͬ��
 * ���s[0,i)�Ѿ����Ա��ָ�����ֵ���ĵ���word��s���Ӵ�[i,word.len) == word��
 * ��ô˵��[0,i+word.len)���Ա��ָ�
 * �Դ���ݹ������ý��.
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
// ��һ�ֽ������������
bool wordBreak(string s, vector<string>& wordDict) {
    if(wordDict.size() == 0) return false;

    unordered_set<string> dict(wordDict.begin(), wordDict.end());
    vector<bool> dp(s.size() + 1, false);
    dp[0] = true;

    // �鿴��[1,n) ��ÿ���Ӵ��Ƿ��ܱ��ָ�
    for(int i = 1; i <= s.size(); ++i){
        // �鿴�Ӵ����Ӵ��Ƿ��ܱ��ָ�
        for(int j = i - 1; j >= 0; --j){
            // ���[0,j)�ܱ��ָ�
            if(dp[j]){
                // �ж� [j,i) �ܷ񱻷ָ�
                string word = s.substr(j, i - j);   // �Ӵ�[j,i)
                if(dict.find(word) != dict.end()){  // [j,i)�������ֵ���
                    dp[i] = true;
                    break;  //�鿴��һ��i
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

        // �鿴��[1,n) ��ÿ���Ӵ��Ƿ��ܱ��ָ�
        for(int i = 1; i <= len; ++i){
            // �鿴�Ӵ����Ӵ��Ƿ��ܱ��ָ�
            for(int j = i - 1; j >= 0; --j){
                // ���[0,j)�ܱ��ָ� =>  �ж� [j,i) �ܷ񱻷ָ� => �ж��Ӵ�[j,i)�������ֵ���
                if(dp[j] && dict.find(s.substr(j, i - j)) != dict.end()){
                    dp[i] = true;
                    break;  //�鿴��һ��i
                }
            }
        }

        return dp[len];
    }
*/
