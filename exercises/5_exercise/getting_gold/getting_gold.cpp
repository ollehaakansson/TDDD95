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

/* Compile with:
g++ -O2 -Wall getting_gold.cpp -o main

Run with:
./main < input.txt
*/
using namespace std;
typedef vector <int> vi;

int main(int argc, char* argv[])
{
    // Optimerar I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int W, H;
    if (!(cin >> W >> H)) return 0;

    vector<string> grid(H);
    int start_r = -1, start_c = -1;

    // read the grid and locate the starting position
    for (int i = 0; i < H; ++i) {
        cin >> grid[i];
        for (int j = 0; j < W; ++j) {
            if (grid[i][j] == 'P') {
                start_r = i;
                start_c = j;
            }
        }
    }

    if (start_r == -1) {
        cout << 0 << "\n";
        return 0;
    }

    vector<vector<bool>> visited(H, vector<bool>(W, false));
    queue<pair<int, int>> q;

    q.push({start_r, start_c});
    visited[start_r][start_c] = true;

    int gold_collected = 0;
    
    // Directions for up, down, left, right
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        if (grid[r][c] == 'G') {
            gold_collected++;
        }

        // Check if there is a trap nearby (draft)
        bool draft = false;
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < H && nc >= 0 && nc < W) {
                if (grid[nr][nc] == 'T') {
                    draft = true;
                    break;
                }
            }
        }

        // If there is no draft, we can safely explore adjacent cells
        if (!draft) {
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                if (nr >= 0 && nr < H && nc >= 0 && nc < W) {
                    if (!visited[nr][nc] && grid[nr][nc] != '#') {
                        visited[nr][nc] = true;
                        q.push({nr, nc});
                    }
                }
            }
        }
    }

    cout << gold_collected << "\n";

    return 0;
}