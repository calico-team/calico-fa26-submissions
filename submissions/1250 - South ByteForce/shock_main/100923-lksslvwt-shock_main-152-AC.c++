#include <bits/stdc++.h>
using namespace std;

struct Earth {
    int r, c, p;
};

vector<int> par;

int findNext(int x) {
    int root= x;
    while (par[root]!=root) root= par[root];
    while (par[x]!=root) {
        int nxt=par[x];
        par[x]=root;
        x= nxt;
    }
    return root;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m, q;
        cin>> n>> m>> q;
        vector<Earth> data(q);
        for (int i=0; i < q; i++) {
            cin>> data[i].r>> data[i].c>> data[i].p;
        }

        vector<int> val(n*m, 0);

        par.assign(n*(m+1), 0);
        for (int i=0; i< n*(m+1); i++) par[i]= i;

        for (int i=q-1; i >= 0; i--) {
            int R=data[i].r;
            int C=data[i].c;
            int P=data[i].p;

            for (int r= max(0, R-P); r<= min(n-1, R+P); r++) {
                int dy= r-R;
                int rem= P*P - dy*dy;

                int w= (int)sqrt((double)rem);
                while (w*w > rem) w--;
                while ((w+1)*(w+1) <= rem) w++;

                int low= max(0, C-w);
                int high= min(m-1, C+w);
                int base= r*(m+1);

                int x= findNext(base + low);
                while (x-base <= high) {
                    int col= x-base;
                    int dx= col-C;
                    val[r*m + col]= rem - dx*dx + 1;
                    par[x]= x+1;
                    x= findNext(x+1);
                }
            }
        }

        for (int r=0; r< n; r++) {
            for (int c=0; c< m; c++) {
                if (c> 0) cout<< " ";
                cout<< val[r*m + c];
            }
            cout<< "\n";
        }
    }
}