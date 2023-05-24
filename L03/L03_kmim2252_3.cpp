//Kosa Matyas, kmim2252, 512

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <fstream>

using namespace std;


ifstream f("3.in");
ofstream o("3.out");

void dfs(int csucs, vector<vector<int>>& graf, vector<int>& indexek, vector<int>& foksz, vector<bool>& stackbe_van, stack<int>& s, int& id, vector<vector<int>>& eredm) {
    indexek[csucs] = foksz[csucs] = id++;
    stackbe_van[csucs] = true;
    s.push(csucs);

    for (int szomsz : graf[csucs]) {
        if (indexek[szomsz] == -1) {
            dfs(szomsz, graf, indexek, foksz, stackbe_van, s, id, eredm);
            foksz[csucs] = min(foksz[csucs], foksz[szomsz]);
        } else if (stackbe_van[szomsz]) {
            foksz[csucs] = min(foksz[csucs], indexek[szomsz]);
        }
    }

    if (indexek[csucs] == foksz[csucs]) {
        vector<int> komp;
        int v;
        do {
            v = s.top();
            s.pop();
            stackbe_van[v] = false;
            komp.push_back(v);
        } while (v != csucs);
        eredm.push_back(komp);
    }
}

vector<vector<int>> tarjan(vector<vector<int>>& graf) {
    int n = graf.size();
    vector<int> indexek(n, -1), foksz(n);
    vector<bool> stackbe_van(n, false);
    stack<int> s;
    vector<vector<int>> eredm;
    int id = 0;

    for (int i = 0; i < n; i++) {
        if (indexek[i] == -1) {
            dfs(i, graf, indexek, foksz, stackbe_van, s, id, eredm);
        }
    }

    return eredm;
}

int main() {
    int n, m;
    f >> n >> m;

    vector<vector<int>> graf(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        f >> a >> b;
        graf[a].push_back(b);
    }

    vector<vector<int>> eredm = tarjan(graf);

    for (auto& komp : eredm) {
        for (int csucs : komp) {
            o << csucs << " ";
        }
        o << endl;
    }

    return 0;
}