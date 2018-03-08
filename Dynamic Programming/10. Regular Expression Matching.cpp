/*
we can define dp[i][j] to be false or true( s[0..i) matches p[0..j) ). Then:
1. if p[j - 1] != '*' 
dp[i][j] = dp[i-1][j-1]  ( s[i - 1] == p[j - 1] or p[j - 1] == '.' )	
like: // s = ...'a' , p = ...'a' or p = ...'.'
2.if p[j - 1] != '*' 
 (1) dp[i][j] = dp[i][j-2] 		
like: // s = ...'b' , p = ..."ba*"	the '*' matches 0 times 
 (2) dp[i][j] = dp[i-1][j]  ( s[i - 1] == p[j-2]	or p[j-2] == '.' )		
like: // s = ...'a', p = ..."a*" or p = ...".*" 	the '*' matches least 1 times
 (3) and so on the '*' matches least 2¡¢3¡¢4... times, but it can 
goto (2)dp[i][j] = dp[i - 2/3/4/...][j]£¬each time the i subtract 1
*/

    bool isMatch(string s, string p) {
        int m = s.length(), n = p.length();
        vector<vector<bool> > dp(m + 1, vector<bool>(n + 1, false));
        dp[0][0] = true;	// s = "" and p = ""
        for(int i = 0; i <= m; ++i)
            for(int j = 1; j <= n; ++j){
                if(p[j - 1] == '*')
                    dp[i][j] = dp[i][j - 2] || (i > 0 && dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'));
                else
                    dp[i][j] = (i > 0 && dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.'));
             }
        return dp[m][n];