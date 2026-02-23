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
g++ -O2 -Wall island_hopping.cpp -o main

Run with:
./main < input.txt
*/
using namespace std;
typedef vector <int> vi;

// Merging of components
struct DSU {
    vi parent;
    DSU(int n) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            return true;
        }
        return false;
    }
};

struct Point {
    double x, y;
};

struct Edge {
    int u, v;
    double weight;
    
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

void solve() {
    int m;
    cin >> m;

    vector<Point> islands(m);
    for (int i = 0; i < m; ++i) {
        cin >> islands[i].x >> islands[i].y;
    }

    // Since the graph is complete, we have m*(m-1)/2 edges.
    vector<Edge> edges;
    edges.reserve((m * (m - 1)) / 2);
    
    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            double dx = islands[i].x - islands[j].x;
            double dy = islands[i].y - islands[j].y;
            double dist = sqrt(dx * dx + dy * dy);
            edges.push_back({i, j, dist});
        }
    }

    // Sort all edges based on their weight
    sort(edges.begin(), edges.end());

    DSU dsu(m);
    double total_cost = 0.0;
    int edges_used = 0;

    // Kruskals algoritm to find the MST
    for (const auto& edge : edges) {
        if (dsu.unite(edge.u, edge.v)) {
            total_cost += edge.weight;
            edges_used++;
            // Abort early if we have connected all nodes (m-1 edges needed)
            if (edges_used == m - 1) break;
        }
    }

    // Making sure to output with high precision to meet the error margin requirement
    cout << fixed << setprecision(8) << total_cost << "\n";
}

int main(int argc, char* argv[])
{
    // Optimerar I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        while (n--) {
            solve();
        }
    }

    return 0;
}