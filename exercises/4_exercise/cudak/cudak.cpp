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

/* 
Compile with:
g++ -O2 -Wall file_name.cpp -o main

Run with:
./main < input.txt
*/
using namespace std;
typedef vector<int> vi;

static string LOWS, HIGHS;
static int L, TARGET_SUM;

// dp[pos][sum][tightLow][tightHigh] = count, -1 means "not computed"
static long long dp[16][136][2][2];

long long solve_dp(int pos, int sum, int tightLow, int tightHigh) {
    if (sum < 0) return 0;
    if (pos == L) return (sum == 0) ? 1LL : 0LL;

    long long &memo = dp[pos][sum][tightLow][tightHigh];
    if (memo != -1) return memo;

    int lo = tightLow ? (LOWS[pos] - '0') : 0;
    int hi = tightHigh ? (HIGHS[pos] - '0') : 9;

    long long res = 0;
    for (int d = lo; d <= hi; d++) {
        int ntl = (tightLow && d == lo);
        int nth = (tightHigh && d == hi);
        res += solve_dp(pos + 1, sum - d, ntl, nth);
    }

    memo = res;
    return memo;
}

int main(int argc, char* argv[])
{
    // Optimimerar I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long A, B;
    int S;
    if (!(cin >> A >> B >> S)) return 0;

    TARGET_SUM = S;

    string a = to_string(A);
    string b = to_string(B);

    // A <= B => len(A) <= len(B)
    L = (int)b.size();

    // Pad with leading zeros to length L
    LOWS = string(L - (int)a.size(), '0') + a;
    HIGHS = b;

    // init dp with -1
    memset(dp, -1, sizeof(dp));

    long long count = solve_dp(0, TARGET_SUM, 1, 1);
    cout << count << "\n";

    // Reconstruct smallest number in [A,B] with digit sum S
    string best;
    best.reserve(L);

    int pos = 0, sum = TARGET_SUM;
    int tightLow = 1, tightHigh = 1;

    while (pos < L) {
        int lo = tightLow ? (LOWS[pos] - '0') : 0;
        int hi = tightHigh ? (HIGHS[pos] - '0') : 9;

        for (int d = lo; d <= hi; d++) {
            int ntl = (tightLow && d == lo);
            int nth = (tightHigh && d == hi);

            if (sum - d < 0) continue;
            if (solve_dp(pos + 1, sum - d, ntl, nth) > 0) {
                best.push_back(char('0' + d));
                sum -= d;
                tightLow = ntl;
                tightHigh = nth;
                break;
            }
        }
        pos++;
    }

    // Strip leading zeros for printing (but keep one digit if all zeros)
    int first_nonzero = 0;
    while (first_nonzero < (int)best.size() && best[first_nonzero] == '0') first_nonzero++;
    if (first_nonzero == (int)best.size()) {
        cout << "0\n";
    } else {
        cout << best.substr(first_nonzero) << "\n";
    }

    return 0;
}
