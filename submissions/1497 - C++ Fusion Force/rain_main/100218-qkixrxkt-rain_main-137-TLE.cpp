/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <bits/stdc++.h>
using namespace std;
int countdiff(vector<int> xcoord, vector<int> ycoord){
    vector<int> diff;
    int countt=1;
    for(int i=0; i<xcoord.size(); i++){
        diff.push_back(15832*xcoord[i]+ycoord[i]);
    }
    sort(diff.begin(), diff.end());
    for(int i=1; i<diff.size(); i++){
        if(diff[i]!=diff[i-1]) countt++;
    }
    return countt;
}
int main()
{
    int n;
    cin>>n;
    for(int i=0; i<n; i++){
        int n, k;
        cin>>n>>k;
        vector<int> xcoord;
        vector<int> ycoord;
        string dir;
        for(int j=0; j<n; j++){
            int x, y, z;
            char d;
            cin>>x>>y>>z>>d;
            xcoord.push_back(x);
            ycoord.push_back(y);
            dir+=d;
        }
        int ans=0;
        for(int j=0; j<k; j++){
            int drops=countdiff(xcoord, ycoord);
            ans+=drops;
            for(int pos=0; pos<dir.size(); pos++){
                if(dir[pos]=='N') ycoord[pos]++;
                else xcoord[pos]++;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
