//Kosa Matyas, 512, kmim2552

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

ifstream f("2.in");

bool bfs(int csucs, vector<int>& szinek, vector<vector<int>>& szomsz){
    queue<int> q;
    q.push(csucs);


    while(!q.empty()){
        int jelenlegi=q.front();
        q.pop();

        for (int v : szomsz[jelenlegi]) {
            if (szinek[v] == -1) {
                szinek[v] = 1 - szinek[jelenlegi];
                q.push(v);
            } else if (szinek[v] == szinek[jelenlegi]) {
                return false;
            }
        }
    }

    return true;
}

void beolvas(int m, vector<vector<int>>& szomsz){
    for(int i=0; i<m; i++) {
        int u, v;
        f >> u >> v;  
        szomsz[u].push_back(v);  
        szomsz[v].push_back(u);
    }
}

int main(){
    int n, m;
    f >> n >> m;  
    vector<vector<int>> szomsz(n+1);  
    beolvas(m, szomsz);

    vector<int>szinek(n, -1);

    bool paros=true;
    for(int i=0; i<n; i++){
        if(szinek[i]==-1){
            szinek[i]=1;
            if(!bfs(i, szinek, szomsz)){
                paros=false;
                break;
            }
        }
    }

    if(paros){
        cout<<"\nigen\n";
    }
    else{
        cout<<"\nnem\n";
    }
}