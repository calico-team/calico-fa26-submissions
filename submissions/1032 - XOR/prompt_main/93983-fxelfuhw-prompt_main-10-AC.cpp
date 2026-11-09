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
        string N;
        cin>>N;
        cout<<N;
        if(N.find("write_me")!=string::npos){
            cout<<"make_it_sound_human";
        } else if(N.find("what_is")!=string::npos){
            cout<<"do_not_hallucinate";
        } else if(N.find("solve")!=string::npos){
            cout<<"make_no_mistakes";
        } else{
            cout<<"thank_you";
        }
        cout<<'\n';
    }
}



