#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <assert.h>

#include "include/union_find.h"
using namespace std;

void test_assert() {
    vector<string> req_keys;
    req_keys.emplace_back("1234");
    vector<string> vals;
    vals.emplace_back("");
    
    vector<string> req_failed_keys;
    std::unordered_map<std::string, std::string> key_to_query;
    try {
        // assert(req_keys.size() == vals.size());
        for (size_t i = 0; i < vals.size(); ++i) {
            std::string& key = req_keys[i];
            if (vals[i] != "") {
                key_to_query[key] = std::move(vals[i]);
            } else {
                req_failed_keys.emplace_back(key);
            }
        }
    } catch (std::exception& e) {
        std::cout << "wrong";
    }
    if (req_failed_keys.size() > 0) {
        for (std::string& key : req_failed_keys) {
            printf("Failed fetch hot query key %s \n", key.c_str());
        }
    }
}


int main(int argc, char const *argv[])
{
    // string a = "";
    // if (a.empty()) {
    //     cout << "a is empty" << endl;
    // }

    // vector<string> a;
    // for (int i = 0; i < 10; i++) {
    //     a.emplace_back(to_string(i));
    // }
    // vector<string> b;
    // b.insert(b.end(), a.begin(), a.end());
    // for (string& i: b) {
    //     cout << i << "\n";
    // }
    // cout << endl;
    // if (!a.empty()) {
    //     cout << "testing pass" << endl;
    // }

    // unordered_map<string, string> key_to_query;
    // key_to_query.reserve(10);
    // key_to_query["1"] = "1,2,3";
    // for (auto& iter: key_to_query) {
    //     std::cout << iter.first << ": " << iter.second;
    // }
    // int64_t a = 100;
    // std::cout << to_string(a).c_str();

    unordered_map<string, std::pair<double, double> > test_map_pair {
        {"a", std::make_pair(0.0, 0.0)},
        {"b", std::make_pair(1.0, 1.0)}
    };
    std::cout << test_map_pair["a"].first << "=>" << test_map_pair["a"].second << "\n";
    std::cout << test_map_pair["b"].first << "=>" << test_map_pair["b"].second << "\n";
    double x = 4.0;
    x = min(pow(x, 0.5), 1.5);
    std::cout << x << endl;

    unordered_set<std::string> YONG_AGE_TAGS = {"0", "1", "2"};
    // std::unordered_map<std::string, std::string>::iterator iter = key_to_query.begin();
    // while (iter != key_to_query.end()) {
    //     cout << iter->first << ": " << iter->second;
    //     iter++;
    // }

    std::vector<std::string> hot_types_ = {"a", "b", "c"};
    for (string& tmp : hot_types_) {
        cout << tmp << "\n";
    }

    int total_num = 35;
    int each_num = total_num / hot_types_.size();
    cout << each_num << "\n";

    std::unordered_set<string> visited_groups;
    // uint64_t t = lexical_cast<uint64_t>("23456");

    test_assert();

    std::cout << "*********** end **************" << endl;
    return 0;
}
