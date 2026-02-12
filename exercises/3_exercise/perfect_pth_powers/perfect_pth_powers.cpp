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
typedef vector <int> vi;

int main(int argc, char* argv[])
{
    // Optimimerar I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long x;
    while (cin >> x && x != 0) {
        long long val = (x < 0) ? -x : x;
        int best_p = 1;

        // The max possible power for a 32-bit int is 31
        // Iterate downwards to find the largest p first
        for (int p = 31; p >= 1; --p) {

            //if x is negative it cannot be a perfect square
            if (x < 0 && p % 2 == 0) continue;

            // fin the p-th root of val
            double root = pow((double)val, 1.0 / p);
            long long b = (long long)(root + 0.5);

            // Since |x| >= 2, the base b must be at least 2 for any p > 1.
            if (b < 2 && p > 1) continue;

            // verify
            long long check = 1;
            for (int k = 0; k < p; ++k){
                check *= b;
            }

            if (check == val){
                best_p = p;
                break;
            }
        }
        cout << best_p << endl;
    }

    return 0;
}