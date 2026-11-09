// Source: https://usaco.guide/general/io
#include <bits/stdc++.h>
using namespace std;

long long solve(int N, int K, vector<tuple<int, int, int, char>> L){
    long long answer =0;
    long long c=0;
    for(int i=0; i<N; i++){
        int Xe=get<0>(L[i]);
        int Ye=get<1>(L[i]);
        int De=get<3>(L[i]);
        if(De!='E') continue;
        for(int j=0; j<N; j++){
        int Xn=get<0>(L[j]);
        int Yn=get<1>(L[j]);
        int Dn=get<3>(L[j]);
        if(Dn!='N') continue;
        long long Se=(long long)Xe+Ye;
        long long Sn=(long long)Xn+Yn;
        if(Se!=Sn)continue;
        long long d=(long long)Xn-Xe;
        if(d>=0 && d<K){
            c++;
        }
    }
}
answer=((long long)N*K)-c;
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin>>t;
    while (t--){
        int N, K; cin>>N>>K;
        vector<tuple<int, int, int, char>> L;
        for (int i = 0; i < N; i++){
            int X, Y, Z;
            char D;
            cin>>X>>Y>>Z>>D;
            L.push_back({X, Y, Z, D});
        }
        cout<<solve(N, K, L)<<endl;
    }
}