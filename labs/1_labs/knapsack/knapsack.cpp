/**
 * Author: Olle Håkansson
 *
 * Problem:
 *   0/1 Knapsack. Given capacity C and n items (value, weight), choose a subset
 *   with maximum total value such that total weight <= C. Output the number of
 *   chosen items and their indices (any order).
 *
 * Algorithm (DP, O(n*C)):
 *   dp[w] = best value achievable with capacity exactly w using items processed so far.
 *   Process items i=0..n-1, update dp in descending w to avoid reusing an item.
 *   Store decisions in take[i][w] = 1 if item i is taken in the optimal solution
 *   for capacity w after processing item i.
 *   Reconstruct by walking i backwards from n-1..0 starting at w=C:
 *     if take[i][w], choose i and set w -= weight[i].
 *
 * Complexity:
 *   Time:  O(n*C)
 *   Space: O(n*C) for take-table + O(C) for dp
 * 
 * Usage:
 *   Compile: g++ -O2 -Wall -Wextra -pedantic -std=gnu++17 knapsack.cpp -o main
 *   Run:     ./main < input.txt
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Item {
    int value;
    int weight;
};

static vector<int> knapsack(int C, const vector<Item>& items) {
    int n = (int)items.size();

    vector<int> dp(C + 1, 0);

    // take[i][w] == 1 means: after processing item i, the optimal for capacity w takes item i.
    vector<vector<unsigned char>> take(n, vector<unsigned char>(C + 1, 0));

    for (int i = 0; i < n; i++) {
        int v = items[i].value;
        int wgt = items[i].weight;

        // Descend to ensure each item used at most once.
        for (int w = C; w >= wgt; w--) {
            int cand = dp[w - wgt] + v;
            if (cand > dp[w]) {
                dp[w] = cand;
                take[i][w] = 1;
            }
        }
    }

    // Reconstruct chosen items from take-table.
    vector<int> chosen;
    int w = C;
    for (int i = n - 1; i >= 0; i--) {
        if (w >= 0 && take[i][w]) {
            chosen.push_back(i);
            w -= items[i].weight;
        }
    }

    return chosen; // any order accepted
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int C, n;
    while (cin >> C >> n) {
        vector<Item> items(n);
        for (int i = 0; i < n; i++) {
            cin >> items[i].value >> items[i].weight;
        }

        vector<int> ans = knapsack(C, items);

        cout << ans.size() << "\n";
        for (int i = 0; i < (int)ans.size(); i++) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << "\n";
    }

    return 0;
}
