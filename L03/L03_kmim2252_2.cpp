//Kosa Matyas, kmim2252, 512
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

ifstream f("2.in");
ofstream o("2.out");

class El {
public:
    int kezdo, veg, suly;
};

class Graf {
public:
    int n, m;
    vector<El> elek;
};

int find(int szulo[], int i) { // gyökér keresése
    if (szulo[i] == i) {
        return i;
    }
    return find(szulo, szulo[i]);
}


void egyesites(int szulo[], int melyseg[], int x, int y) {
    int x_gyoker = find(szulo, x);
    int y_gyoker = find(szulo, y);
    if (melyseg[x_gyoker] < melyseg[y_gyoker]) {
        szulo[x_gyoker] = y_gyoker;
    }
    else if (melyseg[x_gyoker] > melyseg[y_gyoker]) {
        szulo[y_gyoker] = x_gyoker;
    }
    else {
        szulo[y_gyoker] = x_gyoker;
        melyseg[x_gyoker]++;
    }
}

void countingSort(vector<El>& elek) {
    int maxi = 100;
    vector<int> nr(maxi+1, 0); 
    int size = elek.size();
    vector<El> temp(size);


    for (int i = 0; i < size; ++i) {
        ++nr[elek[i].suly];
    }
    for (int i = 1; i <= maxi; ++i) {
        nr[i] += nr[i - 1];
    }
    for (int i = size - 1; i >= 0; --i) {
        temp[--nr[elek[i].suly]] = elek[i];
    }
    elek.swap(temp);
}

void KruskalMST(Graf graf) {
    int n = graf.n;
    vector<El> eredmeny(n-1);
    int e = 0;
    int i = 0;
    countingSort(graf.elek);
    int szulo[n];
    int melyseg[n] = { 0 };
    for (int v = 0; v < n; ++v) {
        szulo[v] = v;
    }
    while (e < n - 1 && i < graf.m) {
        El kovetkezo_el = graf.elek[i++];
        int x = find(szulo, kovetkezo_el.kezdo);
        int y = find(szulo, kovetkezo_el.veg);
        if (x != y) {
            eredmeny[e++] = kovetkezo_el;
            egyesites(szulo, melyseg, x, y);
        }
    }
    int  osszeg=0;
    for (i = 0; i < e; ++i) {
        osszeg+=eredmeny[i].suly;
    }

    o<<"Minimalis Feszitofa Koltsege: "<<osszeg<<"\n";
    o<<"\n El       Suly"<<"\n\n";
    for (i = 0; i < e; ++i) {
        o << eredmeny[i].kezdo << "  " << eredmeny[i].veg << "        " << eredmeny[i].suly << endl;
    }
}

int main() {
    int n, m;
    f>>n>>m;
    Graf graf;
    graf.n = n;
    graf.m = m;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        f >> u >> v >> w;
        graf.elek.push_back({u, v, w});
    }
    
    KruskalMST(graf);
    return 0;
}