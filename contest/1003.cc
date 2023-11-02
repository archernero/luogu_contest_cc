#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#define ll long long

using namespace std;

void solution(uint32_t n, const vector<vector<uint32_t> >& data, uint32_t tx, uint32_t ty) {
  unordered_map<uint32_t, unordered_map<uint32_t, uint32_t> > mem;
  for (uint32_t i = 0; i < n; i++) {
    uint32_t cx, cy, ex, ey;
    cx = data[i][0];
    cy = data[i][1];
    ex = cx + data[i][2];
    ey = cy + data[i][3];
    for (uint32_t r = cx; r <= ex; r++) {
      for (uint32_t c = cy; c <= ey; c++) {
        mem[r][c] = i + 1;
      }
    }
  }
  if (mem.find(tx) != mem.end()) {
    if (mem[tx].find(ty) != mem[tx].end()) {
      cout << mem[tx][ty] << endl;
      return;
    }
  }
  cout << -1 << endl;
}

void solution_v2(uint32_t n, const vector<vector<uint32_t> >& data, uint32_t tx, uint32_t ty) {
  // vector<vector<uint32_t> > mem(n, vector<uint32_t>(4));
  int ans = -1;
  for (int i = 0; i < n; i++) {
    uint32_t cx, cy, ex, ey;
    cx = data[i][0];
    cy = data[i][1];
    ex = cx + data[i][2];
    ey = cy + data[i][3];
    if (tx >= cx && tx <= ex && ty >= cy && ty <= ey) {
      ans = (i + 1);
    }
  }

  cout << ans << endl;
}

int main(int argc, char const* argv[]) {
  uint32_t n;
  cin >> n;
  vector<vector<uint32_t> > data(n, vector<uint32_t>(4));
  for (uint32_t i = 0; i < n; i++) {
    for (uint32_t j = 0; j < 4; j++) {
      cin >> data[i][j];
    }
  }
  uint32_t tx, ty;
  cin >> tx;
  cin >> ty;

  solution_v2(n, data, tx, ty);
  return 0;
}