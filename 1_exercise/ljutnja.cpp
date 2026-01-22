#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
//typedef vector <int> vi;

int main(int argc, char* argv[])
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long M;
    int N;

    // läser in M och N
    if (!(cin >> M >> N)) return 0;

    vector<long long> wishes(N);
    long long total_wishes = 0;

    //Lägg in önskemålen
    for (int i = 0; i < N; i++) {
        cin >> wishes[i];
        total_wishes += wishes[i];
    }
    // Räkna totalt underskott 
    long long total_missing = total_wishes - M;
    //sort(wishes.begin(), wishes.end());

    long long anger = 0;
    for (int i = 0; i < N; i++) {
        long long remaining_children = N - i;
        long long fair_share_missing = total_missing / remaining_children;

        long long actual_missing;
        if (wishes[i] < fair_share_missing) {
            actual_missing = wishes[i];
        } else {
            actual_missing = fair_share_missing;
        }
        anger += actual_missing * actual_missing;
        total_missing -= actual_missing;
    }
    cout << anger << endl;
        
    return 0;
}