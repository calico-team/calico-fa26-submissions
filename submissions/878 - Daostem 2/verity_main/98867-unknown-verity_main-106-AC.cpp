#include <bits/stdc++.h>
using namespace std;
void vecout(vector<char> guess)
{
	for(int p=0; p<guess.size(); p++)
	{
		cout<<guess[p];
	}

	cout<<endl;

}


int main() {

	int t;
	cin>>t;


	while(t--)
	{
		int l, n; //length of each wordle guess, number of posible characters
		cin>>l>>n;
		vector<char> ities(n); //poss characters
		vector<char> guess(l); //current guess?
		vector<char> complete(l,'0'); //confirmed items

		for(int i=0; i<n; i++)
		{
			char idk;
			cin>>idk;
			ities[i]=idk;
		} //set up all the possibel characters!!!

		for(int i=0; i<l; i++)
		{
			guess[i]=ities[i%n];
		}

		//vecout(guess);

		string feedback;
		int step=0;
		while(feedback!="CORRECT")
		{

			for(int i=0; i<complete.size(); i++)
			{
				complete[i]=guess[i];
			}
			for(int i=0; i<feedback.size(); i++)
			{
				if(feedback[i]!='_')
				{
					complete[i]=feedback[i];
				}
			}
			vecout(complete);

			//update the next guess usuing ities letters!!!
			
			step++;

			for (int i=0; i<l; i++) {
				guess[i]=ities[(i+step)%n];
			}

			cin>>feedback;

		}

	}

	return 0;
}