#include <iostream>
#include <vector>
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
	int c = 2;
	long long f = 0;
	for (int i = 0; i < N; i++)
	{
		long long time = A[i];
		while (c < 2 && f <= time)
		{
			c++;
			f += R;
		}
		if (c > 0)
		{
			if (c == 2) f = time + R;
			c--;
		}
		else return "NO";
	}
	return "YES";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int T; cin >> T;
	while (T--)
	{
		int N, R; cin >> N >> R;
		vector<int> A(N);
		for (int i = 0; i < N; i++) cin >> A[i];
		cout << solve(N, R, A) << "\n";
	}
	return 0;
}

