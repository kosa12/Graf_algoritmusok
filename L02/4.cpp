//Kosa Matyas, 512, kmim2552

#include <iostream>
#include <vector>
#include <fstream>
#include <stack>

using namespace std;

void tolopogiai_sort_csomagolo(int csucs, vector<bool>& volt, vector<vector<int>>& szomsz, stack<int>& Stack);
void tolopogiai_sort(int n, vector<vector<int>>& szomsz);

ifstream f("4.in");

int main()
{
    int n, m,  u, v;
    f >> n >> m;
    vector<vector<int>> szomsz(n+1);

    for (int i = 0; i < m; i++) {
        f >> u >> v;
        szomsz[u].push_back(v);
    }

    cout << "\n";
    tolopogiai_sort(m, szomsz);
    cout << "\n";
    return 0;
}

void tolopogiai_sort_csomagolo(int csucs, vector<bool>& volt, vector<vector<int>>& szomsz, stack<int>& Stack)
{
    volt[csucs] = true;

    for (int i : szomsz[csucs]) {
        if (!volt[i]) {
            tolopogiai_sort_csomagolo(i, volt, szomsz, Stack);
        }
    }
    Stack.push(csucs);
}

void tolopogiai_sort(int n, vector<vector<int>>& szomsz)
{
    stack<int> Stack;
    vector<bool> volt(n, false);

    for (int i = 0; i < n; i++) {
        if (!volt[i]) {
            tolopogiai_sort_csomagolo(i, volt, szomsz, Stack);
        }
    }

    while (Stack.empty() == false) {
        cout << Stack.top() << " ";
        Stack.pop();
    }
}