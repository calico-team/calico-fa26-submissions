#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<string> possible; 
        for(int i = 0; i<k; i++){
            string c;
            cin >> c;
            possible.push_back(c);
        }
        string correct="";
        for(int i = 0; i<n; i++){
            correct+=" ";
        }
        bool flag=false;
        for(int i = 0; i<k; i++){
            string s="";
            for(int j=0; j<n; j++){
                s+=possible[i];
            }
            cout << s << "\n";
            string x;
            cin >> x;
            if(x=="CORRECT"){
                flag=true;
                break;
            }
            for(int j = 0; j<n; j++){
                if(x[j]!='_'){
                    correct[j]=x[j];
                }
            }
        }
        if(flag){
            continue;
        }
        cout << correct << "\n";
        string x;
        cin >> x;
        
        
    }
}