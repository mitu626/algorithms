#include <iostream>
#include <unordered_map>

using namespace std;

class LRUCache {
private:
    struct IndexNode {
        int key;
        IndexNode *next;
        IndexNode *prev;
    };
    unordered_map<int, pair<int, int> > cache;
    IndexNode *index;
    IndexNode *head;
    IndexNode *tail;
    int used;
    int size;

    bool check_capacity() {
        return used < size;
    }

    bool check_exist(int key) {
      return get(key) != -1;
    }

public:
    LRUCache(int capacity):
        head(NULL),
        tail(NULL),
        used(0),
        size(capacity) {
        index = new IndexNode[capacity];
    }

    int get(int key) {
      if (cache.find(key) == cache.end()) 
        return -1;
      pair<int, int> data = cache[key];
      int value = data.first;
      int item_index = data.second;
      IndexNode *target = &index[item_index];
      if (target == tail) return value;
      if (target->prev)
        target->prev->next = target->next;
      if (target->next)
        target->next->prev = target->prev;
      if (head == target) 
        head = target->next;
      target->prev = tail;
      target->next = NULL;
      tail = tail->next = target;
      return value;
    }

    void put(int key, int value) {
      if (check_exist(key)) {
        //cout << "[debug] existKey:" << key << endl;
        cache[key].first = value;
      } else if (check_capacity()) {
        //cout << "[debug] createKey:" << key << endl;
        cache[key] = make_pair(value, used); 
        index[used].key = key;
        index[used].prev = tail; 
        index[used].next = NULL;
        if (tail == NULL) {
          head = tail = &(index[used]);
        } else {
          tail = tail->next = &(index[used]);
        }
        ++used;
      } else {
        //cout << "[debug] eraseKey:" << head->key << "  newKey:" << key << endl;
        cache[key] = cache[head->key];
        cache[key].first = value;
        cache.erase(head->key);

        head->key = key;
        tail->next = head;
        head->prev = tail;
        head = head->next;
        head->prev = NULL;
        tail = tail->next;
        tail->next = NULL;
      }
    }

    friend void debug(LRUCache &cache);
};

void debug(LRUCache &cache) {
  LRUCache::IndexNode *head = cache.head;
  cout << "[debug] ";
  while(head) {
    cout << head->key << "  ";
    head = head->next;
  }
  cout << endl;
}


int main(void) {
  LRUCache cache(3);
  cache.put(1,1);
  cache.put(2,2);
  cache.put(3,3);
  cache.put(4,4);
  cout << cache.get(4) << endl;
  cout << cache.get(3) << endl;
  cout << cache.get(2) << endl;
  cout << cache.get(1) << endl;
  cache.put(5,5);
  cout << cache.get(1) << endl;
  cout << cache.get(2) << endl;
  cout << cache.get(3) << endl;
  cout << cache.get(4) << endl;
  cout << cache.get(5) << endl;
  debug(cache);

  return 0;
}











