/**
 * Author: Olle Håkansson
 *
 * Problem:
 *   Longest Increasing Subsequence (strictly increasing).
 *   Given a sequence of n integers, output the length of a LIS and
 *   the indices (0-based) of one such LIS in increasing order.
 *
 * Algorithm (O(n log n)):
 *   Maintain:
 *     tailVal[len] = minimum possible tail value of an increasing subsequence of length len+1
 *     tailIdx[len] = the index in the original array where that tail value occurs
 *     parent[i]    = previous index in the LIS ending at i (for reconstruction)
 *
 *   For each element a[i]:
 *     pos = lower_bound(tailVal, a[i])  // first >= a[i] => strict LIS
 *     update tailVal[pos] = a[i], tailIdx[pos] = i
 *     set parent[i] = tailIdx[pos-1] if pos > 0
 *
 *   Reconstruct by starting from tailIdx[L-1] and following parent[] backwards.
 *
 * Complexity:
 *   Time:  O(n log n)
 *   Space: O(n)
 * 
 * Usage:
 *   Compile: g++ -O2 -Wall -Wextra -pedantic -std=gnu++17 longest_inc.cpp -o main
 *   Run:     ./main < input.txt
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

static vector<int> lis_indices(const vector<long long>& a) {
    int n = (int)a.size();
    vector<int> parent(n, -1);

    vector<long long> tailVal; // values for binary search
    vector<int> tailIdx;       // indices corresponding to tailVal
    tailVal.reserve(n);
    tailIdx.reserve(n);

    for (int i = 0; i < n; i++) {
        // Strictly increasing => use lower_bound (first >= a[i]).
        int pos = (int)(lower_bound(tailVal.begin(), tailVal.end(), a[i]) - tailVal.begin());

        if (pos == (int)tailVal.size()) {
            tailVal.push_back(a[i]);
            tailIdx.push_back(i);
        } else {
            tailVal[pos] = a[i];
            tailIdx[pos] = i;
        }

        if (pos > 0) parent[i] = tailIdx[pos - 1];
    }

    // Reconstruct LIS
    vector<int> seq;
    int cur = tailIdx.back();
    while (cur != -1) {
        seq.push_back(cur);
        cur = parent[cur];
    }
    reverse(seq.begin(), seq.end());
    return seq;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        vector<int> ans = lis_indices(a);

        cout << ans.size() << "\n";
        for (int i = 0; i < (int)ans.size(); i++) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << "\n";
    }

    return 0;
}
