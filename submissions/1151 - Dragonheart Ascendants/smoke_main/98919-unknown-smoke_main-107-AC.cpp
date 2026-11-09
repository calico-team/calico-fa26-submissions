#include <iostream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

int main() 
{ 
    int s;
    cin >> s;

    while (s--){
       int n, r;
       cin >> n >> r;
    
       vector<long long> a(n);
       for (int i = 0; i < n; i++)
       {
        cin >> a[i];
       }

       int smoke = 2;
       queue<long long> q;
       bool possible = true;
       for (int i = 0; i < n; i++)
       {
        while (!q.empty() && q.front() <= a[i])
        {
            smoke++;
            q.pop();
        }
        if (smoke == 0)
        {
            possible = false;
            break;
        }
        smoke--;
        long long time = a[i];
        if(!q.empty())
        {
            time = q.back();
        }
        q.push(time + r);
       }
    if (possible)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
}
    return 0;
}