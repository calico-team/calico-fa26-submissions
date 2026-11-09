#include <bits/stdc++.h>
using namespace std;

int main() {
	int t = 0;
    cin >>t;
    for(int a = 0;a<t;a++){
        int n = 0;
        int k = 0;
        cin >>n>>k;
        char c[k];
        for(int i = 0; i < k; i++){
            cin >> c[i];
        }
        string w = "";
        for(int i = 0; i < n; i++){
            w += "_";
        }
        for(int i = 0; i<k;i++){
            for(int j = 0; j<n;j++){
                //haha smileyface '_'
                if(w[j] == '_'){
                    w[j] = c[i];
                }
            }
            cout <<w<< endl;
            string g;
            cin >> g;
            if(g == "CORRECT"){
                break;
            }
            w =g;
        }
    }
}
