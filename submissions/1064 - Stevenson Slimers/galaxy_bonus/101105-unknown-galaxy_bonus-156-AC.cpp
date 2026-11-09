// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;
int r, c;
vector<string> v(201);
vector<vector<int>> connected(201,vector<int>(201,0));
int comp = 1;
void reset(){
    fill(connected.begin(),connected.end(),vector<int>(201,0));
    comp = 1;
}
void dfs(int x, int y, char a){
    if (x >= r ||x<0 || y < 0|| y >= c || connected[x][y] ||(a != v[x][y] && a != '.'&&v[x][y]!='.')){
        return;
    }
    connected[x][y]= comp;

    dfs(x-1,y,v[x][y]);
    dfs(x+1,y,v[x][y]);
    dfs(x,y-1,v[x][y]);
    dfs(x,y+1,v[x][y]);
}
int main() {
    int t; cin >> t;
    while(t--){
        cin >> r >> c;
        int q; cin >> q;
        for (int i =0; i < r; i++){
            cin >> v[i];
        }
        for (int i = 0; i < r; i++){
            for (int j = 0; j < c; j++){
                if (!connected[i][j]){
                    dfs(i,j,v[i][j]);
                    comp++;
                }
            }
        }/*
        for (int i = 0; i < r; i++){
            for (int j = 0 ;j < c; j++){
                cout << connected[i][j];
            }
            cout << endl;
        }*/
        while (q--){
            int x1, x2, y1 ,y2; cin >> x1 >> y1 >> x2 >> y2;
            if (connected[x1][y1] == connected[x2][y2]){
                cout << "YES\n";
            }
            else{
                cout << "NO\n";
            }
        }
        reset();
    }
}
