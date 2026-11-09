#include<bits/stdc++.h>
using namespace std;

char App[30]={};
char Stro[110]={};
int main()
{

    int t;
    cin>>t;
    for(int i=0;i<t;i++)
    {

        

        int n,k;
        cin>>n>>k;

        for(int j=0;j<k;j++)
        {
            cin>>App[j];
        }


        for(int j=0;j<k;j++)
        {
            char Search=App[j];
            string str="";
            for(int l=0;l<n;l++)
            {
                str+=Search;
            }

            cout<<str<<endl;

            string data;
            cin>>data;

            for(int p=0;p<data.length();p++)
            {
                if(data[p]==Search)
                {
                    Stro[p]=Search;
                }
            }
        }

        for(int j=0;j<n;j++)
        {
            cout<<Stro[i];
        }
        cout<<endl;
        
        string resp="";
        cin>>resp;
        if(resp!="CORRECT")
        {
            exit(0);
        }
    }
    return 0;

}