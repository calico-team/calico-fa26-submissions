#include <iostream>
#include <vector>

using namespace std;

void murreee_function() {
    int sara_kaam;
    if (!(cin >> sara_kaam)) return;
    
    while (sara_kaam--) {
        int N;
        long long R;
        cin >> N >> R;
        
        vector<long long> requests(N);
        for (int i = 0; i < N; i++) {
            cin >> requests[i];
        }
        
        int abika_charges = 2;
        long long dobaracharge_wakht = -1;
        bool oswal = true;
        
        for (int i = 0; i < N; i++) {
            long long abhi_ka_waqt = requests[i];
            
            while (abika_charges < 2 && abhi_ka_waqt >= dobaracharge_wakht) {
                abika_charges++;
                if (abika_charges == 1) {
                    dobaracharge_wakht = dobaracharge_wakht + R;
                }
            }
            
            if (abika_charges > 0) {
                abika_charges--;
                if (abika_charges == 1) {
                    dobaracharge_wakht = abhi_ka_waqt + R;
                }
            } else {
                oswal = false;
                break;
            }
        }
        
        if (oswal) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    murreee_function();
    
    return 0;
}