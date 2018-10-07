#include <iostream>
#include <vector>
#include <stack>
#define EMPTY -1000
using namespace std;
struct Node {
  int val;
  Node *left;
  Node *right;
  Node *parent;
  Node(int v) : val(v), left(NULL), right(NULL), parent(NULL) {}
};

Node* init(vector<int> &data) {
  if (data.size() == 0 || data[0] == EMPTY) return NULL; 
  vector<Node*> index;
  index.push_back(new Node(data[0]));
  for (size_t i = 0, p = 1;i < index.size() && p < data.size();i++) {
    if (index[i] != NULL) {
      Node *left = (data[p] == EMPTY) ? NULL : new Node(data[p]);
      Node *right = (data[p+1] == EMPTY) ? NULL : new Node(data[p+1]);
      index[i]->left = left; index[i]->right = right;
      index.push_back(left); index.push_back(right);
      p += 2;
    }
  }
  return index[0];
}

void debug(Node *root) {
  if (root == NULL) ;
  else {
    cout << root->val << " ";
    debug(root->left);
    debug(root->right);
  }
}

void debugStack(Node *root) {
  if (root == NULL) return ;
  stack<Node*> traverse;
  traverse.push(root);
  Node *p = root; 
  while (traverse.size()) {
    p = traverse.top();
    if (p->left) {
      traverse.push(p->left);
    } else {
      while (traverse.size() && traverse.top()->right == NULL) {
        cout << traverse.top()->val << " ";
        traverse.pop();
      }
      if (traverse.size()) {
        p = traverse.top();
        cout << p->val << " ";
        traverse.pop();
        traverse.push(p->right);
      }
    }
  }
}

void debugStack2(Node *root) {
  if (root == NULL) return ;
  stack<Node*> traverse;
  traverse.push(root);
  while (traverse.size()) {
    Node *p = traverse.top();
    cout << p->val << " ";
    traverse.pop();
    if (p->right) traverse.push(p->right);
    if (p->left) traverse.push(p->left);
  }
}

void debugStack3(Node *root) {
  if (root == NULL) return ;
  stack<Node*> traverse;
  traverse.push(root);
  Node *lastPop = NULL;
  while (traverse.size()) {
    Node *top = traverse.top();
    if ((top->left == NULL && top->right == NULL) ||
         top->right == lastPop) {
      cout << top->val << " ";
      traverse.pop();
      lastPop = top;
    } else {
      if (top->right) traverse.push(top->right);
      if (top->left) traverse.push(top->left);
    }
  }
}

void destroy(Node *root) {
  if (root == NULL) return;
  else {
    destroy(root->left);
    destroy(root->right);
    delete root;
  }
}

int main(void) {
  vector<int> data = {1,2,3,EMPTY,EMPTY,4,5};
  //vector<int> data = {EMPTY};
  Node *root = init(data);
  debug(root); cout << endl;
  debugStack(root); cout << endl;
  debugStack2(root); cout << endl;
  debugStack3(root); cout << endl;
  destroy(root);
  
  return 0;
}
