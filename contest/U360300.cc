#include <iostream>
#include <vector>
using namespace std;


void solution(uint32_t n, vector<int>& a) {
    if (n == 1) {
        cout << a[0];
        return;
    }
    vector<int> mem(n);
    mem[0] = a[0];
    for (uint32_t i = 1; i < n; i++) {
        mem[i] = mem[i - 1] + a[i];
    }
    int ans = mem[0];
    for (uint32_t i = 1; i < n; i++) {
        ans += mem[i];
        for (uint32_t j = 0; j < i; j++) {
            ans += (mem[i] - mem[j]);
        }
    }
    cout << ans;
}


int main(int argc, char const *argv[])
{
    // 主函数进行输入的读取
    uint32_t n;
    cin >> n;
    vector<int> a(n);
    for (uint32_t i = 0; i < n; i++) {
        cin >> a[i];
    }
    // solution 进行算法设计
    solution(n, a);
    // -------------
    return 0;
}
