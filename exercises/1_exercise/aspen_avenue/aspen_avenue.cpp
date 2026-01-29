#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

// Använd ett stort tal för oändlighet (måste vara större än alla möjliga avstånd)
const double INF = 1e18;

void solve() {
    int N;
    // Läs in N. Om det inte går, returnera.
    if (!(cin >> N)) return;

    double L, W;
    cin >> L >> W;

    vector<int> p(N);
    for (int i = 0; i < N; ++i) {
        cin >> p[i];
    }

    // Sortera träden
    sort(p.begin(), p.end());

    // Beräkna avståndet mellan varje 'slot'
    int k = N / 2;
    
    // Avstånd mellan trädplatserna på varje sida
    double dist_step = L / (k - 1);

    // dp[i][j] = minsta kostnad att placera 'i' träd totalt, varav 'j' på vänster sida.
    // i går från 0 till N.
    // j går från 0 till k (N/2).
    vector<vector<double>> dp(N + 1, vector<double>(k + 1, INF));

    // Basfall: 0 träd placerade kostar 0 meter.
    dp[0][0] = 0.0;

    // i är antalet träd vi har processat hittills
    for (int i = 0; i < N; ++i) {
        // j är antalet träd vi hittills lagt på vänster sida
        // j kan inte vara större än i, och inte större än k
        for (int j = 0; j <= k && j <= i; ++j) {
            
            // Om detta tillstånd är omöjligt att nå, skippa det
            if (dp[i][j] == INF) continue;

            // Räkna ut hur många vi lagt på höger sida hittills
            int right_count = i - j;

            // Alternativ 1: Lägg träd i på vänster sida
            // Vi kan bara göra detta om vänster sida inte är full 
            if (j < k) {
                // X-koordinat
                double target_x = j * dist_step;
                // Skillnad i x-led
                double cost = abs(p[i] - target_x);
                
                // Uppdatera nästa tillstånd (i+1 träd totalt, j+1 till vänster)
                dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j] + cost);
            }

            // Alternativ 2: Lägg träd i på höger sida
            // Vi kan bara göra detta om höger sida inte är full
            if (right_count < k) {
                // X-koordinat
                double target_x = right_count * dist_step;
                // Skillnad i x-led
                double dx = p[i] - target_x;
                // Avståndet är hypotenusan
                double cost = sqrt(dx*dx + W*W);

                // Uppdatera nästa tillstånd (i+1 träd totalt, j till vänster - oförändrat)
                dp[i+1][j] = min(dp[i+1][j], dp[i][j] + cost);
            }
        }
    }

    // Svaret ligger i dp[N][k] (Alla N träd placerade, exakt k till vänster)
    cout << fixed << setprecision(10) << dp[N][k] << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}