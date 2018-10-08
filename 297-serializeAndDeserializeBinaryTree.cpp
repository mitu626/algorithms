#include <iostream>
#include <queue>
#include <debug.h>
#include <sstream>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Codec {
public:
  string serialize(TreeNode* root) {
    if (root == NULL) return "[]";
    stringstream os;
    os << "[";
    queue<TreeNode*> levelNodes;
    levelNodes.push(root);
    while (levelNodes.size()) {
      for (int i = 0, len = levelNodes.size();i < len;i++) {
        TreeNode *temp = levelNodes.front();
        levelNodes.pop();
        if (temp == NULL) {
          os << "NULL,";
        } else {
          os << temp->val << ",";
          levelNodes.push(temp->left);
          levelNodes.push(temp->right);
        }
      }
    }
    string final = os.str();
    while (true) {
      if (string(final.end()-5, final.end()) == "NULL,") {
        final = string(final.begin(), final.end()-5);
      } else {
        break;
      }
    }
    *(final.end()-1) = ']';
    return final;
  }

  TreeNode* deserialize(string data) {
    if (data.size() < 2 || 
        *data.begin() != '[' || 
        *(data.end()-1) != ']' ||
        data == "[]" ||
        data == "[NULL]")
      return NULL;
    vector<string> splits;
    for (size_t i = 1;i < data.size()-1;) {
      auto e = data.find(",", i);
      if (e == string::npos) {
        splits.push_back(string(data.begin()+i, data.end()-1));
        break;
      } else {
        splits.push_back(string(data.begin()+i, data.begin()+e));
        i = e + 1;
      }
    }

    vector<TreeNode*> nodes;
    int value;
    sscanf(splits.begin()->c_str(), "%d", &value);
    nodes.push_back(new TreeNode(value));
    for (size_t i = 0, p = 1; i < nodes.size() && p < splits.size();i++) {
      if (nodes[i] == NULL) continue;
      TreeNode *left, *right;
      if (splits[p] == "NULL") {
        left = NULL;
      } else {
        int a; sscanf(splits[p].c_str(), "%d", &a);
        left = new TreeNode(a);
      }

      if (p+1 == splits.size() || splits[p+1] == "NULL") {
        right = NULL;
      } else {
        int b; sscanf(splits[p+1].c_str(), "%d", &b);
        right = new TreeNode(b);
      }

      nodes[i]->left = left; nodes.push_back(left);
      nodes[i]->right = right; nodes.push_back(right);
      p += 2;
    }
    return nodes[0];
  }
};

int main(void) {
  Codec c;
  //string s = "[1,2,3,NULL,NULL,4,5]";
  string s = "[1,2]";
  TreeNode *root = c.deserialize(s);
  cout << c.serialize(root);
}
