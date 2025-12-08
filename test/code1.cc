#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <assert.h>
#include <time.h>

#include "include/union_find.h"
using namespace std;

struct SJMusicRgidInfo {
    int64_t gid = 0;
    int64_t stay_time = 0;
    int64_t time_stamp = 0;
    int32_t play_count = 0;
};
typedef std::shared_ptr<SJMusicRgidInfo> SJMusicRgidInfoPtr;

void test_assert() {
    vector<string> req_keys;
    req_keys.emplace_back("1234");
    vector<string> vals;
    vals.reserve(12);
    vals.emplace_back("");
    
    vector<string> req_failed_keys;
    std::unordered_map<std::string, std::string> key_to_query;
    key_to_query.emplace("a", "b");
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

void test_insert() {
    std::cout << "*********** test_insert begin **************\n";
    vector<string> req_keys;
    req_keys.emplace_back("1");
    req_keys.emplace_back("2");
    req_keys.emplace_back("3");
    req_keys.emplace_back("4");
    req_keys.emplace_back("5");

    vector<string> vals;
    vals.insert(vals.begin(), req_keys.begin(), req_keys.begin() + 3);
    vals.at(0) = "6";
    for (string v : vals) {
        cout << v << "\n";
    }

    for (string v : req_keys) {
        cout << v << "\n";
    }

    std::cout << "*********** test_insert end **************" << endl;
}

// void test_left_bracket() {
//     std::cout << "*********** test_left_bracket begin **************\n";
//     string data = "我曾用心爱着你 （热播DJ)";
//     string d = "（";
//     std::vector<std::string> output;
//     size_t found = data.find(d);
//     size_t old_pos = 0;
//     if (found != std::string::npos) {
//         string title = data.substr(0, found);
//         boost::trim_if(title, boost::is_any_of(" \t"));
//         std::cout << "title is " << title << "\n";
//     }
    
//     std::cout << "*********** test_left_bracket begin **************\n" << endl;
// }

void test_and_if() {
    std::cout << "*********** test_and_if begin **************\n";
    vector<string> a;
    a.emplace_back("2");
    if (std::find(a.begin(), a.end(), "1") != a.end()) {
        cout << "find item!\n";
    } else {
        cout << "not find item!\n";
    }

    // if ( 1 > 2 && a[1].empty()) {
    //     cout << "?\n"; 
    // } else {
    //     cout << "normal\n"; 
    // }
    
    
    std::cout << "*********** test_and_if end **************\n" << endl;
}

void test_map_diff() {
    std::cout << "*********** test_map_diff begin **************\n";
    unordered_map<string, string> a;
    uint64_t x = 123527264;
    a["a"] = x;
    for (auto iter : a) {
        // if (iter.second.empty()) {
        //     cout << "ok" << "\n";
        // }
        cout << iter.first <<": " << iter.second << "\n";
    }
    int32_t cur_timestamp = time(nullptr);
    cout << cur_timestamp << "\n";
    
    std::cout << "*********** test_map_diff end **************" << endl;
}

void test_bool_fallback(bool& visited) {
    std::cout << "*********** test_bool_fallback begin **************\n";
    visited = true;

    time_t nt = time(NULL);
    struct timeval tv = {nt, 0};
    struct tm now_time;
    localtime_r(&tv.tv_sec, &now_time);
    cout << now_time.tm_wday << "\n";
    std::cout << "*********** test_bool_fallback begin **************" << endl;
}

void test_int32_scope() {
    std::cout << "*********** test_int32_scope begin **************\n";
    int32_t a = -1;
    if (a != -1) {
        cout << "lll" << "\n";
    } else {
        cout << a << "\n";
    }
    std::cout << "*********** test_int32_scope end **************\n" << endl;
}


void test_valid_play() {
    std::cout << "*********** test_valid_play begin **************\n";
    int64_t a = 15;
    int64_t b = 16;
    float c = a / float(b);
    float d = std::trunc(c);
    if (c - d > 0) {
        if (std::trunc((c - d) * 10) >= 8) {
            d += 1;
        }
    }
    for (int i = 0; i >= 0; i--) {
        cout << i << "\n";
    }
    cout << std::abs(-5) << "\n";

    cout << "c is " << c << "\n";
    cout << "d is " << d << "\n";

    std::cout << "*********** test_valid_play end **************\n" << endl;
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

    test_int32_scope();

    test_valid_play();

    // bool is_visited = false;
    // cout << is_visited << "\n";
    // test_bool_fallback(is_visited);
    // cout << is_visited << "\n";

    std::cout << "*********** main end **************" << endl;
    return 0;
}
