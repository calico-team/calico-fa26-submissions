#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        long long int n,r;
        cin >> n >> r;
        vector<long long int> a(n);
        bool flag=false;
        for(long long int i=0; i<n; i++)
        {
            cin >> a[i];
        }
        
        long long int smoke1=0, smoke2=0;
        
        for(long long int i=0; i<n; i++)
        {
            if(smoke1<=a[i] && smoke2<=a[i])
            {
                smoke1=a[i]+r;
            }
            
            else if(smoke2<=a[i] && smoke1>a[i])
            {
                smoke2=a[i]+r+(smoke1-a[i]);
            }
            
            else if(smoke1<=a[i] && smoke2>a[i])
            {
            	smoke1=a[i]+r+(smoke2-a[i]);
            }
            else if(smoke1>a[i] && smoke2>a[i])
            {
                flag=true;
            }
            
            if(flag)
            break;
        }
        
        if(flag)
        cout << "NO" << endl;
        
        else cout << "YES" << endl;
    }

    return 0;
}