#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
class WeightedQuickUnionUF {
 public:
  WeightedQuickUnionUF(int n) {
    // 初始化链接数组和统计数组
    count_ = n;
    ids_.reserve(n);
    for (int i = 0; i < n; i++) {
      ids_.emplace_back(i);
    }
    sz_.reserve(n);
    for (int i = 0; i < n; i++) {
      sz_.emplace_back(i);
    }
  }
  virtual ~WeightedQuickUnionUF(){};

  int find(int p) {
    while (p != ids_[p]) {
      p = ids_[p];
    }
    return p;
  }

  void union_func(int p, int q) {
    int i = find(p);
    int j = find(q);
    if (i == j) return;
    if (sz_[i] < sz_[j]) {
      ids_[i] = j;
      sz_[j] += sz_[i];
    } else {
      ids_[j] = i;
      sz_[i] += sz_[j];
    }
  }

  bool connected(int p, int q) { return find(p) == find(q); }

  /*
   * 返回所有图的数量 [独立节点算一个图]
   */
  int union_count() {
    int single_count = 0;
    for (int i = 0; i < count_; i++) {
      if (ids_[i] == i) {
        single_count += 1;
      }
    }
    return single_count;
  }

  /*
   * 统计图的数量和内部细节
   */
  void print_info() {
    unordered_map<int, vector<int> > ans;
    for (int i = 0; i < count_; i++) {
      int root_id = i;
      if (i != ids_[i]) {
        root_id = find(i);
      }
      ans[root_id].emplace_back(i);
      // if (ans.find(root_id) != ans.end()) {
      //     ans[root_id].emplace_back(i);
      // }
    }
    // 1. 打印连通图的数量
    cout << "Total graph count: " << ans.size() << ".\n";
    // 2. 打印不止一个节点的连通图数量
    for (auto kv : ans) {
      if (kv.second.size() > 1) {
        cout << kv.first << " graph count: " << kv.second.size() << ".\n";
      }
    }
  }

 private:
  int count_;  // 节点的数量
  vector<int> ids_;  // 父链接数组
  vector<int> sz_;  // (由触点索引的)各个根节点所对应的分量的大小
};