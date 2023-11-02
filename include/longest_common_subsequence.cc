#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;
void test_longest_common_subsequence() {
    string a = "3456";
    string b = "7356";
    uint16_t a_len = a.size();
    uint16_t b_len = b.size();
    vector<vector<uint16_t> > mem(a_len + 1, vector<uint16_t>(b_len + 1));
    // uint16_t mem[a_len + 1][b_len + 1];
    // 初始化都是0
    for (uint16_t i = 1; i < a_len + 1; i++) {
        for (uint16_t j = 1; j < b_len + 1; j++) {
            if (a.at(i - 1) == b.at(j - 1)) {
                mem[i][j] = mem[i - 1][j - 1] + 1;
            } else {
                mem[i][j] = max(mem[i - 1][j], mem[i][j - 1]);
            }
        }
    }
    cout << mem[a_len][b_len] << endl;
}

int main(int argc, char const *argv[])
{
    test_longest_common_subsequence();
    return 0;
}
