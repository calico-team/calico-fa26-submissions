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
        cd = r;
        for(int i=0;i<n;i++){
            int a; cin>>a;
            reqs.push_back(a);
        }
        //request times come in sorted
        for(int t=1;t<=reqs[n-1];t++){
            //smoke count management and cooldown updates
            cd--;
            if(cd==0){
                smk++;
                cd = r;
            }
            else if(smk==2){
                cd = r;
            }
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