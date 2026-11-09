#include<bits/stdc++.h>
using namespace std;

int n, m, q,b[8000005]; 
char a[2005][2005];
int zuzong(int k){
    if(b[k] == k) return k;
    else return b[k] = zuzong(b[k]); 
}
int main(){
    int t; 
    cin >> t; 
    while(t--) {
        cin >> n >> m >> q;
        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                cin >> a[i][j];
            }
        }
        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                b[(i-1)*m+j] = (i-1)*m+j; 
                b[(i-1)*m+j + n*m] = (i-1)*m+j + n*m; 
            }
        }
        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                int blue = (i-1)*m+j;
                int red = (i-1)*m+j + n*m;
                if(a[i][j] == '.') {
                    b[zuzong(blue)] = zuzong(red);
                }
                if(j < m) {
                    if(a[i][j] != 'R' && a[i][j+1] != 'R') {
                        b[zuzong(blue)] = zuzong(blue + 1);
                    }
                    if(a[i][j] != 'B' && a[i][j+1] != 'B') {
                        b[zuzong(red)] = zuzong(red + 1);
                    }
                }
                if(i < n) {
                    if(a[i][j] != 'R' && a[i+1][j] != 'R') {
                        b[zuzong(blue)] = zuzong(blue + m);
                    }
                    if(a[i][j] != 'B' && a[i+1][j] != 'B') {
                        b[zuzong(red)] = zuzong(red + m);
                    }
                }
            }
        }
        while(q--) {
            int stx, sty, enx, eny;
            cin >> stx >> sty >> enx >> eny;
            stx++; sty++; enx++; eny++;
            
            int startnum = (stx - 1) * m + sty,end_blue = (enx - 1) * m + eny,end_red = (enx - 1) * m + eny + n*m; 
            bool ok = false;
            if(a[enx][eny] != 'R' && zuzong(startnum) == zuzong(end_blue)) {
                ok = true;
            }
            if(a[enx][eny] != 'B' && zuzong(startnum) == zuzong(end_red)) {
                ok = true;
            }
            
            if(ok){
                cout << "YES" << endl;
            } 
            else {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}
