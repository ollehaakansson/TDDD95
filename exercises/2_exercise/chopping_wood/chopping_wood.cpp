#include <algorithm>
#include <cassert>
#include <cmath>
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

using namespace std;
typedef vector <int> vi;

int main(int argc, char* argv[])
{
    // Optimimerar I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // node är numrerade 1..n+1
    vi node(n);
    // om degree[i] == 0 så är nod ett löv
    vi degree(n+2, 0);

    for (int i = 0; i < n; i++) {
        cin >> node[i];

        if (node[i] >= 1 && node[i] <= n+1){
            degree[node[i]]++;
        } else {
            // ogiltig nod
            cout << "Ogiltig nod: " << node[i] << "\n";
            return 0;
        }
    }

    int ptr = 1; // pekare till nästa löv
    while (ptr <= n + 1 && degree[ptr] != 0) {
        ptr++;
    }

    vi result;
    result.reserve(n);
    int leaf = ptr;

    for (int i = 0; i < n; i++) {
        if (leaf > n + 1) {
            cout << "Felaktig indata\n";
            return 0;
        }

        result.push_back(leaf);
        degree[leaf] = -1; // markera som borttagen

        int neighbor = node[i];
        degree[neighbor]--;

        // om grannen blir ett löv och är mindre än ptr
        // så måste den vara minsta nästa löv
        if (degree[neighbor] == 0 && neighbor < ptr) {
            leaf = neighbor;
        } else {
            // hitta nästa löv
            ptr++;
            while (ptr <= n + 1 && degree[ptr] != 0) {
                ptr++;
            }
            leaf = ptr;
        }
    }

    // Kontrollera att det träd vi byggt genererar exakt samma
    // sekvens om man alltid tar bort minsta lövet.

    vector<vector<int>> adj(n + 2);
    vector<int> verify_degree(n + 2, 0);

    for (int i = 0; i < n; ++i) {
        int u = result[i];   // Lövet vi gissade på
        int w = node[i];        // Grannen från indatan
        adj[u].push_back(w);
        adj[w].push_back(u);
        verify_degree[u]++;
        verify_degree[w]++;
    }

    // Simulera processen med det byggda trädet
    ptr = 1;
    while (ptr <= n + 1 && verify_degree[ptr] != 1) {
        ptr++;
    }
    
    int check_leaf = ptr;
    vector<bool> removed_nodes(n + 2, false); // Håll koll på borttagna noder

    for (int i = 0; i < n; ++i) {
        // Hitta vem nuvarande löv är kopplat till (som inte är borttagen)
        int neighbor = -1;
        for (int candidate : adj[check_leaf]) {
            if (!removed_nodes[candidate]) {
                neighbor = candidate;
                break;
            }
        }

        // Stämmer grannen i vårt träd med grannen i indatan?
        // Om nej: Då var trädstrukturen omöjlig för den givna ordningen.
        if (neighbor != node[i]) {
            cout << "Error" << "\n";
            return 0;
        }

        // Ta bort lövet
        removed_nodes[check_leaf] = true;
        verify_degree[neighbor]--;

        // Hitta nästa löv
        if (verify_degree[neighbor] == 1 && neighbor < ptr) {
            check_leaf = neighbor;
        } else {
            while (ptr <= n + 1 && (verify_degree[ptr] != 1 || removed_nodes[ptr])) {
                ptr++;
            }
            check_leaf = ptr;
        }
    }

    //resultat
    for (int i = 0; i < n; i++) {
        cout << result[i] << "\n";
    }

    return 0;
}