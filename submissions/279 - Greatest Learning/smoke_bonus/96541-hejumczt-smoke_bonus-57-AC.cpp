#include <bits/stdc++.h>
using namespace std;
#define int long long





int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);



int T; cin >> T;


while (T--){
	int N, R; cin >> N >> R;
	vector<int> A(N); for (int i = 0; i < N; i++) cin >> A[i];
	
	int first_charge_time = 0, second_charge_time = 0;
	
	bool ok = true;
	
	for (int i = 0; i < N; i++){
		if (i != 0){
			int difference_time = A[i] - A[i-1]; // calculate diff in time between two requesats
			
			if (first_charge_time != 0){
				if (first_charge_time < difference_time){
					difference_time -= first_charge_time;
					first_charge_time = 0;
					second_charge_time -= difference_time;
					if (second_charge_time < 0) second_charge_time = 0; // difference time enough to charge both
					
				}
				else{
					first_charge_time -= difference_time;
				}


			}
			else{ 
				second_charge_time -= difference_time;
				if (second_charge_time < 0) second_charge_time = 0;
			}
			
		//	cout << "Difference in time is: " << difference_time << '\n';

		}
		//cout << "New first charge: " << first_charge_time << " New second charge: " << second_charge_time << '\n';
		if (first_charge_time == 0 && second_charge_time == 0){
			first_charge_time = R;
		}
		else if (first_charge_time == 0){
			first_charge_time = second_charge_time; // swap them, so it is faster to recharge next recharge (lower cd for first)
			second_charge_time = R;
		}
		else if (second_charge_time == 0){
			second_charge_time = R;
			
		}
		else{
			ok = false;
			break;
		}
	
	
	}
	
	if (ok){
		cout << "YES\n";
	}
	else{
		cout << "NO\n";
	}




}






	return 0;
}
