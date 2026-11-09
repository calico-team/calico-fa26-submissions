#include <iostream> //g++ -std=c++20 Usaco/main.cpp -o Usaco/ryan.out && Usaco/ryan.out
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include<map>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
using namespace std;
using ll = long long;//woah
//    vector<vector<int>> a(3, vector<int>(3));
#include <string>


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("Usaco/temporary.in");//temporary
    ofstream fout("Usaco/temporary.out"); 
    
    int n;
    cin>>n;
    string s;
    for(int i = 0; i < n; i++){
        cin>>s;
        if(s.find("write_me") != string::npos){
            s+="make_it_sound_human";
        }
        else if(s.find("what_is") != string::npos){
            s+="do_not_hallucinate";
        }
        else if(s.find("solve") != string::npos){
            s+="make_no_mistakes";
        }else{
            s+="thank_you";
        }
        cout<<s<<endl;
    }

}
