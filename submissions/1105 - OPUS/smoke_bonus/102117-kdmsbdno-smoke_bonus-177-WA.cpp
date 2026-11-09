#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main()
{
    int tc; cin>>tc;
    for(int testcase=0;testcase<tc;testcase++){
        bool poss=true;
        int smk = 1, n, r, cd; //smk set to 1 because 1 has already been used in a skipped
        vector<int> reqs;
        cin>>n>>r;
        cd = r;
        for(int i=0;i<n;i++){
            int a; cin>>a;
            reqs.push_back(a);
        }
        //calculate using delta of time
        for(int i=1;i<n;i++){
            int dt = reqs[i]-reqs[i-1]; // delta of time is calculated
            smk--;
            
            if(dt>=cd){
                dt-=cd;
                smk++;
                cd = r;
            }
            smk += dt/cd;
            dt -= (dt/cd) *cd;
            cd -= dt;
            
            if(smk>2){
                smk = 2;
            }
            if(smk<0){
                poss = false;
                break;
            }
        }
        if(poss){
            cout<<"YES";
        }
        else{
            cout<<"NO";
        }
        cout<<"\n";
    }
}