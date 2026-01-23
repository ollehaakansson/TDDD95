#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
const int INF = 1e9; 

void solve() {
    int M;
    cin >> M; // Antal distanser

    // Läs in distanserna
    vector<int> d(M);
    int sum_dist = 0;
    for (int i = 0; i < M; ++i) {
        cin >> d[i];
        sum_dist += d[i];
    }

    // dp[i][h] lagrar den minsta max-höjden för att nå höjd h vid steg i
    // Fyller alla tomma rutor med INF
    vector<vector<int>> dp(M + 1, vector<int>(1001, INF));

    // Startvärde: Vid steg 0 är vi på höjd 0. 
    // Maxhöjden vi varit på hittills är också 0.
    dp[0][0] = 0;

    // Loopa genom varje steg 
    for (int i = 0; i < M; ++i) {
        int dist = d[i];

        // Loopa genom alla möjliga höjder vi kan befinna oss på just nu
        for (int height = 0; height <= 1000; ++height) {
            
            // Hoppa över.
            if (dp[i][height] == INF) continue;

            // Alternativ UP:
            // Ny höjd blir height + dist.
            if (height + dist <= 1000) {
                // Undersöker om vår nya höjd är högre än vår tidigare peak.
                int potential_peak = max(dp[i][height], height + dist);
                
                // Vi vill spara det minsta möjliga peak-värdet i nästa ruta.
                dp[i+1][height+dist] = min(dp[i+1][height+dist], potential_peak);
            }

            // Alternativ Down:
            if (height - dist >= 0) {
                // När vi klättrar ner ökar inte max-höjden.
                int potential_peak = dp[i][height];
                
                dp[i+1][height-dist] = min(dp[i+1][height-dist], potential_peak);
            }
        }
    }

    // Efter M steg måste vi vara på höjd 0.
    // Om dp[M][0] fortfarande är INF, finns ingen lösning.
    if (dp[M][0] == INF) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }

    //BACKTRACKING
    string path = "";
    int current_height = 0; 

    for (int i = M - 1; i >= 0; --i) {
        int dist = d[i];
        
        // Testa: Kom vi från en up
        int prev_height_from_up = current_height - dist;
        
        // Testa: Kom vi från en down
        int prev_height_from_down = current_height + dist;
        
        bool did_we_go_down = false;
        
        // Kollar om vi kom från en down
        if (prev_height_from_down <= 1000 && dp[i][prev_height_from_down] != INF) {
             // Om vi gick ner, så var peaken densamma.
             if (dp[i+1][current_height] == dp[i][prev_height_from_down]) {
                 path += 'D';
                 current_height = prev_height_from_down;
                 did_we_go_down = true;
             }
        }

        if (!did_we_go_down) {
            // Om vi inte gick ner, måste vi ha gått upp.
            if (prev_height_from_up >= 0 && dp[i][prev_height_from_up] != INF) {
                 // Om vi gick upp, så blev peaken max(prev_peak, ny_höjd).
                 if (dp[i+1][current_height] == max(dp[i][prev_height_from_up], current_height)) {
                     path += 'U';
                     current_height = prev_height_from_up;
                 }
            }
        }
    }

    // Vänder på den byggda vägen eftersom vi backtrackade
    reverse(path.begin(), path.end());
    cout << path << endl;
}

int main(int argc, char* argv[]) {
    // Optimera I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N; // Antal scenarion
    if (cin >> N) {
        while(N--) {
            solve();
        }
    }
    return 0;
}