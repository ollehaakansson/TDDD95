#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
//typedef vector <int> vi;

/* Vi vill minimera den totala summan av total_missing^2
Målet blir alltså att sprida ut "anger" så mycket som möjligt eftersom
det växer kvadratiskt. Vi tar en greedy approach
*/
int main(int argc, char* argv[])
{
    // Optimimerar I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    unsigned long long M; // Totalt antal godis
    int N; // Antal barn

    // läser in M och N
    if (!(cin >> M >> N)) return 0;

    // Använder vektor för att lagra önskemålen
    vector<unsigned long long> wishes(N);
    unsigned long long total_wishes = 0;

    //Läs in önskemålen
    for (int i = 0; i < N; i++) {
        cin >> wishes[i];
        total_wishes += wishes[i];
    }
    // Räkna totalt underskott 
    unsigned long long total_missing = total_wishes - M;
    if(total_missing <= 0) total_missing = 0;

    // Sortera önskemålen i stigande ordning 
    sort(wishes.begin(), wishes.end());

    unsigned long long anger = 0;

    // Iterera genom barnen och bestäm hur mycket vi ska ta från varje
    for (int i = 0; i < N; i++) {
        unsigned long long remaining_children = N - i;
        unsigned long long fair_share_missing = total_missing / remaining_children;

        unsigned long long take_from_child;
        if (wishes[i] < fair_share_missing) { // Barnet önskar sig mindre än fair share
            take_from_child = wishes[i];
        } else { // Vi tar bara vår fair share från detta barn
            take_from_child = fair_share_missing;
        }
        anger += take_from_child * take_from_child;
        total_missing -= take_from_child;
    }
    cout << anger << endl;
        
    return 0;
}