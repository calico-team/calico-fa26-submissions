#include <iostream>
#include <vector>
using namespace std;

int main() {
    int T;
    cin >> T;
    
    for (int i = 0; i < T; i++) {
        int N, K;
        cin >> N >> K;

        vector<char> A(K);
        for (int j = 0; j < K; j++) {
            cin >> A[j];
        }

        string str;
    for(int i=0;i<N;i++){
        str+='_';
    }for(int i=0;i<K;i++){
        for(int j=0;j<N;j++){
            if(str[j]=='_'){
                str[j]=A[i];
            }
        }cout<<str<<'\n';
        cin>>str;
        if(str=="CORRECT"){
            break;
        }
    }
    }

    return 0;
}