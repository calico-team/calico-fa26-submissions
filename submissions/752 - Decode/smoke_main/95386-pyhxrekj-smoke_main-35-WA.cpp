#include <bits/stdc++.h>
using namespace std;

void testcase()
{
	int N, R;
	cin >> N >> R;

	bool ok = true;

	int ch = 2;
	int toget1 = R;

	int cur = -1;

	for(int i = 0; i < N; i++)
	{
		int Ai;
		cin >> Ai;

		if(ch < 2 && cur != -1)
		{
			toget1 -= (Ai - cur);

			while(toget1 < 0)
			{
				ch++;
				toget1 += R;
			}

			if(ch >= 2)
			{
				ch = 2;
				toget1 = R;
			}
		}
		else
			toget1 = R;

		cur = Ai;

		if(ch > 0)
		{
			if(ch == 2)
				toget1 = R;
			ch--;
		}
		else
			ok = false;
	}

	if(ok) cout << "YES\n";
	else   cout << "NO\n";
}

int main()
{
	int T;
	cin >> T;
	while(T--)
		testcase();
	return 0;
}
