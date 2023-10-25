#pragma once
#include <iostream>
#include <vector>

using namespace std;
void input_with_vector_size() {
    uint32_t n;
    cin >> n;
    vector<uint32_t> p(n);
    for (uint32_t i = 0; i < n; i++) {
        cin >> p[i];
    }
}

void input_without_vector_size() {
    vector<uint32_t> p;
    uint32_t i;
    do {
        cin >> i;
        p.emplace_back(i);
    } while (getchar() != '\n' );
}