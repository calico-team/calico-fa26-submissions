#include <iostream>
#include <vector>
#include <queue>
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
	queue<long long> q;
	bool isPossible = true;

	for (int i = 0; i < N; i++)
	{
		long long current_time = A[i];
		while (!q.empty() && q.front() <= current_time){
			q.pop();
		}

		int available_charges=2-q.size();
		if(available_charges<=0)
		{
			isPossible=false;
			break;
		}

		long long start_recharge=q.empty()?current_time:q.back();
		q.push(start_recharge+R);
	}
	if(isPossible)
	return "YES";
	else
	return "NO";
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
