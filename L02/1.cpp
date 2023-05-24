//Kosa Matyas, 512, kmim2552

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;


ifstream f("1.in");

void dfs(int csucs, vector<vector<int>>& szomsz, vector<bool>& volt) {
    volt[csucs] = true; 
    cout << csucs << " ";  
    
    for(int i=0; i<szomsz[csucs].size(); i++) {
        int next = szomsz[csucs][i];
        if(!volt[next]) {
            dfs(next, szomsz, volt); 
        }
    }
}

void bfs(int csucs, vector<vector<int>>& szomsz, vector<bool>& volt){
    queue<int> q;
    q.push(csucs);
    volt[csucs]=true;
    while(!q.empty()){
        int jelenlegi=q.front();
        q.pop();

        cout<<jelenlegi<<" ";

        for(int i=0; i<szomsz[jelenlegi].size(); i++){
            int kovi = szomsz[jelenlegi][i];
            if(!volt[kovi]){
                q.push(kovi);
                volt[kovi] = true;
            }
        }
    }
    cout<<"\n";
}

void dfs_csomagolo(vector<vector<int>>& szomsz, int n){
    vector<bool> volt(n+1, false);  

    for(int i=1; i<=n; i++) {
        if(!volt[i]) {
            dfs(i, szomsz, volt);
        }
    }
}

void bfs_csomagolo(vector<vector<int>>& szomsz, int n){
    vector<bool> volt(n+1, false);  

    for(int i=1; i<=n; i++) {
        if(!volt[i]) {
            bfs(i, szomsz, volt);
        }
    }
}

void beolvas(int m, vector<vector<int>>& szomsz){
    
    
    
    for(int i=0; i<m; i++) {
        int u, v;
        f >> u >> v;  
        szomsz[u].push_back(v);  
        szomsz[v].push_back(u);
    }
}

int main() {
    int n, m;
    f >> n >> m;  
    vector<vector<int>> szomsz(n+1);  
    beolvas(m, szomsz);
    
    cout<<"\nMelysegi bejaras:\n";
    dfs_csomagolo(szomsz, n);

    cout<<"\nSzelessegi bejaras:\n";
    bfs_csomagolo(szomsz, n);
    

    return 0;
}