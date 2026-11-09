#include <bits/stdc++.h>
using namespace std;
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int T;
    cin>>T;
    while(T--){
        long long n,k;
        cin>>n>>k;

        vector<long long> x(n), y(n), z(n);
        vector<char> d(n);
        for(int i=0; i<n; i++) cin>> x[i]>>y[i]>>z[i]>>d[i];
        
        long long total_agua=0;
        for(int noche=0; noche<k; noche++){
            for(int i=0; i<n; i++){
                bool tapado=false;
                for(int j=0; j<n; j++)
                    if(x[i]==x[j] && y[i]==y[j]&&z[i]<z[j])
                        tapado=true;
                if (!tapado)total_agua++;
            }
            for(int i=0; i<n; i++){
                if (d[i]=='E') x[i]++;
                else y[i]++;
            }
        }
        cout<<total_agua<<"\n";
    }
}
    