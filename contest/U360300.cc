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

void solution1(uint32_t n, vector<int>& a) {
    if (n == 1) {
        cout << a[0] << '\n';
        return;
    }    
    long long ans = 0;
    for (uint32_t i = 0; i < n; i++) {
        // ans += cur_num * ((i + 1) * (1 + n - (i + 1)));
        // 1ll这个需要放到前面才转换类型
        ans += 1ll * a[i] * (i + 1) * (n - i);
    }
    cout << ans << '\n';
}

void solution3() {
    int n;
    cin >> n;

    long long res = 0;
    for(int i = 1; i <= n; i++){
        int x;
        cin >> x;
        res += 1ll * i * (n - i + 1) * x;
    }

    cout << res << '\n';
}

int main(int argc, char const *argv[])
{
    // 主函数进行输入的读取
    uint32_t n;  // uint32_t 也就是 0 到 4294967295
    cin >> n;
    vector<int> a(n);
    for (uint32_t i = 0; i < n; i++) {
        cin >> a[i];
    }
    // solution 进行算法设计 2 1 2 => 6
    solution1(n, a);
    // -------------
    return 0;
}
