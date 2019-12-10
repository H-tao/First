/*
we can define dp[i][j] to be to be the minimum number of operations to convert word1[0..i - 1] to word2[0..j - 1]. Then:
if word1[i] != word2[j]:
1. Replace word1[i - 1] by word2[j - 1] (dp[i][j] = dp[i - 1][j - 1] + 1 (for replacement));
2. Delete word1[i - 1] and word1[0..i - 2] = word2[0..j - 1] (dp[i][j] = dp[i - 1][j] + 1 (for deletion));
3. Insert word2[j - 1] to word1[0..i - 1] and word1[0..i - 1] + word2[j - 1] = word2[0..j - 1] (dp[i][j] = dp[i][j - 1] + 1 (for insertion)).

So:
1. dp[i][0] = i, edge case
2. dp[0][j] = j, edge case
3. dp[i][j] = dp[i - 1][j - 1], if word1[i - 1] = word2[j - 1];
4. dp[i][j] = min(dp[i - 1][j - 1] + 1, dp[i - 1][j] + 1, dp[i][j - 1] + 1), otherwise.
the answer will be dp[m][n].
*/

int minDistance(string word1, string word2) {
	int m = word1.length(), n = word2.length();
    if(m == 0) return n;
    if(n == 0) return m;

	std::vector<std::vector<int> > dp(m + 1, std::vector<int>(n + 1, 0));
	for(int i = 1; i <= m; ++i)
		dp[i][0] = i;
	for(int j = 1; j <= n; ++j)
		dp[0][j] = j;
	for(int i = 1; i <= m; ++i){
		for(int j = 1; j <= n; ++j){
			if(word1[i - 1] == word2[j - 1])
				dp[i][j] = dp[i - 1][j - 1];
			else
				dp[i][j] = min(dp[i - 1][j - 1]/*replace*/, min(dp[i - 1][j]/*delete*/, dp[i][j - 1])/*insert*/) + 1;
		}
	}
	return dp[m][n];
}

// Optimized Code:	we only need to maintain pre = dp[i - 1][j - 1](replace)、dp[j - 1] = dp[i][j - 1](delete)、dp[j]` = dp[i - 1][j](insert)
// n\m 	0		1		2		3		4
// 0	0		1		2		3		4
// 1	pre		dp[j]` 	..						// dp' means the old value
// 2	dp[j-1]	dp[j]	...						// dp  means the value we updating
// 3    3...

// n\m 	0		1		2		3		4
// 0	0		1		2		3		4
// 1	1		pre 	dp[j]`	...				// dp' means the old value
// 2	2		dp[j-1]	dp[j]	...				// dp  means the value we updating
// 3    3		...
int minDistance(string word1, string word2) {
    int m = word1.length(), n = word2.length();
    if(m == 0) return n;
    if(n == 0) return m;

    // n + 1 rows , m  + 1 columns
    std::vector<int> dp(m + 1, 0);
    for(int j = 1; j <= m; ++j)	// dp[0][0...j]
        dp[j] = j;
    for(int i = 1; i <= n; ++i){
        int pre = dp[0];  // remember the 0th column(dp[1...i][0])'s old value
        dp[0] = i;          // update the 0th column(dp[1...i][0])'s new value
        for(int j = 1; j <= m; ++j){
            int temp = dp[j];   
            if(word1[j - 1] == word2[i - 1])
                dp[j] = pre;
            else
                dp[j] = min(pre/*replace*/, min(dp[j - 1]/*delete*/, dp[j]/*insert*/)) + 1;
            pre = temp;  // the j will + 1, so it means remember the dp[j - 1]'s old value 
        }
    }
    return dp[m];
}
