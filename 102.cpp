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
int main() 
{
	ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;

    int count = 0;
    for (int i = 1; i <= n; ++i) 
    {
        if (__gcd(n, i) == 1) 
        {
            count++;
        }
    }

    cout << count << endl;
    return 0;
}
