#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;
vector<string> merge_recall_queues(vector<vector<string> >& queues, vector<int> weights, int final_size) {
    int total_weight = 0;
    int queue_size = weights.size();
    vector<pair<int, int> > weight_idxs;
    for (int i = 0; i < queue_size; i++) {
        total_weight += weights[i];
        weight_idxs.emplace_back(make_pair(weights[i], i));
    }
    vector<string> ans;
    unordered_set<string> visited;

    sort(weight_idxs.begin(), weight_idxs.end(), [](const pair<int, int>& a, const pair<int, int>& b){
        return a.first > b.first;
    });
    int pre_weight = 0;
    for (int i = 0; i < weight_idxs.size(); i++) {
        int idx = weight_idxs[i].second;

        int cur_weight = weights[idx];
        total_weight -= pre_weight;
        final_size -= ans.size();
        // 向上取整 宁可取多 不取少 防止后面不够了 FIXME: 这里万一后面队列压根没有qouta了怎么办?
        int cur_size = (final_size * cur_weight + total_weight - 1) / total_weight;
        int j = 0;
        int count = 0;
        while (j < queues[idx].size() && count < cur_size) {
            if (visited.find(queues[idx][j]) == visited.end()) {
                ans.emplace_back(queues[idx][j]);
                visited.emplace(queues[idx][j]);
                count += 1;
            }
            j += 1;
        }

        pre_weight = cur_weight;
    }

    return ans;
}


int main(int argc, char const *argv[])
{
    vector<vector<string> > queues = {
        {"1", "2", "3"},
        {"4", "5", "3", "2", "1", "10", "7"}, 
        {"11", "3", "6", "8"}, 
    };
    vector<int> weights{3, 5, 4};
    int size = 10;
    vector<string> ans = merge_recall_queues(queues, weights, size);
    for (auto& tmp: ans) {
        cout << tmp << "\n";
    }
    cout << endl;
    return 0;
}
