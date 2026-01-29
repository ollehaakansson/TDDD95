#include <algorithm>
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// Delar upp en sträng i tokens baserat på mellanslag
vector<string> split(const string &s) {
    vector<string> tokens;
    stringstream ss(s);
    string item;
    while (ss >> item) {
        tokens.push_back(item);
    }
    return tokens;
}

// Kollar om en sträng är en platshållare
bool is_placeholder(const string& s) {
    return s.length() >= 2 && s.front() == '<' && s.back() == '>';
}

// Disjoint Set Union 
struct DSU {
    vector<int> parent;
    vector<string> assigned_val; // Sparar ordet som variabeln är bunden till

    DSU(int n) {
        parent.resize(n);
        assigned_val.resize(n, ""); // Tom sträng = inget ord bundet än
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }

    // Slår ihop två variabler. Returnerar false vid konflikt.
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        
        if (root_i != root_j) {
            string val_i = assigned_val[root_i];
            string val_j = assigned_val[root_j];

            // Konfliktcheck: Om båda har ord, och de är olika.
            if (!val_i.empty() && !val_j.empty() && val_i != val_j) {
                return false; 
            }

            // Slå ihop
            parent[root_i] = root_j;
            
            // Om i hade ett värde men inte j, flytta det till j (som är ny root)
            if (val_j.empty() && !val_i.empty()) {
                assigned_val[root_j] = val_i;
            }
        }
        return true;
    }

    // Binder en variabel till ett specifikt ord. Returnerar false vid konflikt.
    bool assign(int i, const string& word) {
        int root = find(i);
        if (!assigned_val[root].empty()) {
            // Om den redan har ett ord, måste det vara samma
            return assigned_val[root] == word;
        }
        assigned_val[root] = word;
        return true;
    }

    string get_val(int i) {
        return assigned_val[find(i)];
    }
};

void solve() {
    string line1, line2;
    if (!getline(cin, line1)) return;
    getline(cin, line2);

    vector<string> p1 = split(line1);
    vector<string> p2 = split(line2);

    // Längdkontroll
    if (p1.size() != p2.size()) {
        cout << "-" << endl;
        return;
    }

    // Mappa variabler till unika ID:n
    map<string, int> var_to_id;
    int id_counter = 0;
    
    // hämta ID för en variabel, skapa nytt om den inte finns
    auto get_id = [&](string s, int pattern_idx) {
        string key = to_string(pattern_idx) + ":" + s; 
        if (var_to_id.find(key) == var_to_id.end()) {
            var_to_id[key] = id_counter++;
        }
        return var_to_id[key];
    };

    // Registrera alla variabler först för att veta hur stor DSU vi behöver
    for (const auto& s : p1) if (is_placeholder(s)) get_id(s, 1);
    for (const auto& s : p2) if (is_placeholder(s)) get_id(s, 2);

    DSU dsu(id_counter);

    // Unifiering (Gå igenom token för token)
    for (size_t i = 0; i < p1.size(); ++i) {
        string u = p1[i];
        string v = p2[i];
        bool u_is_var = is_placeholder(u);
        bool v_is_var = is_placeholder(v);

        if (!u_is_var && !v_is_var) {
            // Båda är ord -> Måste vara identiska
            if (u != v) {
                cout << "-" << endl; 
                return;
            }
        } else if (u_is_var && !v_is_var) {
            // Var mot Ord -> Bind variabeln
            if (!dsu.assign(get_id(u, 1), v)) {
                cout << "-" << endl; return;
            }
        } else if (!u_is_var && v_is_var) {
            // Ord mot Var -> Bind variabeln
            if (!dsu.assign(get_id(v, 2), u)) {
                cout << "-" << endl; return;
            }
        } else {
            // Var mot Var -> Slå ihop mängderna
            if (!dsu.unite(get_id(u, 1), get_id(v, 2))) {
                cout << "-" << endl; return;
            }
        }
    }

    // Skriv ut resultatet
    for (size_t i = 0; i < p1.size(); ++i) {
        if (i > 0) cout << " ";
        
        string token = p1[i];
        if (!is_placeholder(token)) {
            cout << token;
        } else {
            // Det är en variabel, hämta dess bundna ord
            int id = get_id(token, 1);
            string val = dsu.get_val(id);
            if (val.empty()) {
                // Variabeln blev aldrig bunden till ett ord (t.ex <x> matchade <y>).
                // Vi väljer "a".
                cout << "a";
            } else {
                cout << val;
            }
        }
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    // Optimimerar I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        string dummy;
        getline(cin, dummy); // Konsumera newline efter siffran
        while (n--) {
            solve();
        }
    }
    return 0;
}