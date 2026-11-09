#include <iostream>
using namespace std;

long long time[1000000010];

int main()
{
    int n1,n2,cd;
    int cur=1;
    cin>>n1;
    for (int i=1;i<=n1;i++) {
        cin>>n2>>cd;
        for (int j=1;j<=n2;j++) {
            cin>>time[j];
        }
        for (int j=1;j<=n2;j++) {
            if ((time[j]-time[i-1])<cd){
                cur=0;
            }
        }
        if (cur){
            cout<<"YES"<<endl;
        }
        else {
            cout<<"NO"<<endl;
        }
    }
}