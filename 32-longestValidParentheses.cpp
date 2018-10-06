#include <iostream>
#include <stack>
#include <vector>
#include <debug.h>

using namespace std;

class Solution {
public:
  int longestValidParentheses(string s) {
    vector<int> index(s.size(), 0);
    //debug(index);
    stack<pair<int, char>> temp;
    for (size_t i = 0;i < s.size();i++) {
      if(temp.empty()) temp.push(make_pair(i, s[i]));
      else {
        auto t = temp.top();
        if (t.second == '(' && s[i] == ')') {
          index[i] = 1; index[t.first] = 1;
          temp.pop();
        } else {
          temp.push(make_pair(i, s[i]));
        }
      }
    }

    //for (size_t i = 2;i < s.size();i++) {
      //if (index[i] == 0 && index[i-1] == 1 && s[i] == '(') 
        //index[i] = 2;
    //}
    //debug(index);

    int final = 0;
    for (size_t i = 0;i < s.size();) {
      if (index[i]) {
        int t = 0;
        while (index[i] && i < s.size()) {
          t++;i++;
        }
        if (t > final) final = t;
      } else i++;
    }
    
    return final;
  }
};

int main(void) {
  //string d = "((())()(";
  //string d = "()(()";
  //string d = "(()";
  string d = ")()())";
  Solution s;
  cout << s.longestValidParentheses(d);
  
  return 0;
}
