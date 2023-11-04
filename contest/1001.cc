#include <iostream>

using namespace std;

void solution(long long a, long long b) {
  long long ans = a + b;
  cout << ans << "\n";
}

int main(int argc, char const *argv[]) {
  // 构造输入
  long long a;
  long long b;
  cin >> a;
  cin >> b;
  // 解答
  solution(a, b);
  return 0;
}
