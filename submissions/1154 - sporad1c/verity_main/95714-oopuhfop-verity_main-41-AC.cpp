/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void decider(){
    int n,k;
    cin>> n>> k;
    vector<char> a(k);
    for(int i=0; i<k; i++){
        cin>> a[i];
    }
    
    string res(n, '_');
    
    for(int i=0; i<k; i++){
        string guess=res;
        for(int j=0; j<n; j++){
            if(guess[j]=='_'){
                guess[j]=a[i];
            }
        }
        cout<< guess<< endl;
        string ans;
        cin>> ans;
        
        if(ans=="CORRECT"){
            return;
        }
        
        for(int j=0; j<n; j++){
            if(ans[j]!='_'){
                res[j]=ans[j];
            }
        }
    }
}

int main(){
    int t;
    cin>> t;
    while(t--){
        decider();
    }
    return 0;
}