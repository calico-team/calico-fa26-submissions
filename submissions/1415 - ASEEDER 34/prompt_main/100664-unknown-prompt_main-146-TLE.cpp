#include <random>
#include <string>
#include <iostream>
using namespace std;
int t;
int n;
int l;
char A[26];
char R[100];
string result;

void Guesses(){
    for(int m=0;m<l;m++){
        
        if(R[m]=='_') cout<<random()*n;
        else cout<<R[m];
    }
    cout<<endl;

}


int main(){
    
    cin>>t;
    for (int j=0;j<t;j++){
        for (int q=0;q<100;q++) R[q]='_';
        cin>>l;
        cin>>n;
        for(int i=0;i<n;i++){
            cin>>A[i];
        }
        bool F=true;
        while (F){
            Guesses();
            cin>>result;
            if(result=="CORRECT") F=false;
            else {
                for(int k=0;k<n;k++){
                    if(result[k]!='_'){
                        R[k]=result[k];
                    }
                }
            }
        }
    }
    

    
}
