#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <cstring>
#include <cctype>
#include <cassert>

using namespace std;
using ll = long long;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll t;
    cin>>t;
    while(t--){
        ll N,K;
        cin>>N>>K;
        ll a;
        cin>>a;
        bool comp=true;
        ll charge=1,r=0;
        for(ll i=1;i<N;i++){
            if(comp){
                ll b;
                cin>>b;
                charge+=(b-a+r)/K;
                r=(b-a+r)%K;
                if(charge>=2LL){
                    r=0;
                    charge=2;
                }
                charge--;
                a=b;
                if(charge==-1){
                    comp=false;
                }
            }
            else{
                cin>>a;
            }
        }
        if(comp){
            cout<<"YES\n";
        }
        else{
            cout<<"NO\n";
        }
    }
}


