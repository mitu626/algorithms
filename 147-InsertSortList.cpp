#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x):val(x), next(NULL) {}
};

class Solution {
public:
  ListNode* insertionSortList(ListNode* head) {
    ListNode p(-10000), *tail, *go = head;
    tail = &p;
    if (head) {
      while (go) {
        ListNode *temp = &p;
        while (temp != tail && temp->next &&
               temp->next->val < go->val) {
            temp = temp->next;
        }
        ListNode *t = go;
        go = go->next;
        t->next = temp->next;
        temp->next = t;
        if (temp == tail) {
          tail = t;
        }
      }
    }
    return p.next;
  }

};

void debug(ListNode *head) { 
  cout << "[debug] ";
  while(head) {
    cout << head->val << "  ";
    head = head->next;
  }
  cout << endl;
}

ListNode* init(vector<int> data) {
  ListNode *head = NULL, *go = NULL;
  for(auto it = data.begin();it != data.end();it++) {
    ListNode *p = new ListNode(*it);   
    if (it == data.begin()) head = go = p;
    go = go->next = p;
  }
  return head;
}

void destroy(ListNode *head) {
  while(head) {
    ListNode *p = head;
    head = head->next;
    delete p;
  }
}

int main(void) {
  //vector<int> data = {1,3,9,2,8,4,6,5};
  //vector<int> data = {4,2,1,3};
  vector<int> data = {-1,5,3,4,0};
  ListNode *head = init(data);
  Solution s;
  head = s.insertionSortList(head);
  debug(head);
  
  destroy(head);

  return 0;
}
