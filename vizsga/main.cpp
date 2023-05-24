// Kósa Mátyás, 512/2
// kmim2252

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <stack>

using namespace std;

ifstream f("dune.txt");

void kor_kereses_ut(int v, int kezdo, int jelenlegi_tav, int tav, vector<vector<int>> &szomsz, vector<bool> &volt, stack<int> &ut)
{

    volt[v] = true;
    ut.push(v);
    jelenlegi_tav++;

    if (jelenlegi_tav == tav)
    {
        if (szomsz[v][kezdo] == 1)
        {
            cout << "Kör, amelynek a hosszúsága " << tav << ": ";
            for (int i = 0; i < tav; i++)
            {
                cout << ut.top() + 1 << " ";
                ut.pop();
            }
            cout << v + 1 << endl;
        }
        volt[v] = false;
        ut.pop();
        return;
    }

    for (int i = 0; i < szomsz.size(); i++)
    {
        if (szomsz[v][i] == 1 && !volt[i])
        {
            kor_kereses_ut(i, kezdo, jelenlegi_tav, tav, szomsz, volt, ut);
        }
    }

    volt[v] = false;
    ut.pop();
}

void kor_kereses(int tav, vector<vector<int>> &szomsz)
{
    vector<bool> volt(szomsz.size(), false);
    stack<int> ut;

    for (int i = 0; i < szomsz.size(); i++)
    {
        kor_kereses_ut(i, i, 0, tav, szomsz, volt, ut);
        volt[i] = true;
    }
}

vector<int> izolalt(vector<vector<int>> &incidencia, int n)
{
    vector<int> izolalt_pontok;

    for (int i = 0; i < n; ++i)
    {
        bool ok = true;
        for (int j = 0; j < incidencia[i].size(); ++j)
        {
            if (incidencia[i][j] == 1)
            {
                ok = false;
                break;
            }
        }
        if (ok)
        {
            izolalt_pontok.push_back(i);
        }
    }

    return izolalt_pontok;
}

bool osszefuggo(vector<vector<int>> szomsz, int n)
{
    vector<bool> volt(n, false);

    queue<int> q;
    q.push(0);
    volt[0] = true;

    while (!q.empty())
    {
        int jelenlegi = q.front();
        q.pop();

        for (int i = 0; i < n; i++)
        {
            if (szomsz[jelenlegi][i] == 1 && !volt[i])
            {
                q.push(i);
                volt[i] = true;
            }
        }
    }

    for (bool v : volt)
    {
        if (!v)
        {
            return false;
        }
    }

    return true;
}

void szomszed(vector<vector<int>> &szomsz, vector<vector<int>> incidencia, int n, int m)
{
    for (int i = 0; i < m; ++i)
    {
        int u = -1, v = -1;
        for (int j = 0; j < n; ++j)
        {
            if (incidencia[j][i] == 1)
            {
                if (u == -1)
                {
                    u = j;
                }
                else
                {
                    v = j;
                    break;
                }
            }
        }
        szomsz[u][v] = 1;
        szomsz[v][u] = 1;
    }

    cout << "Szomszedsagi matrix:\n\n";
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cout << szomsz[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool teljes(vector<vector<int>> szomsz, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (szomsz[i][j] != 1 || szomsz[j][i] != 1)
            {
                return false;
            }
        }
    }

    return true;
}

void beolvas(vector<vector<int>> &incidencia, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            f >> incidencia[i][j];
        }
    }
}

int main()
{
    int n;
    f >> n;
    int m;
    f >> m;
    int tav;
    vector<vector<int>> incidencia(n, vector<int>(m, 0));
    beolvas(incidencia, n, m);
    f >> tav;

    // a) pont
    vector<vector<int>> szomsz(n, vector<int>(n, 0));
    szomszed(szomsz, incidencia, n, m);

    // b) pont
    if (teljes(szomsz, n))
    {
        cout << "Igen, teljes\n";
    }
    else
    {
        cout << "Nem teljes\n";
    }

    // c) pont
    if (osszefuggo(szomsz, n))
    {
        cout << "Igen, osszefuggo\n";
    }
    else
    {
        cout << "Nem osszefuggo\n";
    }

    // d) pont
    vector<int> izolalt_pontok = izolalt(incidencia, n);
    if (izolalt_pontok.size() > 0)
    {
        cout << "Barat nelkuli ember: ";
        for (int csomopont : izolalt_pontok)
        {
            cout << csomopont + 1 << " ";
        }
        cout << "\n";
    }
    else
    {
        cout << "Mindenkinek van baratja\n";
    }

    // e) pont
    // kor_kereses(tav, szomsz);

    return 0;
}