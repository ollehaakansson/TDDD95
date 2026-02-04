#include <algorithm>
#include <cassert>
#include <cmath>
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

using namespace std;
typedef vector <int> vi;

int main(int argc, char* argv[])
{
    // Optimimerar I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vi v(n);
    // Vertices are numbered 1 to n+1. We use size n+2 for 1-based indexing.
    // degree[i] stores the count of occurrences of vertex i in the input list.
    vi degree(n + 2, 0);

    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        if (v[i] >= 1 && v[i] <= n + 1) {
            degree[v[i]]++;
        } else {
            // Input constraint violation
            cout << "Error" << "\n";
            return 0;
        }
    }

    // ptr acts as a monotonic pointer to find the smallest leaf.
    int ptr = 1;
    while (ptr <= n + 1 && degree[ptr] != 0) {
        ptr++;
    }

    vi result;
    result.reserve(n);
    int leaf = ptr;

    // Process n edges
    for (int i = 0; i < n; ++i) {
        // Validation: If we ran out of valid leaves
        if (leaf > n + 1) {
            cout << "Error" << "\n";
            return 0;
        }

        result.push_back(leaf);
        
        // Mark the current leaf as removed (using -1 to distinguish from degree 0)
        degree[leaf] = -1;

        int neighbor = v[i];
        degree[neighbor]--;

        // Standard logic for O(N) Prüfer-like reconstruction:
        // If the neighbor becomes a leaf and is smaller than our current search pointer 'ptr',
        // it must be the immediate next smallest leaf.
        if (degree[neighbor] == 0 && neighbor < ptr) {
            leaf = neighbor;
        } else {
            // Otherwise, scan forward to find the next available leaf.
            // degree[ptr] == -1 indicates it was already processed.
            // degree[ptr] > 0 indicates it is not yet a leaf.
            // We look for degree[ptr] == 0.
            while (ptr <= n + 1 && degree[ptr] != 0) {
                ptr++;
            }
            leaf = ptr;
        }
    }

    // Output the reconstructed u column
    for (int i = 0; i < n; ++i) {
        cout << result[i] << "\n";
    }

    return 0;
}