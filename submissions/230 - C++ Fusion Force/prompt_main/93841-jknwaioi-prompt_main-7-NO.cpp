#include <bits/stdc++.h>
using namespace std;
int main()
{
    //center is i+(i+(n-1))/2, j+(j+(n-1))/2 
    //i+a or j+a, or i+(n-1)-a or j+(n-1)-a gives a points
    int n, q;
    int x0, y0;
    cin >> n >> q >> x0 >> y0;
    
        vector<vector<pair<int, int>>> coords;
        vector<pair<int, int>> temppair;
        vector<vector<int>> points(n, vector<int>(n));
        int countx, county;
        for(int i=0; i<n; i++)
        {
            county=y0+(n-1)-i;
            for(int j=0; j<n; j++)
            {
                countx=x0+j;
                temppair.push_back({countx, county});
            }
            coords.push_back(temppair);
            temppair.clear();
        }
       
        //int centeri=i+(i+(n-1))/2, centerj=j+(j+(n-1))/2;
        for(int a=0; a<n/2+1; a++)
        {
            for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(points[i][j]==0 && (coords[i][j].first==x0+a || coords[i][j].second==y0+a || coords[i][j].first==x0+n-1-a || coords[i][j].second==y0+n-1-a))
                points[i][j]=a+1;
                
            }
        }
        }
    
    while(q--)
    {
        
        int t;
        cin >> t;
        if(t==1)
        {
            int x, y;
            cin >> x >> y;
            bool flag=false;
            if(x<x0 || y<y0 || x>x0+(n-1) || y>y0+(n-1))
            cout << 0 << endl;
            else{
            for(int i=0; i<n; i++)
            {
                for(int j=0; j<n; j++)
                {
                    if(x==coords[i][j].first && y==coords[i][j].second)
                    {cout << points[i][j] << endl;
                    flag=true;
                    break;
                    }
                }
                if(flag)
                {
                    flag=false;
                    break;
                }
            }
        }}
        if(t==2){
            int p, tot=0;
            cin >> p;
          
            for(int i=0; i<n; i++)
            {
                for(int j=0; j<n; j++)
                {
                    if(points[i][j]==p)
                    {tot+=coords[i][j].first + coords[i][j].second;
                    }
                    
                }
            }
            cout << tot << endl;
        }
    }
   
    return 0;
}