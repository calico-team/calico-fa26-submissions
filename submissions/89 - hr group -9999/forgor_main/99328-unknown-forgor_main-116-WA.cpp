#include <bits/stdc++.h>
using namespace std;
#define int long long
void first(){
    int n;
    cin >> n;
    vector<int> edges[n + 1];
    int checksum = 0;
    for(int i = 0; i < n - 1; i++){
        int a, b;
        cin >> a >> b;
        if(a > b){
            swap(a, b);
        }
        assert(a <= b);
        edges[a].push_back(b);
    }
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < edges[i].size(); j++){
            if(j == 0){
                cout << edges[i][j] + 200000 << " ";
                checksum += edges[i][j] + 200000;
                checksum %= 1000001;
            } else{
                cout << edges[i][j]<< " ";
                checksum += edges[i][j];
                checksum %= 1000001;
            }
        }
    }
    cout << checksum << endl;
}
void second(){
    int n;
    cin >> n;
    vector<int> edges[n + 1];
    int ind = -1;
    vector<int> input;
    for(int i = 0; i < n - 1; i++){
        int a;
        cin >> a;
        input.push_back(a);
    }
    int checksum;
    cin >> checksum;
    if(checksum == -1){
        int ind = 0;
        for(int i = 0; i < n - 1; i++){
            if(input[i] >= 200000){
                ind++;
                //input[i] = input[i] - 200000;
            }
            edges[ind].push_back(input[i]);
        }
    } else{
        int cur = 0;
        for(int i = 0; i < n - 1; i++){
            if(input[i] == -1){
                continue;
            }
            cur += input[i];
        }
        while(checksum < cur){
            checksum += 1000001;
        }
        int missing = checksum - cur;
        //cout << missing << endl;
        for(int i = 0; i < n - 1; i++){
            if(input[i] == -1){
                input[i] = missing;
            }
        }


        int ind = 0;
        for(int i = 0; i < n - 1; i++){
            if(input[i] >= 200000){
                ind++;
                input[i] = input[i] - 200000;
            }
            edges[ind].push_back(input[i]);
        }
    }

    for(int i = 1; i <= n; i++){
        for(int j = 0; j < edges[i].size(); j++){
            cout << i << " " << edges[i][j] << endl;
        }
    }
    // (sum + x) % 1000000 = checksum
}
signed main(){
    string s;
    cin >> s;
    if(s == "FIRST"){
        first();
    } else{
        second();
    }
    return 0;
}