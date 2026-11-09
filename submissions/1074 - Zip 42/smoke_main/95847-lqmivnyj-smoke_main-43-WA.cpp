//
// Created by User on 11/8/2026.
//
#include "bits/stdc++.h"
using namespace std;

int main() {
    int tests;
    cin>>tests;
    while (tests>0) {
        tests--;

        int req, rec;
        cin>>req>>rec;
        vector<int> v;
        vector<int> r;
        for (int i=0; i<req; i++) {
            int n;
            cin>>n;
            v.push_back(n);
        }
        //recharges
        int smokes=0;
        bool reload=false;
        r.push_back(rec);reload=true;

        int p=0;
        for (int i=0; i<req; i++) {
            while (p<r.size() && v[i]>=r[p]) {
                smokes=min(2,smokes+1);
                reload=false;
                if (smokes<2) {
                    r.push_back(rec+r[p]);//reload
                    reload=true;
                }
                p++;//gain a smoke
                //reload now

            }
            if (smokes<=0) {
                cout<<"NO"<<"\n";
                goto stuff;
            }else {
                smokes--;

                if (!reload) {
                    r.push_back(rec+v[i]);//reload
                    reload=true;
                }
            }
        }
        cout<<"YES"<<"\n";
        stuff:int abc=0;
    }
}