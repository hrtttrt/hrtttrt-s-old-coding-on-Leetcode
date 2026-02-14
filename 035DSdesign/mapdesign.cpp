#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;
/*1、setAll功能的哈希表
*/
class MyMap 
{
    // pair <value, cnt> // 加时间戳技术
    std::unordered_map<int, std::pair<int, int>> umap;
    int setAllValue;
    int setAllTime{0};
    int cnt{1};
public:
    void put(int key, int value) 
    {
        umap[key] = {value, cnt++}; 
    }

    int get(int key) 
    {
        if (!containsKey(key)) {
            return -1;
        }

        if (umap[key].second < setAllTime) {
            return setAllValue;
        }
        return umap[key].first;
    }

    bool containsKey(int key)
    {
        if (umap.find(key) == umap.end()) {
            return false;
        }
        return true;
    }

    void setAll(int value)
    {
        setAllValue = value;
        setAllTime = cnt++;
    }

};

/*2、双向队列实现lru 实现O(1)的时间复杂度，要自己手写双向链表，调用map接口。
注意双向链表的增删查改的边界条件处理（动的那个点是头部点，尾部点，中间点）。特别是在c++的delete
测试链接：https://leetcode.cn/problems/lru-cache/
*/
class doubleNode{  
public:  
    doubleNode(int key, int value){  
        this->next= nullptr;  
        this->pre= nullptr;  
        this->val = value;  
        this->key = key;  
    }  
    int val;  
    int key;  
    doubleNode* next;  
    doubleNode* pre;  
};  
class doubleList{  
public:  
    doubleNode* head;  
    doubleNode* tail;  
    int size;  
    doubleList(){  
        this->head= nullptr;  
        this->tail= nullptr;  
        this->size = 0;  
    }  
    void pushBack(doubleNode* node){  
        //// 这个点在不在链表里  
        // 一个点都没有  
        if (head == nullptr){  
            head = node;  
            tail = node;  
            ++size;  
        } else {  
            node->next = tail;  
            tail->pre = node;  
            tail = node;  
            ++ size;  
        }  
  
    }  
    void moveToTail(doubleNode* node){  
        //不只一个点 & 这个点不在尾部  
        if (node->pre!= nullptr){  
            //恰好那个点是头部,node->next = = nullptr  
            if(node == head){  
                head = node->pre;  
                node->pre->next=node->next;  
//                node->next->pre = node->pre;  
                node->next = tail;  
                node->pre = nullptr;  
                tail->pre = node;  
                tail = node;  
            }  
            else{  
                node->pre->next=node->next;  
                node->next->pre = node->pre;  
                node->next = tail;  
                node->pre = nullptr;  
                tail->pre = node;  
                tail = node;  
            }  
  
        }  
    };  
    void removeHead(){  
        doubleNode* pre = head->pre;  
        // 不止一个点  
        if (head->pre!= nullptr){  
            head->pre->next = nullptr;  
            head->pre = nullptr;  
            head->next = nullptr;  
        } else{  
            tail = nullptr;  
        }  
        delete head;  
        --size;  
        head = pre;  
    }  
  
  
};  
class LRUCache {  
public:  
    LRUCache(int capacity) {  
        this->capacity=capacity;  
        this->list = new doubleList();  
    }  
  
    bool containsKey(int key)  
    {  
        if (umap.find(key) == umap.end()) {  
            return false;  
        }  
        return true;  
    }  
  
    int get(int key) {  
        if (!containsKey(key)) {  
            return -1;  
        }  
        list->moveToTail(umap[key]);  
        return umap[key]->val;  
    }  
  
    void put(int key, int value) {  
        if(containsKey(key)){  
            umap[key]->val=value;  
            list->moveToTail(umap[key]);  
        } else{  
            doubleNode* node = new doubleNode(key,value);  
            if(list->size==capacity){  
                umap.erase(list->head->key);  
                list->removeHead();  
                list->pushBack(node);  
                umap.insert(pair<int,doubleNode*>(key,node));  
            } else{  
                list->pushBack(node);  
                umap.insert(pair<int,doubleNode*>(key,node));  
            }  
        }  
  
    }  
private:  
    int capacity;  
    doubleList* list;  
    unordered_map<int, doubleNode*> umap;  
};

/*3、插入、删除和获取随机元素O(1)时间的结构
remove直接实现会导致连续数组有洞 方法：用最后一个补到挖出洞的位置
测试链接：https://leetcode.cn/problems/insert-delete-getrandom-o1/class
*/
RandomizedSet {  
public:  
    RandomizedSet() {  
        this->count=0;  
        srand((unsigned)time(NULL));  
    }  
  
    bool insert(int val) {  
        auto result = m.insert(pair<int,int>(val,count));  
        if (result.second){  
            v.push_back(val);  
            count++;  
            return true;  
        } else{  
            return false;  
        }  
    }  
  
    bool remove(int val) {  
        auto pos = m.find(val);  
        if (pos!=m.end()){  
            int vpos = pos->second;  
            v[vpos] = v[count-1];  
            m.find(v[vpos])->second=vpos;  
            v.pop_back();  
            m.erase(pos);  
            count--;  
            return true;  
        } else{  
            return false;  
        }  
  
    }  
  
    int getRandom() {  
        int randomIndex = rand()%v.size();  
        return v[randomIndex];  
    }
    private:  
    vector<int> v;  
    int count;
    std::unordered_map<int,int> m;  
};

/*4、插入、删除和获取随机元素O(1)时间且允许有重复数字的结构
测试链接：https://leetcode.cn/problems/insert-delete-getrandom-o1/
*/

class RandomizedCollection {  
public:  
    unordered_map<int, unordered_set<int>> idx;  
    vector<int> nums;  
  
    /** Initialize your data structure here. */  
    RandomizedCollection() {  
  
    }  
  
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */  
    bool insert(int val) {  
        nums.push_back(val);  
        idx[val].insert(nums.size() - 1);  
        return idx[val].size() == 1;  
    }  
  
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */  
    bool remove(int val) {  
        if (idx.find(val) == idx.end()) {  
            return false;  
        }  
        int i = *(idx[val].begin());  
        nums[i] = nums.back();  
        idx[val].erase(i);  
        idx[nums[i]].erase(nums.size() - 1);  
        //最后一个直接删不需要插入  
        if (i < nums.size() - 1) {  
            idx[nums[i]].insert(i);  
        }  
        if (idx[val].size() == 0) {  
            idx.erase(val);  
        }  
        nums.pop_back();  
        return true;  
    }  
  
    /** Get a random element from the collection. */  
    int getRandom() {  
        return nums[rand() % nums.size()];  
    }  
}

/*5、请你设计一个用于存储字符串计数的数据结构，并能够返回计数最小和最大的字符串。 
老师课上说的是用一个hash表+一个桶的双向链表 其实和上一题很像。桶就是hash 
如果是用set来做，无法做到方便正常的再多种情况下切换min索引，
因为删了一个set之后，不知道指向这个set的min该向小的数动还是大的数动，无法找到下一个数，但是双向链表可以
测试链接：https://leetcode.cn/problems/all-oone-data-structure/
*/
class Bucket {  
public:  
    set<string> set;  
    int cnt;  
    Bucket* last;  
    Bucket* next;  
  
    Bucket(const string& s, int c) {  
        set.insert(s);  
        cnt = c;  
    }  
};  
class AllOne {  
public:  
    Bucket* head;  
  
    Bucket* tail;  
  
    unordered_map<string , Bucket*> umap;  
    AllOne() {  
        head = new Bucket("", 0);  
        tail = new Bucket("", 2147483647);  
        head->next = tail;  
        tail->last = head;  
    }  
  
    void insert(Bucket* cur, Bucket* pos) {  
        cur->next->last = pos;  
        pos->next = cur->next;  
        cur->next = pos;  
        pos->last = cur;  
    }  
  
    void remove(Bucket* cur) {  
        cur->last->next = cur->next;  
        cur->next->last = cur->last;  
        delete cur;  
    }  
  
    bool containsKey(string key){  
        if(umap.find(key)!=umap.end()){  
            return true;  
        }  
        return false;  
    }  
    void inc(string key) {  
        if (!containsKey(key)) {  
            if (head->next->cnt == 1) {  
                umap.insert(pair<string, Bucket*>(key, head->next));  
                head->next->set.insert(key);  
            } else {  
                Bucket * newBucket = new Bucket(key, 1);  
                umap.insert(pair<string, Bucket*>(key, newBucket));  
                insert(head, newBucket);  
            }  
        } else {  
            Bucket* bucket = umap[key];  
            if (bucket->next->cnt == bucket->cnt + 1) {  
                umap[key] = bucket->next;  
//                umap.insert(pair<string, Bucket*>(key, bucket->next));  
                bucket->next->set.insert(key);  
            } else {  
                Bucket* newBucket = new Bucket(key, bucket->cnt + 1);  
                umap[key] = newBucket;  
//                umap.insert(pair<string, Bucket*>(key, newBucket));  
                insert(bucket, newBucket);  
            }  
            bucket->set.erase(key);  
            if (bucket->set.empty()) {  
                remove(bucket);  
            }  
        }  
    }  
  
    void dec(string key) {  
        Bucket* bucket = umap[key];  
        if (bucket->cnt == 1) {  
            umap.erase(key);  
        } else {  
            if (bucket->last->cnt == bucket->cnt - 1) {  
                umap[key] = bucket->last;  
//                umap.insert(pair<string, Bucket*>(key, bucket->last));  
                bucket->last->set.insert(key);  
            } else {  
                Bucket* newBucket = new Bucket(key, bucket->cnt - 1);  
                umap[key] = newBucket;  
//                umap.insert(pair<string, Bucket*>(key, newBucket));  
                insert(bucket->last, newBucket);  
            }  
        }  
        bucket->set.erase(key);  
        if (bucket->set.empty()) {  
            remove(bucket);  
        }  
    }  
  
    string getMaxKey() {  
        return *tail->last->set.begin();  
    }  
  
    string getMinKey() {  
        return *head->next->set.begin();  
    }  
  
};