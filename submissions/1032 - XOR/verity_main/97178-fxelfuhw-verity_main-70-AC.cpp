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
        vector<char> arr(K);
        for(ll i=0;i<K;i++){
            cin>>arr[i];
        }
        ll change=-1;
        string str="",ans=string(N,'n');
        for(ll i=0;i<N;i++){
            str+='_';

        }
        ll j=0;
        while(true){
            if(j!=0){
                cin>>str;
                if(str=="CORRECT"){
                    break;
                }
            }
            for(ll i=0;i<N;i++){
                if(str[i]=='_'){
                    ans[i]=arr[j];
                }
            }
            j++;
            cout<<ans<<endl;

        }
    }
}


