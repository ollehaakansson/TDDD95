/**
 * Author: Olle Håkansson
 *
 * Problem:
 *   Minimum interval cover. Given target [A,B] and n intervals [ai,bi],
 *   output the minimum number of intervals needed to cover [A,B] and
 *   the indices of one optimal choice, or "impossible" if no cover exists.
 *
 * Algorithm (Greedy, O(n log n)):
 *   Sort intervals by start ascending, and end descending on ties.
 *   Let cur = A. Repeatedly choose among intervals with start <= cur the one
 *   with the largest end; advance cur to that end. If no interval can extend
 *   beyond cur, covering is impossible.
 *   Special case: if A == B (point interval), pick any interval containing A.
 *
 * Complexity:
 *   Time:  O(n log n) per test case (sorting) + O(n) scan
 *   Space: O(n)
 * 
 * Usage:
 *   Compile: g++ -O2 -Wall -Wextra -pedantic -std=gnu++17 interval_cover.cpp -o main
 *   Run:     ./main < input.txt
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

struct Interval {
    double l, r;
    int idx;
};

static vector<int> cover_min(double A, double B, vector<Interval>& segs) {

    // Special case: target is a point.
    if (A == B) {
        for (const auto& s : segs) {
                if (s.l <= A && A <= s.r) return {s.idx};
            }
        return {};
    }

    sort(segs.begin(), segs.end(), [](const Interval& a, const Interval& b) {
        if (a.l != b.l) return a.l < b.l;
        return a.r > b.r;
    });

    vector<int> chosen;
    double cur = A;
    int i = 0, n = (int)segs.size();

    while (cur < B) {
        double bestEnd = cur;
        int bestIdx = -1;

        while (i < n && segs[i].l <= cur) {
            if (segs[i].r > bestEnd) {
                bestEnd = segs[i].r;
                bestIdx = segs[i].idx;
            }
            i++;
        }

        // No interval can extend coverage -> impossible.
        if (bestIdx == -1 || bestEnd <= cur) return {};

        chosen.push_back(bestIdx);
        cur = bestEnd;
    }

    return chosen;
}

int main() {
    // Optimimerar I/O
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double A, B;
    while (cin >> A >> B) {
        int n;
        cin >> n;

        vector<Interval> segs;
        segs.reserve(n);

        for (int i = 0; i < n; i++) {
            double a, b;
            cin >> a >> b;
            segs.push_back({a, b, i});
        }

        vector<int> ans = cover_min(A, B, segs);

        if (ans.empty()) {
            cout << "impossible\n";
        } else {
            cout << ans.size() << "\n";
            for (int i = 0; i < (int)ans.size(); i++) {
                if (i) cout << ' ';
                cout << ans[i];
            }
            cout << "\n";
        }
    }
    return 0;
}
