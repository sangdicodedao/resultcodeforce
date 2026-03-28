#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct Domino 
{
    int left, right;
};

int N;
vector<Domino> pieces;
vector<vector<pair<int, int>>> graph(7); 
vector<bool> used;
vector<pair<int, char>> result; 

bool dfs(int u, int count) {
    if (count == N) return true;

    for (auto& [v, idx] : graph[u]) {
        if (used[idx]) continue;
        used[idx] = true;

        if (pieces[idx].left == u && pieces[idx].right == v) {
            result.push_back({idx + 1, '+'});
            if (dfs(v, count + 1)) return true;
            result.pop_back();
        } else {
            result.push_back({idx + 1, '-'});
            if (dfs(pieces[idx].left, count + 1)) return true;
            result.pop_back();
        }

        used[idx] = false;
    }
    return false;
}

bool isConnected() {
    vector<bool> visited(7, false);
    int start = -1;
    for (int i = 0; i < 7; ++i) {
        if (!graph[i].empty()) {
            start = i;
            break;
        }
    }
    if (start == -1) return true;

    vector<int> stack = {start};
    visited[start] = true;
    while (!stack.empty()) {
        int u = stack.back(); stack.pop_back();
        for (auto& [v, _] : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                stack.push_back(v);
            }
        }
    }

    for (int i = 0; i < 7; ++i) {
        if (!graph[i].empty() && !visited[i]) return false;
    }
    return true;
}

int main() {
    cin >> N;
    pieces.resize(N);
    used.resize(N, false);

    vector<int> degree(7, 0);
    for (int i = 0; i < N; ++i) {
        int a, b;
        cin >> a >> b;
        pieces[i] = {a, b};
        graph[a].emplace_back(b, i);
        graph[b].emplace_back(a, i);
        degree[a]++;
        degree[b]++;
    }

    int odd = 0;
    int start = -1;
    for (int i = 0; i < 7; ++i) {
        if (degree[i] % 2 == 1) {
            odd++;
            start = i;
        }
    }

    if (odd != 0 && odd != 2) {
        cout << "No solution\n";
        return 0;
    }

    if (!isConnected()) {
        cout << "No solution\n";
        return 0;
    }

    if (start == -1) {
        for (int i = 0; i < 7; ++i) {
            if (!graph[i].empty()) {
                start = i;
                break;
            }
        }
    }

    if (dfs(start, 0)) {
        for (auto& [idx, dir] : result) {
            cout << idx << " " << dir << "\n";
        }
    } else {
        cout << "No solution\n";
    }

    return 0;
}