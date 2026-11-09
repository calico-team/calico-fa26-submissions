#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() 
{ 
    int s;
    cin >> s;

    while (s--){
       int n, k;
       cin >> n >> k;
    vector<char> a(k);
    for (int i = 0; i < k; i++)
    {
        cin >> a[i];
    }
    string ans(n, '?');
    for (int j = 0; j < k; j++)
    {
        string guess = ans;
        for (int i = 0; i < n; i++)
        {
            if(ans[i] == '?')
            {
               guess[i] = a[j];
            }
        }
        cout << guess << endl;
        string response;
        cin >> response;
        if(response == "CORRECT")
        {
            break;
        }
        
            for (int i = 0; i < n; i++)
            {
                if(response[i] != '_')
                {
                    ans[i] = response[i];
                }
            } 
    }
    }
    return 0;
}