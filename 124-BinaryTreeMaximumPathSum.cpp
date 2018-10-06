#include <iostream>
#include <vector>
#include <debug.h>
#define EMPTY -100000

using namespace std;

struct TreeNode {
 int val;
 TreeNode *left;
 TreeNode *right;
 TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
  int final = -1000;
  int maxPathSum(TreeNode* root) {
    go(root);
    return final;
  }

  int go(TreeNode *root) {
    if (root == NULL) return 0;
    int left = go(root->left);
    int right = go(root->right);
    left = left > 0 ? left : 0;
    right = right > 0 ? right : 0;
    int maxNum = left + root->val + right;
    if (maxNum > final) final = maxNum;
    return max(left, right) + root->val;
  }
};

TreeNode* init(vector<int> &data) {
  vector<TreeNode*> final;
  int t = -1;
  int a = 0;
  for (auto it = data.begin();it != data.end();it++) {
    struct TreeNode *temp;
    if (*it == EMPTY) temp = NULL;
    else temp = new TreeNode(*it);
    final.push_back(temp);
    
    if (t == -1) t = 0;
    else {
      struct TreeNode *root = final[t];
      if (a == 2) root = NULL;
      while (root == NULL) root = final[++t];
      a %= 2;
      if (a == 0) {
        root->left = temp;
      } else {
        root->right = temp;
      }
      a++;
    }
  }
  return final[0];
}

void debug(TreeNode *root) {
  if (root == NULL) cout << "=> NULL" << endl;
  else {
    cout << "=> " << root->val << endl;
    debug(root->left);
    debug(root->right);
  }
}

void destroy(TreeNode *root) {
  if (root == NULL) return ;
  destroy(root->left);
  destroy(root->right);
  delete root;
}

int main(void) {
  //vector<int> data = {-10, 9, 20, EMPTY, EMPTY, 15, 7};
  vector<int> data = {-3};
  TreeNode *root = init(data);
  debug(root);
  Solution s;
  cout << s.maxPathSum(root) << endl;
  destroy(root);
  
  return 0;
}
