#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <deque>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <limits>
#include <fstream>
#include <bitset>
#include <sstream>
#include <cstring>
#include <cctype>
#include <utility>
#include <tuple>
#include <functional>
#include <memory>
#include <random>
#include <chrono>
#include <cassert>
#include <stdexcept>
#include <exception>
#include <optional>
#include <variant>
#include <filesystem>
#include <regex>

using namespace std;
using ll = long long;
constexpr ll MOD = 10e9+7;


int main() {
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


