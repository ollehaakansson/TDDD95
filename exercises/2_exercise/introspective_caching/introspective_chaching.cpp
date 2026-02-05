#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int INF = 200000;

int main() {
    // Optimera I/O för snabbare exekvering
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int C, N, A;
    // Läs in Cache storlek C, Antal unika objekt N och Antal åtkomster A
    if (!(cin >> C >> N >> A)) return 0;

    vector<int> accesses(A);
    for (int i = 0; i < A; ++i) {
        cin >> accesses[i];
    }

    // Skapar next_use där next_use[i] pekar på indexet för nästa gång objektet vid accesses[i] används.
    vector<int> next_use(A);
    vector<int> last_seen_index(N, INF); // för att minnas var vi såg ett objekt sist 

    // Går baklänges genom listan för att fylla i framtidsdatan
    for (int i = A - 1; i >= 0; --i) {
        int obj = accesses[i];
        next_use[i] = last_seen_index[obj];
        last_seen_index[obj] = i;
    }

    // Cachen representeras av ett set med par {nästa_användnings_index, objekt_id}
    set<pair<int, int>> cache_contents;

    vector<bool> is_in_cache(N, false);
    
    int reads = 0;

    for (int i = 0; i < A; ++i) {
        int obj = accesses[i];
        int next_occurrence = next_use[i];

        if (is_in_cache[obj]) {
            // chache hit: Objektet finns redan.
            // uppdaterar dess nästa användning i cachen
            
            cache_contents.erase({i, obj});
            cache_contents.insert({next_occurrence, obj});
        } else {
            // chache miss: Objektet måste hämtas.
            reads++;

            // Om vi inte har någon plats kan vi inte lagra något.
            if (C > 0) {
                // Om cachen är full måste vi kasta ut någon
                if (cache_contents.size() == C) {
                    // Hämta det element som har störst 'next_use'
                    pair<int, int> to_evict = *cache_contents.rbegin();
                    
                    // Ta bort från cachen
                    cache_contents.erase(prev(cache_contents.end()));
                    is_in_cache[to_evict.second] = false;
                }

                // Lägg in det nya objektet
                is_in_cache[obj] = true;
                cache_contents.insert({next_occurrence, obj});
            }
        }
    }

    cout << reads << endl;

    return 0;
}