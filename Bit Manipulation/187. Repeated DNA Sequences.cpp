/*  "AAAAAAAAAAA" 11个A  Return ：["AAAAAAAAAA"]
    一共A、C、G、T四个字母，我们可以分别用00、01、10、11表示
    一个子序列10个字母，为2*10位，可以用int型数来表示
    如：对于AAACGGGTTT => 00 00 00 01 10 10 10 11 11 11 
    一共有s.length() - 9个子序列，循环[0, s.length - 10]
    对于每一个子序列：
    1、如果不存在子序列集合Set中，说明子序列第1次出现，则放入集合
    2、如果已存在子序列集合Set中，却不存在结果数组中，说明序列是第2次出现，但未加入结果数组，则加入结果数组中
    3、如果已存在子序列集合Set中，也存在结果数组中，说明序列是第2+次出现，忽略
    由于vector<T>查找效率为O(n)，我们可以用另一个集合resultSet来存储已经加入结果数组的子序列
*/
vector<string> findRepeatedDnaSequences(string s) {
    int len = s.size();
    if(len == 0) return vector<string>();
    
    vector<string> result;
    unordered_set<int> oneSet;
    unordered_set<int> resultSet;
    char map[26]; 
    map['A' - 'A'] = 0; map['C' - 'A'] = 1;
    map['G' - 'A'] = 2; map['T' - 'A'] = 3;
    
    // total len - 9 numbers of 10-letter-long sequences
    for(int i = 0; i <= len - 10; ++i){
        int seq = 0;
        int seqEnd = i + 10;    // 10-letter-long sequences' end
        // make the 10-letter-long sequences to a int
        for(int j = i; j < seqEnd; ++j){   
            int state = map[s[j] - 'A'];   // A => 00 ; 
            seq <<= 2;      // move two bit to left
            seq |= state;   // add the new 
        }
        if(!oneSet.count(seq) && (!resultSet.count(seq)))
            oneSet.emplace(seq);
        else if(oneSet.count(seq) && (!resultSet.count(seq))){
            resultSet.emplace(seq);
            result.push_back(s.substr(i, 10));
        }
    }
    
    return result;
}