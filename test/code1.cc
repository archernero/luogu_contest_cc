#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

template<class InputIterator, class UnaryPredicate>
InputIterator find_all (InputIterator first, InputIterator last, UnaryPredicate pred)
{
    while (first!=last) {
        if (pred(*first)) return first;
        ++first;
    }
    return last;
}


int main(int argc, char const *argv[])
{
    vector<string> a = {"1", "2", "3", "4", "5"};
    
    // vector<string>::const_iterator iter = find_if(a.cbegin(), a.cend(), [](const string& i){
    //     return stoi(i) % 2 == 0;
    // });
    // vector<string>::iterator iter = find_if(a.begin(), a.end(), [](const string& i){
    //     return stoi(i) % 2 == 0;
    // });
    // cout << *iter << endl;

    // std::copy_if(a.begin(), a.end(), std::ostream_iterator<string>(std::cout, "\n"), [](const string& i) {
    //     return stoi(i) % 2 == 0;
    // });

    std::vector<string> matches;
    std::copy_if(a.begin(), a.end(), std::back_inserter(matches), [](const string& i) {
        return stoi(i) % 2 == 0;
    });
    
    for (string& tmp: matches) {
        cout << tmp << endl;
    }
    
    return 0;
}
