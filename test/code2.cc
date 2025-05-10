#include <algorithm>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

// #include <ctime>
using namespace std;

struct Person {
    string name;
    int age;
};

void test1() {
    vector<string> a = {"1", "2", "3"};
    // for (string& k : a) {
    //     cout << k << " ";
    // }
    vector<uint64_t> b;
    for (string& k : a) {
        b.emplace_back(stoll(k));
    }
    for (uint64_t k : b) {
        cout << k << " ";
    }
    cout << endl;
}


void test2() {
    vector<pair<int, int> > tmp;
    pair<int, int> a = std::make_pair(0, 1);
    tmp.emplace_back(a);
    tmp.push_back({2, 3});
    tmp.emplace_back(make_pair(1, 0));
    tmp.emplace_back(4, 5);
    std::sort(tmp.begin(), tmp.end(), [](const pair<int, int>& a, const pair<int, int>& b){
        return a.first < b.first;
    });
    for (auto& t : tmp) {
        cout << t.first << ": " << t.second << "\n";
    }
    cout << endl;
}

void test3() {
    vector<int> tmp;
    for (int i = 0; i < 10; i++) {
        tmp.emplace_back(i);
    }
    // 所以要保证有序
    tmp.insert(tmp.begin() + 2, 101);
    tmp.insert(tmp.begin() + 0, 100);
    
    for (int t : tmp) {
        cout << t << "\n";
    }
    cout << endl;
}

void test4() {
    // string a = "0.97643999";
    // float b = std::stof(a);
    // cout << b << endl;

    unordered_set<string> tmp;
    tmp.emplace("a");
    if (tmp.size() > 0) {
        cout << "tmp is not empty." << endl;
    }

    unordered_map<string, string> a;
    if (a.empty()) {
        cout << "a is empty" << endl;
    }
}

long get_tomorrow_time() 
{  
    time_t t = time(NULL); 
    t += 86400;
    struct tm* tm = localtime(&t);  
    tm->tm_hour = 0;  
    tm->tm_min = 1;  
    tm->tm_sec = 0;
    return mktime(tm); 
}

// void get_day_time_() 
// {  
//     std::time_t t = time(nullptr);
//     struct tm* tm = localtime(&t);
//     std::stringstream time_str;
    
//     // 以下依次把年月日的数据加入到字符串中
// 	time_str << tm->tm_year + 1900;
// 	time_str << tm->tm_mon + 1;
// 	time_str << tm->tm_mday;
//     cout << time_str.str() << endl;

// }


std::string get_time_as_string(std::string format_string, time_t the_time)
{
    const struct tm* timeinfo = localtime(&the_time);

    std::ostringstream os;
    os << std::put_time(timeinfo, format_string.c_str());
    return os.str();
}

void insert_test() {
    vector<string> a = {"1", "2", "3"};
    // cout << a.size() << endl;
    vector<pair<int, string> > pos = {{0, "x"}, {3, "b"}, {5, "d"}};
    for (auto x : pos) {
        uint32_t size = a.size();
        if (x.first < size) {
            a.insert(a.begin() + x.first, x.second);
        } else {
            cout << x.first <<":"<< size << "\n";
            a.emplace_back(x.second);
        }
    }
    for (auto x:a) {
        cout << x << "\n";
    }
    cout << endl;
}

void map_iter_test() {
    unordered_map<string, string> a;
    if (a.empty()) {
        a.emplace("1", "a");
        a.emplace("2", "b");
    }
    
    for (auto iter: a) {
        cout << iter.first << ": " << iter.second << "\n";
    }
}

void int_to_float() {
    int64_t a = 10;
    int64_t b = 3;
    float c = a / static_cast<float>(b);
    cout << c << endl;
}

void test_sort_person() {
    vector<Person> ps;
    Person p1 = {"zhangsan", 16};
    Person p2 = {"lisi", 16};
    Person p3 = {"wangwu", 16};

    ps.emplace_back(p2);
    ps.emplace_back(p3);
    ps.emplace_back(p1);

    std::sort(ps.begin(), ps.end(), [](const Person& x1, const Person& x2) {
        return x1.age > x2.age;
    });

    for (const auto& p: ps) {
        cout << p.name << "\n";
    }
    cout << endl;
}

bool is_vaild_user(const std::string& num, int target) {
    int source = std::stoi(num);
    return source & target;
}


void test_swap_shrink_to_fit() {
    vector<string> data1;
    data1.reserve(10);
    
    data1.emplace_back("a");
    vector<string> data2;
    data2.emplace_back("b");

    data1.clear();
    data1.shrink_to_fit();
    std::cout << data1.size() << std::endl;
    std::cout << data1.capacity() << std::endl;

    data1.swap(data2);
    std::cout << data1.size() << std::endl;
    std::cout << data1.capacity() << std::endl;
    std::cout << data2.size() << std::endl;
    std::cout << data2.capacity() << std::endl;
}

void test_insert_vector() {
    vector<string> data1;
    data1.emplace_back("a");

    vector<string> data2;
    data2.emplace_back("b");

    data1.insert(data1.end(), data2.begin(), data2.end());

    for (auto& x : data1) {
        cout << x << endl;
    }
    
}

void test_share_ptr_vector() {
    // std::shared_ptr<std::vector<std::string>> user_imprs =
    //     std::make_shared<std::vector<std::string>>();
    // user_imprs.get()->emplace_back("aaa");
    // // for (size_t i = 0; i < user_imprs.get()->size(); i++) {
    // //     cout << user_imprs->data()[i] << endl;
    // // }
    // for (std::string& a : *user_imprs) {
    //     cout << a << endl;
    // }
    
    int a = 100;
    vector<int> b{a, a, a};
    for (int x : b) {
        cout << "num is: " << x << endl;
    }
}


// command + shift + p
int main(int argc, char const *argv[])
{
    // long x = get_tomorrow_time();
    // cout << x << endl;

    // std::time_t t = time(nullptr);
    // std::string format_string = "_%Y%m%d";

    // cout << get_time_as_string(format_string, t) << endl;

    test4();
    unordered_set<string> bbb;
    bbb.emplace("a");
    if (bbb.find("a") != bbb.end()) {
        cout << "bbbbbbbbb" << endl;
    }
    vector<string> c(bbb.begin(), bbb.end());
    for (auto& tmp : c) {
        cout << tmp << "\n";
    }
    cout << endl;

    string x;
    x.append("a");
    x.append("_");
    x.append("b");
    cout << x << endl;

    map_iter_test();
    int_to_float();

    test_sort_person();

    // string a = "1";
    // if (is_vaild_user(a, 1)) {
    //     cout << "yes" << endl;
    // } else {
    //     cout << "no" << endl;
    // }

    // test_swap_shrink_to_fit();

    test_insert_vector();
    std::to_string(1);
    for (int i = 0; i < 10; i += 2) {
        cout << i << "\n";
    }
    cout << endl;

    test_share_ptr_vector();

    return 0;
}
