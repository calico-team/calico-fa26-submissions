
#include <stdio.h>
#include <stdlib.h>

char a[205][205];
int find(int p[], int x){
    if(p[x] != x){
        p[x] = find(p, p[x]);
    }return p[x];
    
}void unite(int p[],int sz[],int x, int y) 
{
    x = find(p, x);
    y = find(p, y);
    if(x == y) return;
    if(sz[x]< sz[y]){
        int z = x;
        x = y;
        y = z;
    }
    
    
    p[y] = x;
    sz[x] += sz[y];
}
int id(int x, int y, int z, int n, int m){
    return z * n * m + x * m + y;}
int ok(char c, int z) {
    if(c == '.') return 1;
    if(z == 0) return c == 'B';
    return c == 'R';
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int n, m, q;
        scanf("%d %d %d", &n, &m, &q);
        for(int i=0; i<n; i++){
            scanf("%s", a[i]);
        }
        int k=2*n*m;
        int *p = malloc(k * sizeof(int));
        int *sz = malloc(k *sizeof(int));

        for(int i = 0; i < k; i++){
            p[i] =i;
            sz[i]=1;
        }
        for(int i = 0; i < n;i++){
            for(int j=0;j < m; j++) {
                if(a[i][j]=='.') {
                    unite(p, sz, id(i,j,0,n,m),
                                  id(i,j,1,n,m));
                }
            }
        }
        for(int z =0; z < 2; z++) {
            for(int i= 0; i < n; i++) {
                for(int j=0; j<m; j++) {
                    if(!ok(a[i][j], z)) continue;
                    if(i + 1 < n && ok(a[i+1][j], z)) {
                        unite(p, sz, id(i,j,z,n,m),
                                      id(i+1,j,z,n,m));
                    }
                    if(j+ 1 < m && ok(a[i][j+1], z)) {
                        unite(p, sz, id(i,j,z,n,m),
                                      id(i,j+1,z,n,m));
                    }
                }
            }
        }

        while(q--){
            int x, y, u, v;
            scanf("%d %d %d %d",&x, &y, &u,&v);

            int s = find(p,id(x,y,0,n,m));
            int ans =0;

            for(int z=0; z<2;z++){
                if(ok(a[u][v], z)) {
                    if(s==find(p, id(u,v,z,n,m))) {
                        ans= 1;
                    }
                }
            }
            if(ans) printf("YES\n");
            else printf("NO\n");
        }free(p);
        free(sz);
    }
    return 0;
}
