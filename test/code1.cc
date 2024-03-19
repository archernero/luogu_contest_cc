#include <vector>
#include <string>
#include <iostream>
using namespace std;

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

    std::unordered_map<std::string, std::string> key_to_query;
    key_to_query.reserve(10);
    key_to_query["1"] = "1,2,3";
    for (auto& iter: key_to_query) {
        cout << iter.first << ": " << iter.second;
    }
    
    // std::unordered_map<std::string, std::string>::iterator iter = key_to_query.begin();
    // while (iter != key_to_query.end()) {
    //     cout << iter->first << ": " << iter->second;
    //     iter++;
    // }

    cout << endl;
    return 0;
}
