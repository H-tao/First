/*
	Custon Testcase：
	"3[a]2[bc]"
	"3[a]2[bc]dd"
	"2[a2[b]]"
	"12[aa20[bb23[cc]]]dd"
*/
/*
	Approch One：Use Stack
	num = 0，word = ""
	从左至右扫描串s，每次取一个字符c：
		1) c为数字，num = num * 10 + c - '0';
		2) c为字母，word += c;
		3) c为'['，将num进数字栈, 将word进单词栈，num清零;
		4) c为']'，弹出数字栈顶num，弹出单词栈顶为newWord，
			newWord += word重复num次，将newWord再次进栈;
		
*/

class Solution {
public:
    string decodeString(string s) {
        int len = s.size();
        if(len == 0) return "";

        stack<string> wordStack;
        stack<int> numStack;
        string word = "";
        int num = 0;
        for(int i = 0; i < len; ++i){
            char c = s[i];
            if(c <= '9' && c >= '0'){
                num = num * 10 + c - '0';
            }
            else if(c == '['){
                wordStack.push(word);
                word = "";
                numStack.push(num);
                num = 0;
            }
            else if(c == ']'){
                string newWord = wordStack.top();	wordStack.pop();// res相当于newWord
                int n = numStack.top();	numStack.pop();// 取数字栈顶
                for(int j = 0; j < n; ++j)
                    newWord += word;
                word = newWord;
            }
            else{
                word += c;
            }
        }
        return word;
    }
};


/*
	Approach Two：Recursive
*/
class Solution {
public:
    string decodeString(string s) {
        int pos = 0;
        return subWord(pos, s);
    }
    
    string subWord(int &pos, const string& s){
        string word = "";
        for(int count = 0; pos < s.size(); ++pos){
            if(isdigit(s[pos]))
                count = count * 10 + s[pos] - '0';
            else if(s[pos] == '['){
                string temp = subWord(++pos, s);
                for(; count > 0; --count)
                    word += temp;
            }
            else if(s[pos] == ']')
                break;
            else
                word += s[pos];
        }
        return word;
    }
};