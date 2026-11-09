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
        long long int smoke1=0, smoke2=0;

        for(long long int i=0; i<n; i++)
        {
            cin >> a[i];
            
            if(!flag)
            {
            if(smoke1<=a[i] && smoke2<=a[i])
            {
                smoke1=a[i]+r;
            }
            
            else if(smoke2<=a[i] && smoke1>a[i])
            {
                smoke2=r+smoke1;
            }
            
            else if(smoke1<=a[i] && smoke2>a[i])
            {
            	smoke1=r+smoke2;
            }
            else flag=true;}
        }
      
        if(flag)
        cout << "NO" << endl;
        
        else cout << "YES" << endl;
    }

    return 0;
}