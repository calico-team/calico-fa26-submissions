#include <iostream>
using namespace std:
int main(){
        int T;
        cin>>T;
        while(T--){
        int N,K;
        cin>>N>>K;

       charA[30];
       for(int i=0;i<K;i++){
        cin>>A[i];
        }

        string answer(N,'?');
        for(int k=0;k<k-1;k++)
        char ch=A[k];

        string guess(N,ch);
        cout<< guess << endl;
        cout.flush();

        string response;
        cin>>response;
        if(response == "CORRECT"){
        break;
        }
        for(int i=0;i<N;i++){
        if(response [i]!='_'){
           answer[i]=ch;
           }
           }
           }

         for(int i=0;i<N;i++){
         if(answer[i] == '?'){
            answer[i]=A[K-1];
            }
           }
         cout<<answer<<endl;
         cout.flush();

         string last;
         cin>>last;
         }
          return 0;
     