#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "union_find.h"

using namespace std;

// template<class InputIterator, class UnaryPredicate>
// InputIterator find_if (InputIterator first, InputIterator last, UnaryPredicate pred)
// {
//     while (first!=last) {
//         if (pred(*first)) return first;
//         ++first;
//     }
//     return last;
// }

void test_vector() {
  vector<int> a;
  a.reserve(10);
  for (int i = 0; i < 10; i++) {
    a.emplace_back(i);
  }
  reverse(a.begin(), a.end());
  cout << a.back() << endl;
}

int findCircleNum(vector<vector<int>>& is_connected) {
  // leetcode 547
  int nums = is_connected.size();
  UnionFind uf(nums);
  for (int i = 0; i < nums; i++) {
    for (int j = 0; j < i; j++) {
      if (is_connected[i][j]) {
        uf.union_func(i, j);
      }
    }
  }
  int ans = 0;
  for (int i = 0; i < nums; i++) {
    if (i == uf.find(i)) {
      ans += 1;
    }
  }
  return ans;
}

bool validTree(int n, vector<vector<int>>& edges) {
  // leectcode 261
  UnionFind uf(n);
  for (auto tmp: edges) {
    int f = tmp[0];
    int t = tmp[1];
    if (uf.find(f) != uf.find(t)) {
      uf.union_func(f, t);
    } else {
      return false;
    }
  }
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (i == uf.find(i)) count += 1;
  }
  return count == 1;
}

int main(int argc, char const* argv[]) {
  vector<string> a = {"1", "2", "3", "4", "5"};

  // vector<string>::const_iterator iter = find_if(a.cbegin(), a.cend(), [](const string& i){
  //     return stoi(i) % 2 == 0;
  // });
  // vector<string>::iterator iter = find_if(a.begin(), a.end(), [](const string& i){
  //     return stoi(i) % 2 == 0;
  // });
  // cout << *iter << endl;

  // std::copy_if(a.begin(), a.end(), std::ostream_iterator<string>(std::cout, "\n"), [](const string& i) {
  //     return stoi(i) % 2 == 0;
  // });

  // std::vector<string> matches;
  // std::copy_if(a.begin(), a.end(), std::back_inserter(matches), [](const string& i) {
  //     return stoi(i) % 2 == 0;
  // });

  // for (string& tmp: matches) {
  //     cout << tmp << endl;
  // }

  test_vector();

  return 0;
}
