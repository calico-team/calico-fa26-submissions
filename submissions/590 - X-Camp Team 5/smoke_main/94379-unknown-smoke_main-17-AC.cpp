#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * Output whether all of the requests can be fulfilled.
 *
 * N: Number of smoke requests
 * R: Number of seconds needed for a smoke charge to recharge
 * A: List of timestamps where smokes are requested
 */
string solve(int N, int R, vector<int> A)
{
	sort(A.begin(), A.end());
	int num = 2 * R;
	int lastProcess = 0;
	for (int i = 0; i < N; i++)
	{
		int theTime = A[i];
		num = min(2 * R, num + (theTime - lastProcess));
		lastProcess = theTime;
		if (num >= R)
		{
			num -= R;
		}
		else
		{
			return "NO";
		}
	}
	return "YES";
}

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int N, R;
		cin >> N >> R;
		vector<int> A(N);
		for (int i = 0; i < N; i++)
		{
			cin >> A[i];
		}

		cout << solve(N, R, A) << "\n";
	}
}
