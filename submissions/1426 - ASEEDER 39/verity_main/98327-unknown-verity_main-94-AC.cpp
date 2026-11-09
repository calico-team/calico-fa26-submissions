#include<bits/stdc++.h>
using namespace std;
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        int n,k;
        scanf("%d %d",&n,&k);
        char a[26];
        for(int i=0;i<k;i++) scanf(" %c",&a[i]);
        char known[105];
        for(int i=0;i<n;i++) known[i]='?';
        bool ok=0;
        for(int j=0;j<k;j++){
            char g[105];
            for(int i=0;i<n;i++){
                if(known[i]!='?') g[i]=known[i];
                else g[i]=a[j]; 
            }
            g[n]='\0';
            cout<<g<<endl;
            char res[105];
            scanf("%s",res);
            if(strcmp(res,"CORRECT")==0){
                ok=1;
                break;
            }
            for(int i=0;i<n;i++){
                if(res[i]!='_') known[i]=res[i];		//'_'
            }
        }
        if(ok==true){
 
        }
        else{
            char g[105];
            for(int i=0;i<n;i++){
                if(known[i]!='?') g[i]=known[i];
                else g[i]=a[0];
            }
            g[n]='\0';
            cout<<g<<endl;
            char res[105];
            scanf("%s",res);
        }
        }
    return 0;
}