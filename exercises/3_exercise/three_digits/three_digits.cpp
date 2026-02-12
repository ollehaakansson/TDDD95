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
./file_name < input.txt
*/

using namespace std;
typedef vector <int> vi;

// precomputes product number 1..125 excluding multiples of 5 (mod 125)
long long get_block_product() {
    long long prod = 1;
    for (int i = 1; i <= 125; i++) {
        if ( i % 5 != 0) {
            prod = (prod * i) % 125;
        }
    }
    return prod;
}

// Function to calculate n! % 125 (excluding all factors of 5)
// Basically computes (n! / 5^k) % 125 where k is the count if factors of 5
long long fact_no_five(long long n, long long block_prod) {
    if (n == 0) return 1;

    long long num_blocks = n / 125;
    long long result = 1;

    for(int i = 0; i < num_blocks; i++){
        result = (result * block_prod) % 125;
    }

    int remainder = n % 125;
    for (int i = 1; i <= remainder; i++) {
        if (i % 5 != 0) {
            result = (result *i) % 125;
        }
    }

    return (result * fact_no_five(n/5, block_prod) % 125);
}

// power function for modular exponentiation
long long power(long long base, long long exp, int mod) {
    long long result = 1;
    base %= mod;

    while (exp > 0) {
        if ((exp % 2) == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main(int argc, char* argv[])
{
    // Optimimerar I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    if (cin >> n) {
        /* We want to handle 2 cases
        1. Small n (we calculate factorials direclty)
        2. Large n (we use the hinese remainder theorem)
        
        We don't care about the trailing zero's. 
        A trailing zero occurs when we multiply a factor of 2 and a 
        factor of 5. So we basically want to calculate n!/(10^k) 
        (where k is the number of pairs of (2, 5) in the prime 
        factorization of n!)
        */

        // Case 1
        if (n < 10) {
            long long fact = 1;
            for (int i = 1; i <= n; i++) {
                fact *= i;
            }
            while (fact % 10 == 0){
                fact /= 10;
            }
            cout << fact % 1000 << endl;
        }
        // Case 2
        else {
            long long block_prod = get_block_product();

            // Step A: Calculate part modulo 125
            long long val_mod_125 = fact_no_five(n, block_prod);

            // Count how many factors of 5 (and thus 2) where removed
            long long count5 = 0;
            long long temp = n;
            while (temp >= 5) {
                count5 += temp/5;
                temp /=5;
            }

            // For every factor of 5 removed, we also removed a factor of 2.
            // To fix a modulo 125 result, we multiply by mod inverse of 2.
            // 2^-1 mod 125 = 63
            // So we need to multiply by 63^count5

            long long inv2_pow = power(63, count5, 125);
            long long rem125 = (val_mod_125 * inv2_pow) % 125;

            // Step B: Calculate part modulo 8
            // for N >= 10, the non zero part of factorial is always a multiple of 8

            long long rem8 = 0;

            // Step C: CRT Combinatino

            long long k = ((-rem125 * 5) % 8 + 8) % 8;
            long long ans = k * 125 + rem125;

            cout << setfill('0') << setw(3) << ans << endl;


        }

    }

    return 0;
}