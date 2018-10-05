#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x):val(x), next(NULL) {}
};

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

void debug(ListNode *head) { 
  cout << "[debug] ";
  while(head) {
    cout << head->val << "  ";
    head = head->next;
  }
  cout << endl;
}

class Solution {
public:
  ListNode* insertionSortList(ListNode* head) {
    head = head == NULL ? NULL : quickSortList(head);
    return head;
  }

  ListNode* quickSortList(ListNode *head) {
    if (head->next == NULL) return head;
    ListNode *ea = head;
    ListNode *eb = head;

    ListNode *la = NULL;
    ListNode *lb = NULL;
    ListNode *ra = NULL;
    ListNode *rb = NULL;
    ListNode *p = head->next;
    while (p) {
      if (p->val < ea->val) {
        if (la == NULL) la = lb = p;
        else lb = lb->next = p;
      } else if (p->val == ea->val) {
        eb = eb->next = p;
      } else {
        if (ra == NULL) ra = rb = p;
        else rb = rb->next = p;
      }
      p = p->next;
    }
    if (lb) {
      lb->next = NULL;
      la = quickSortList(la);
      lb = la;
      while(lb->next) lb = lb->next;
      lb->next = ea;
    }
    if (rb) {
      rb->next = NULL;
      ra = quickSortList(ra);
      rb = ra;
      while(rb->next) rb = rb->next;
      rb->next = NULL;
    }
    eb->next = ra;
    //if (la) debug(la); else debug(ea);
    return la == NULL ? ea : la;
  }
};


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
