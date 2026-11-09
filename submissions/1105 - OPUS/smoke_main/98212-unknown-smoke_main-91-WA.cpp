#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main()
{
    int tc; cin>>tc;
    for(int testcase=0;testcase<tc;testcase++){
        bool poss=true;
        int smk = 2, n, r, cd;
        vector<int> reqs;
        cin>>n>>r;
        for(int i=0;i<n;i++){
            int a; cin>>a;
            reqs.push_back(a);
        }
        //request times come in sorted
        for(int t=0;t<=reqs[n-1];t++){
            //smoke count management and cooldown updates
            cd--;
            
            if(cd==0){
                smk++;
                //cout<<"pl";
                cd = r;
            }
            
            if(smk==2){
                cd = r;
            }
            //cout<<cd;
            if(reqs[0]==t){
                reqs.erase(reqs.begin());
                smk--;
                //cout<<"m";
                if(smk<0){
                    poss = false;
                    cout<<"NO"; 
                    break;
                }
            }
            //cout<<smk<<" ";
        }
        if(poss){
            cout<<"YES";
        }
        cout<<"\n";
    }
}