#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#define ll long long

using namespace std;

bool check(uint32_t x, uint32_t y, unordered_map<uint32_t, unordered_set<uint32_t> >& mem) {
  if (mem.find(x) != mem.end()) {
    if (mem[x].count(y) > 0) {
      return true;
    }
  }
  return false;
}

void solution(uint32_t tx, uint32_t ty, uint32_t mx, uint32_t my) {
  // https://blog.csdn.net/bqw18744018044/article/details/81665898
  // 防止答案太大...[这里面的题都是这个尿性,无语]
  vector<vector<ll> > mem(tx + 1, vector<ll>(ty + 1));
  // can visited => 0
  int pos[9][2] = {{0, 0}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}, {1, -2}, {2, -1}, {2, 1}, {1, 2}};
  unordered_map<uint32_t, unordered_set<uint32_t> > ss;
  for (auto& tmp : pos) {
    int tmp_x = mx + tmp[0];
    int tmp_y = my + tmp[1];
    if (tmp_x < 0 || tmp_x > tx || tmp_y < 0 || tmp_y > ty) {
      continue;
    }
    ss[tmp_x].emplace(tmp_y);
  }

  // init
  for (uint32_t i = 0; i <= ty; i++) {
    if (check(0, i, ss)) {
      mem[0][i] = 0;
      break;
    } else {
      mem[0][i] = 1;
    }
  }
  for (uint32_t i = 0; i <= tx; i++) {
    if (check(i, 0, ss)) {
      mem[i][0] = 0;
      break;
    } else {
      mem[i][0] = 1;
    }
  }
  for (uint32_t i = 1; i <= tx; i++) {
    for (uint32_t j = 1; j <= ty; j++) {
      if (check(i, j, ss)) {
        mem[i][j] = 0;
      } else {
        mem[i][j] = mem[i - 1][j] + mem[i][j - 1];
      }
    }
  }
  cout << mem[tx][ty] << "\n";
}

int main(int argc, char const* argv[]) {
  uint32_t tx, ty, mx, my;
  cin >> tx;
  cin >> ty;
  cin >> mx;
  cin >> my;

  solution(tx, ty, mx, my);
  return 0;
}
