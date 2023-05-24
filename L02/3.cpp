//Kosa Matyas, 512, kmim2552

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

ifstream f("3.in");

bool dfs(int csucs, vector<int>szinek, vector<vector<int>>& szomsz){
    szinek[csucs]=1;
    for(int i : szomsz[csucs]){
        if(szinek[i] == 0){
            if(dfs(i, szinek, szomsz)){
                return true;
            }
        }
        else if(szinek[i]==1){
            return true;
        }
    }

    szinek[csucs]=2;
    return false;
}

void beolvas(int m, vector<vector<int>>& szomsz){
    for(int i=0; i<m; i++) {
        int u, v;
        f >> u >> v;  
        szomsz[u].push_back(v);
    }
}

int main(){
    int n, m;
    f >> n >> m;  
    vector<vector<int>> szomsz(n+1);  
    beolvas(m, szomsz);

    vector<int>szinek(n, 0);

    bool kor=false;
    for(int i=1; i<=n; i++){
            if(szinek[i]==0 && dfs(i, szinek, szomsz) ){
                kor=true;
                break;
            }
    }

    if(kor){
        cout<<"\nigen\n";
    }
    else{
        cout<<"\nnem\n";
    }
}