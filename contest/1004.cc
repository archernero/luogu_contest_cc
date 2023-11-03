/*
这个题注意是两个路径,不是重复走两遍的和,重复走两遍其实是一个路径并不是和乘2
所以尽量选取重复度不高的路径拿到更多的数是核心。
后面就都用int得了 最多加个long long => uint32_t写着太麻烦了
*/
#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int robot(int n, vector<vector<vector<vector<int> > > >& mem, const vector<vector<int> >& data, int x1, int y1, int x2,
          int y2) {
  if (mem[x1][y1][x2][y2] != -1) {
    return mem[x1][y1][x2][y2];
  }
  if (x1 == n && y1 == n && x2 == n && y2 == n) return 0;
  int res = 0;
  // 都向下
  if (x1 < n - 1 && x2 < n - 1) {
    res = max(res, robot(n, mem, data, x1 + 1, y1, x2 + 1, y2) + data[x1 + 1][y1] + data[x2 + 1][y2] -
                       data[x1 + 1][y1] * (x1 + 1 == x2 + 1 && y1 == y2));
  }
  // 1 下 2 右
  if (x1 < n - 1 && y2 < n - 1) {
    res = max(res, robot(n, mem, data, x1 + 1, y1, x2, y2 + 1) + data[x1 + 1][y1] + data[x2][y2 + 1] -
                       data[x1 + 1][y1] * (x1 + 1 == x2 && y1 == y2 + 1));
  }
  // 1 右 2 下
  if (y1 < n - 1 && x2 < n - 1) {
    res = max(res, robot(n, mem, data, x1, y1 + 1, x2 + 1, y2) + data[x1][y1 + 1] + data[x2 + 1][y2] -
                       data[x1][y1 + 1] * (x1 == x2 + 1 && y1 + 1 == y2));
  }
  // 都向右
  if (y1 < n - 1 && y2 < n - 1) {
    res = max(res, robot(n, mem, data, x1, y1 + 1, x2, y2 + 1) + data[x1][y1 + 1] + data[x2][y2 + 1] -
                       data[x1][y1 + 1] * (x1 == x2 && y1 + 1 == y2 + 1));
  }

  mem[x1][y1][x2][y2] = res;
  return res;
}

void solution(int n, const vector<vector<int> >& data) {
  if (n == 1) {
    cout << data[0][0] << endl;
    return;
  }

  // int mem[n][n][n][n];  // 所以为什么c++竞赛需要大量预定义的数组 而在实际工业就没啥用
  vector<vector<vector<vector<int> > > > mem;
  for (int i = 0; i < n; i++) {
    vector<vector<vector<int> > > tmp1;
    for (int j = 0; j < n; j++) {
      vector<vector<int> > tmp2;
      for (int k = 0; k < n; k++) {
        vector<int> tmp3;
        for (int l = 0; l < n; l++) {
          tmp3.emplace_back(-1);
        }
        tmp2.emplace_back(tmp3);
      }
      tmp1.emplace_back(tmp2);
    }
    mem.emplace_back(tmp1);
  }
  // 因为每次只能向下或者向右，因此从左上角到右下角的不管什么路径，步数一定是相同的 [这个思路太重要了]
  // auto robot = [&](int x1, int y1, int x2, int y2) {
  //     if (mem[x1][y1][x2][y2] != -1) {
  //         return mem[x1][y1][x2][y2];
  //     }
  //     if (x1 == n && y1 == n && x2 == n && y2 == n) return 0;
  //     int res = 0;
  //     // 都向下
  //     if (x1 < n - 1 && x2 < n - 1) {
  //         res = max(res, robot(x1 + 1, y1, x2 + 1, y2))
  //     }

  // };
  cout << robot(n, mem, data, 0, 0, 0, 0) + data[0][0] << endl;
}

int main(int argc, char const* argv[]) {
  int n;
  cin >> n;
  vector<vector<int> > matrix(n, vector<int>(n));
  while (1) {
    int x, y, v;
    cin >> x >> y >> v;
    if (x == 0 && y == 0 && v == 0) {
      break;
    }
    matrix[x - 1][y - 1] = v;
  }
  solution(n, matrix);
  return 0;
}
