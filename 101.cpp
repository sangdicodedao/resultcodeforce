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
struct Edge 
{
    int to, idx;
    bool used;
    Edge(int t, int i) : to(t), idx(i), used(false) {}
};

int N;
vector<pair<int, int>> dominoes;
vector<Edge> graph[7];
vector<pair<int, char>> result;
map<int, pair<int, int>> edge_map;

void dfs(int u) 
{
    for (auto &e : graph[u]) 
    {
        if (!e.used) 
        {
            e.used = true;
            for (auto &rev : graph[e.to]) 
            {
                if (rev.to == u && rev.idx == e.idx && !rev.used) 
                {
                    rev.used = true;
                    break;
                }
            }
            dfs(e.to);
            int a = dominoes[e.idx].first;
            int b = dominoes[e.idx].second;
            char dir = (a == u) ? '+' : '-';
            result.push_back({e.idx + 1, dir});
        }
    }
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    dominoes.resize(N);
    vector<int> degree(7, 0);

    for (int i = 0; i < N; ++i) 
    {
        int a, b;
        cin >> a >> b;
        dominoes[i] = {a, b};
        graph[a].emplace_back(b, i);
        graph[b].emplace_back(a, i);
        degree[a]++;
        degree[b]++;
    }

    int odd = 0, start = -1;
    for (int i = 0; i < 7; ++i) 
    {
        if (degree[i] % 2 != 0) 
        {
            odd++;
            start = i;
        } 
        else if (degree[i] > 0 && start == -1) 
        {
            start = i;
        }
    }

    if (odd != 0 && odd != 2) 
    {
        cout << "No solution\n";
        return 0;
    }

    dfs(start);

    if (result.size() != N) 
    {
        cout << "No solution\n";
    } 
    else 
    {
        reverse(result.begin(), result.end());
        for (auto &[idx, dir] : result) 
        {
            cout << idx << " " << dir << "\n";
        }
    }

    return 0;
}
