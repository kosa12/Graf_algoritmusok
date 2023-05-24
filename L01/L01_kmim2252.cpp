//Kosa Matyas
//512/2

#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <tuple>

using namespace std;
ifstream f("graf.in");

struct graf {
    int kezdopont;
    int vegpont;
    int suly;
};

typedef vector<graf> vg;
typedef vector<vector<int>> vv;

void beolvas(int m, vg& kezdo);
void szomszedsagi_matrix(int m, vv& szomsz_mat, vg& kezdo);
void kiir_szomsz_mat(int n, vv& szomsz_mat);
void szomsz_to_inc(int m, vv& szomsz_mat, vv& inc_mat, vg&kezdo);
void kiir_inc_mat(int n, int m, vv& inc_mat);
void szom_lista(vector<vector<pair<int, int>>>& szomsz_lista, vv& inc_mat);
void kiir_szom_lista(vector<vector<pair<int, int>>>& szomsz_lista);
void elek_listaja(vector<tuple<int, int, int>>& elek_list, vector<vector<pair<int, int>>>& szomsz_lista);
void kiir_elek_listaja(vector<tuple<int, int, int>>& elek_list);
void izolalt_csp(vv& szomsz_mat);
void vegpontok(vv& inc_mat);
bool regularis(vv& szomsz_mat);
void kiir_regularis(vv& szomsz_mat);

int main() {

    int n, m;
    f >> n >> m;
    vg kezdo(m);
    beolvas(m, kezdo);

    //szomszedsagi matrix
    vv szomsz_mat(n, vector<int>(n, 0));
    szomszedsagi_matrix(m, szomsz_mat, kezdo);
    kiir_szomsz_mat(n, szomsz_mat);

    //incidencia matrix
    vv inc_mat(n, vector<int>(m, 0));
    szomsz_to_inc(n, szomsz_mat, inc_mat, kezdo);
    kiir_inc_mat(n, m, inc_mat);

    //szomszedsagi lista
    vector<vector<pair<int, int>>> szomsz_lista(inc_mat.size());
    szom_lista(szomsz_lista, inc_mat);
    kiir_szom_lista(szomsz_lista);

    //elek listaja
    vector<tuple<int, int, int>> elek_list;
    elek_listaja(elek_list, szomsz_lista);
    kiir_elek_listaja(elek_list);

    //izolalt csomopontok a szomszedsagi matrixbol
    izolalt_csp(szomsz_mat);
    
    //vegpontok az incidencia matrixbol
    vegpontok(inc_mat);

    //regularis-e a graf, ugy hogy  meg van adva a szomszedsagi matrix
    kiir_regularis(szomsz_mat);

    return 0;

}

//fuggvenyek:

void kiir_regularis(vv& szomsz_mat){
    if(regularis(szomsz_mat)){
        cout<<"\nRegularis\n";
    }
    else{
        cout<<"\nNem regularis\n";
    }
}

bool regularis(vv& szomsz_mat){

    int fokszam=0;
    for(int i=0; i<szomsz_mat.size(); i++){
        if(szomsz_mat[0][i]!=0){
            fokszam++;
        }
    }

    for(int i=0; i<szomsz_mat.size(); i++){
        int akt_foksz=0;
        for(int j=0; j<szomsz_mat.size(); j++){
            if(szomsz_mat[i][j]!=0){
                akt_foksz++;
            }
        }

        if(akt_foksz!=fokszam){
            return false;
        }
    }
    return true;

}

void vegpontok(vv& inc_mat){
    cout<<"\nVegpont(ok):\n";
    bool vegpont_volt = false;
    for(int i=0; i<inc_mat.size(); i++){
        int vegpont_nr = 0;
        int vegpont=-1;
        for(int j=0; j<inc_mat.size(); j++){
            if(inc_mat[i][j]!=0){
                int x=inc_mat[i][j];
                vegpont_nr++;
                vegpont=i;
            }
        }

        if(vegpont_nr==1){
            vegpont_volt=true;
            cout<<vegpont+1<<" ";
        }
    }

    if(!vegpont_volt){
        cout<<"egyik se\n";
    }
    else{
        cout<<"\n";
    }
    
}

void izolalt_csp(vv& szomsz_mat){
    bool izolalt_volt = false;
    cout<<"\nIzolalt csomopont(ok):\n";
    for(int i=0; i<szomsz_mat.size(); i++){
        bool izolalt_e = true;
        for(int j=0; j<szomsz_mat[i].size(); j++){
            if(szomsz_mat[i][j]!=0){
                izolalt_e=false;
                break;
            }
        }

        if(izolalt_e){
            izolalt_volt=true;
            cout<<i+1<<"\n";
        }
    }

    if(!izolalt_volt){
        cout<<"egyik se\n";
    }
}

void kiir_elek_listaja(vector<tuple<int, int, int>>& elek_list)
{
    cout<<"\nElek listaja:\n";
    for(int i=0; i<elek_list.size(); i++){
        cout<<"("<<get<0>(elek_list[i])<<","<<get<1>(elek_list[i])<<","<<get<2>(elek_list[i])<<")\n";
    }
}

void elek_listaja(vector<tuple<int, int, int>>& elek_list, vector<vector<pair<int, int>>>& szomsz_lista){
    
    for(int i=0; i<szomsz_lista.size(); i++){
        for(int j=0; j<szomsz_lista[i].size(); j++){
            int pont = szomsz_lista[i][j].first;
            int suly = szomsz_lista[i][j].second;
            if(pont>i){
                elek_list.push_back(make_tuple(i+1, pont, suly));
            }
        }
    }
}

void kiir_szom_lista(vector<vector<pair<int, int>>>& szomsz_lista){
    cout<<"\nSzomszedsagi lista:\n";
    for(int i=0; i<szomsz_lista.size(); i++){
        cout<< i+1<< ": ";
        for(int j=0; j<szomsz_lista[i].size(); j++){
            cout<<"("<<szomsz_lista[i][j].first<<","<<szomsz_lista[i][j].second<<")";
        }
        cout<<"\n";
    }
}

void szom_lista(vector<vector<pair<int, int>>>& szomsz_lista, vv& inc_mat){
    
    for (int i=0; i<inc_mat[0].size(); i++){
        int honnan=-1;
        int hova=-1;
        int suly;
        for(int j=0; j<inc_mat.size(); j++){
            if(inc_mat[j][i]!=0){
                if(honnan==-1){
                    honnan=j;
                }
                else{
                    hova=j;
                }
                suly=inc_mat[j][i];
            }
        }

        if(honnan != -1 and hova !=-1){
            szomsz_lista[honnan].push_back({hova+1, suly});
            szomsz_lista[hova].push_back({honnan+1, suly});
        }
    }
}

void kiir_inc_mat(int n, int m, vv& inc_mat)
{
    cout << "Incidencia matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << inc_mat[i][j] << " ";
        }
        cout << "\n";
    }
}

void szomsz_to_inc(int n, vv& szomsz_mat, vv& inc_mat, vg& kezdo)
{
    int oszl = n;
    int el = 0;
    for (int i = 0; i < oszl; i++) {
        for (int j = 0; j <= i; j++) {
            if (szomsz_mat[i][j] != 0) {
                inc_mat[j][el] = inc_mat[i][el] = szomsz_mat[j][i]; //suly
                el++;
            }
        }
    }
}

void kiir_szomsz_mat(int n, vv& szomsz_mat)
{
    cout << "\nSzomszedsagi matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << szomsz_mat[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void szomszedsagi_matrix(int m, vv& szomsz_mat, vg& kezdo)
{
    for (int i = 0; i < m; i++) {
        szomsz_mat[kezdo[i].kezdopont-1][kezdo[i].vegpont-1] = kezdo[i].suly;
        szomsz_mat[kezdo[i].vegpont-1][kezdo[i].kezdopont-1] = kezdo[i].suly;
    }
}

void beolvas(int m, vg& kezdo){
    for (int i = 0; i < m; i++)
    {
        f >> kezdo[i].kezdopont >> kezdo[i].vegpont >> kezdo[i].suly;
    }
}
