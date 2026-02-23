#include <algorithm>
#include <cassert>
#include <cmath>
// #include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <string>
#include <utility>
#include <vector>

/* Compile with:
g++ -O2 -Wall get_shorty.cpp -o main

Run with:
./main < input.txt
*/
using namespace std;
typedef vector <int> vi;

void solve() {
    int n, m;
    
    // read n and m, break if n=0 and m=0
    while (cin >> n >> m && (n != 0 || m != 0)) {
        // adj[u] contains pairs of (neighbor node, factor)
        vector<vector<pair<int, double>>> adj(n);
        
        for (int i = 0; i < m; ++i) {
            int u, v;
            double f;
            cin >> u >> v >> f;
            
            // corridors are bidirectional
            adj[u].push_back({v, f});
            adj[v].push_back({u, f});
        }

        // max_factor saves the largest product found so far to reach each node
        vector<double> max_factor(n, 0.0);
        
        // max-heap for Dijkstra's algorithm. Stores pairs of (current product, node)
        priority_queue<pair<double, int>> pq;

        // Start node is 0
        max_factor[0] = 1.0;
        pq.push({1.0, 0});

        while (!pq.empty()) {
            double current_f = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            // if we already found a better path to this node, skip
            if (current_f < max_factor[u]) continue;

            // abort early if we reach the target node, since the max-heap guarantees 
            // we reached it with the maximum possible product
            if (u == n - 1) break;

            // Explore all neighbors
            for (size_t i = 0; i < adj[u].size(); ++i) {
                int v = adj[u][i].first;
                double weight = adj[u][i].second;

                // If the product through node u to v is better than previously known
                if (current_f * weight > max_factor[v]) {
                    max_factor[v] = current_f * weight;
                    pq.push({max_factor[v], v});
                }
            }
        }

        // print the result for the current graph with exactly four decimal places
        cout << fixed << setprecision(4) << max_factor[n - 1] << "\n";
    }
}

int main(int argc, char* argv[])
{
    // Optimerar I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}