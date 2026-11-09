#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <queue>

#define fff(i, a, b) for(int i = a; i < b; i++)
#define N 205   
using namespace std;
int n, m, q;
int component[N][N][2], grid[N][N];

void floodfill(int r, int c, int mode, int color){
    // this one must be done
    component[r][c][mode] = color;
    
    // can move nearby if that's valid
    if (component[r][c][1-mode] == 0 && grid[r][c] == 2){
        floodfill(r, c, 1-mode, color);
    }
    if (r < n-1 && component[r+1][c][mode] == 0 && (grid[r+1][c] == 2 || grid[r+1][c] == mode)){
        floodfill(r+1, c, mode, color);
    }
    if (r > 0 && component[r-1][c][mode] == 0 && (grid[r-1][c] == 2 || grid[r-1][c] == mode)){
        floodfill(r-1, c, mode, color);
    }
    if (c < m-1 && component[r][c+1][mode] == 0 && (grid[r][c+1] == 2 || grid[r][c+1] == mode)){
        floodfill(r, c+1, mode, color);
    }
    if (c > 0 && component[r][c-1][mode] == 0 && (grid[r][c-1] == 2 || grid[r][c-1] == mode)){
        floodfill(r, c-1, mode, color);
    }
}

void do_thing(){
    cin >> n >> m >> q;
    fff(i, 0, n){
        string s; cin >> s;
        fff(j, 0, m){
            if (s[j] == '.'){
                grid[i][j] = 2;
            }else if (s[j] == 'R'){
                grid[i][j] = 0;
            }else{
                grid[i][j] = 1;
            }
            component[i][j][0] = 0;
            component[i][j][1] = 0;
        }
    }

    // floodfill
    int col = 1;
    fff(i, 0, n){
        fff(j, 0, m){
            fff(k, 0, 2){
                if (component[i][j][k] == 0 && (grid[i][j] == 2 || grid[i][j] == k)){
                    floodfill(i,j,k,col);
                    col++;
                }
            }
        }
    }
    // cout << endl;
    // fff(i, 0, n) {fff(j, 0, m) cout << component[i][j][0]; cout << endl;}
    // cout << endl;
    // fff(i, 0, n) {fff(j, 0, m) cout << component[i][j][1]; cout << endl;}
    fff(i, 0, q){
        int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
        if (component[r1][c1][1] == component[r2][c2][1] || component[r1][c1][1] == component[r2][c2][0]){
            cout << "YES" << endl;
        }else{
            cout << "NO" << endl;
        }
    }    

}

int main(){
    int t;
    cin >> t;
    while(t--){
        do_thing();
    }
}