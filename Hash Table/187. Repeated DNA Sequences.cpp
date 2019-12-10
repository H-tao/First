/*  "AAAAAAAAAAA" 11个A  Return ：["AAAAAAAAAA"] 
    遍历整个DNA序列s：
    1、我们可以用hash_map<string, int> 存储每10-letter-long sequences(10个字母长的序列) s.substr(i, 10)
    2、每发现一个string，则hash_map[substr]++
    3、最后遍历hash_map，如果键值大于1，说明存在重复，加入结果数组
*/
vector<string> findRepeatedDnaSequences(string s) {
    int len = s.size();
    if(len == 0) return vector<string>();
    
    vector<string> result;
    unordered_map<string, int> map;
    // last 10-letter-long sequences is [len - 10, len)
    for(int i = 0; i <= len - 10; ++i){
        map[s.substr(i, 10)]++;
    }
    
    // traversal the map
    for(auto &m : map){
        if(m.second > 1)
            result.push_back(m.first);
    }
    
    return result;
}