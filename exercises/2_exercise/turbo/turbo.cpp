#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class FenwickTree {
private:
    int size;
    vector<int> tree;

public:
    FenwickTree(int n) : size(n), tree(n + 1, 0) {}

    void add(int i, int var) {
        while (i <= size) {
            tree[i] += var;
            i += i & (-i);
        }
    }

    // Returnerar summan av elementen från index 1-i.
    int query(int i) {
        int sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= i & (-i);
        }
        return sum;
    }
};

int main() {
    // Optimera I/O för prestanda
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // position[val] lagrar ursprungspositionen för talet 'val'.
    vector<int> position(n + 1);
    for (int i = 1; i <= n; ++i) {
        int val;
        cin >> val;
        position[val] = i;
    }

    FenwickTree bit(n);
    for (int i = 1; i <= n; ++i) {
        bit.add(i, 1);
    }

    int left = 1;      // Det minsta talet vi inte sorterat än
    int right = n;     // Det största talet vi inte sorterat än

    // Algon körs i N faser
    for (int phase = 1; phase <= n; ++phase) {
        if (phase % 2 != 0) {
            // Udda fas: Flytta det minsta talet 'left' till vänster.
            int current_pos_index = position[left];
            
            // Antal byten är antalet aktiva element till vänster om detta index.
            int swaps = bit.query(current_pos_index - 1);
            cout << swaps << "\n";

            // Markera detta index som tomt ta bort 1.
            bit.add(current_pos_index, -1);
            left++;
        } else {
            // Jämn fas: Flytta det största talet 'right' till höger.
            int current_pos_index = position[right];

            // Antal byten är antalet aktiva element till höger om detta index.
            int total_active = bit.query(n);
            int active_before_and_self = bit.query(current_pos_index);
            
            int swaps = total_active - active_before_and_self;
            cout << swaps << "\n";

            // Markera detta index som tomt.
            bit.add(current_pos_index, -1);
            right--;
        }
    }

    return 0;
}