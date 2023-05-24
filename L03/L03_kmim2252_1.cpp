//Kosa Matyas, kmim2252, 512

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <fstream>

using namespace std;

typedef pair<int, int> pii;

ifstream f("1.in");
ofstream o("1.out");

const int INF = 1e9;

void prim(vector<vector<pii>> szomsz, int source) {
    int n = szomsz.size(); // a gráf csúcsainak száma

    vector<bool> volt(n, false); // követi, hogy mely csúcsokat jártuk már be
    vector<int> parent(n, -1); // követi, hogy az adott csúcsot melyik szülő csúcs választotta ki
    vector<int> suly(n, INF); // követi az adott csúcstól mért minimális távolságokat

    priority_queue<pii, vector<pii>, greater<pii>> bin_kupac; // binaris kupac, amelyben az élek vannak tárolva
    bin_kupac.push(make_pair(0, source)); // az első él a forrásból indul, a távolsága nulla
    suly[source] = 0;

    // Az algoritmus addig megy, amíg a binaris kupac nem üres
    while (!bin_kupac.empty()) {
        int u = bin_kupac.top().second; // kiválasztjuk a legkisebb súlyú élt
        bin_kupac.pop();

        if (volt[u]) continue; // ha már jártunk ezen a csúcson, ugrunk a következőre
        volt[u] = true; // az adott csúcsot bejártuk

        // végigmegyünk az összes szomszédos csúcson
        for (int i = 0; i < szomsz[u].size(); i++) {
            int v = szomsz[u][i].first; // a szomszédos csúcs
            int w = szomsz[u][i].second; // az él súlya

            // ha még nem jártuk be a csúcsot, és az új él súlya kisebb, mint a korábbi távolság, 
            // akkor frissítjük a minimum távolságot és az élek közötti kapcsolatot
            if (!volt[v] && w < suly[v]) {
                suly[v] = w;
                parent[v] = u;
                bin_kupac.push(make_pair(suly[v], v));
            }
        }
    }
    int osszeg=0;
    for (int i = 1; i < n; i++) {
        if (parent[i] != -1) {
           osszeg+=suly[i];
        }
    }
    o<<"Minimalis Feszitofa Koltsege: "<<osszeg<<"\n";
    o<<"\n El       Suly"<<"\n\n";

    
    for (int i = 1; i < n; i++) {
        if (parent[i] != -1) {
            o << parent[i] << "  " << i << "       " << suly[i] << "\n";
        }
    }
}

int main() {
    int n, m;
    f >> n >> m;

    vector<vector<pii>> szomsz(n); 

    for (int i = 0; i < m; i++) {
        int u, v, w;
        f >> u >> v >> w;
        szomsz[u].push_back(make_pair(v, w));
        szomsz[v].push_back(make_pair(u, w));
    }

    prim(szomsz, 0);

    return 0;
}