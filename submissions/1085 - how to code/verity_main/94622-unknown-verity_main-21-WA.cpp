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
        for(int i = 0; i<k; i++){
            string s="";
            for(int j=0; j<n; j++){
                s+=possible[i];
            }
            cout << s << "\n";
            string x;
            cin >> x;
            for(int j = 0; j<n; j++){
                if(x[j]!='_'){
                    correct[j]=x[j];
                }
            }
        }
        cout << correct << "\n";
        string x;
        cin >> x;
        
        
    }
}