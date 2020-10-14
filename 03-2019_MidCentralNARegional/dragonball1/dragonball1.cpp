#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>

#define endl '\n'
#define ll long long int

using namespace std;

struct edge {
    int to;
    ll cost;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    auto cmp = [](const edge& lhs, const edge& rhs) { return lhs.cost > rhs.cost; };

    string str;
    int n, m;
    getline(cin, str);
    stringstream(str) >> n >> m;

    vector<vector<edge>> adj(n);
    vector<int> key_cities {0}; // Need to start from first city
    map<int, vector<ll>> dists; // Key is start city, val is vec<> of best dists

    for (int i = 0; i < m; ++i) {
        int a, b, t;
        getline(cin, str);
        stringstream(str) >> a >> b >> t;
        adj[a - 1].push_back({b - 1, t});
        adj[b - 1].push_back({a - 1, t});
    }

    getline(cin, str);
    stringstream ss(str);
    for (int i = 0; i < 7; ++i) {
        int x;
        ss >> x;
        --x;
        bool seen = false;
        for (auto c : key_cities) if (x == c) seen = true;
        if (!seen) key_cities.push_back(x);
    }

    // Dijkstra, <= 7 times
    for (auto src : key_cities) {
        priority_queue<edge, vector<edge>, decltype(cmp)> pq(cmp);
        pq.push({src, 0});
        dists[src] = vector<ll>(n, -1);
        dists[src][src] = 0;

        while (!pq.empty()) {
            int u = pq.top().to;
            pq.pop();

            for (auto e : adj[u]) {
                int v = e.to;
                int cost = e.cost;

                if (dists[src][v] == -1 || dists[src][v] > dists[src][u] + cost) {
                    dists[src][v] = dists[src][u] + cost;
                    pq.push({v, dists[src][v]});
                }
            }
        }
    }

    sort(key_cities.begin(), key_cities.end()); // To get "first" permutation, and 0 first

    ll best = -1;
    auto start = key_cities.begin();
    ++start; // Skip permuting 0 on loop (we must start at 0)
    auto end = key_cities.end();
    do {
        ll tmp = 0;
        for (int i = 1; i < key_cities.size(); ++i) {
            int from = key_cities[i - 1];
            int to = key_cities[i];
            if (dists[from][to] == -1) { tmp = -1; break; } // if city unreachable, this path is impossible
            tmp += dists[from][to];
        }
        if (best == -1 || (tmp != -1 && tmp < best)) best = tmp;
    } while (next_permutation(start, end));

    if (best == -1) cout << -1 << endl;
    else cout << best << endl;

    return 0;
}
