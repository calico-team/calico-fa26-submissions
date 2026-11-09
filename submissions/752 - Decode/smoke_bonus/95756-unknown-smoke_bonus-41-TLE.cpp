#include <bits/stdc++.h>
using namespace std;

void testcase()
{
	int N, R;
	cin >> N >> R;

	bool ok = true;

	int ch = 2;
	int rechargeby = INT_MAX;

	int cur = -1;

	for(int i = 0; i < N; i++)
	{
		int Ai;
		cin >> Ai;

		while(rechargeby <= Ai)
		{
			ch++;
			rechargeby += R;
		}

		if(ch >= 2)
		{
			ch = 2;
			rechargeby = INT_MAX;
		}

		cur = Ai;

		if(ch > 0)
		{
			if(ch == 2)
				rechargeby = Ai + R;
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
