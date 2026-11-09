#include<iostream>
#include<string>
using namespace std;
int main(){
    int T;
    cin>>T;
    for(int i=0;i<T;i++){
        int N,K;
        cin>>N>>K;
        string s="";
        for(int j=0;j<K;j++){
            char c;
            cin>>c;
            s+=c;
        }
        string s2(N,'_');
        for(int j=0;j<K;j++){
            string tempt=s2;
            for(int k=0;k<N;k++){
                if(tempt[k]=='_'){
                    tempt[k]=s[j];
                }
            }
            cout<<tempt<<endl;
            string result;
            cin>>result;
            if(result=="CORRECT"){
                break;
            }
            for (int k = 0; k < N; k++) {
                if (result[k] != '_') {
                    s2[k] = result[k];
                }
            }
        }
    }
    return 0;
}