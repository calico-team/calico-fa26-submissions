#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct drouneing_force {
    long long porrr;
    long long yorrrr;
    long long heee_z;
    char testooo;
    int namumken_inde;
};

void apni_duniya() {
    int sara_kaam;
    if (!(cin >> sara_kaam)) return;
    
    while (sara_kaam--) {
        int kitne_drones;
        long long kitni_raatein;
        cin >> kitne_drones >> kitni_raatein;
        
        map<long long, vector<drouneing_force> > group_by_diagonal;
        
        for (int i = 0; i < kitne_drones; i++) {
            drouneing_force temp_drone;
            cin >> temp_drone.porrr >> temp_drone.yorrrr >> temp_drone.heee_z >> temp_drone.testooo;
            temp_drone.namumken_inde = i;
            
            long long diagonal_sum = temp_drone.porrr + temp_drone.yorrrr;
            group_by_diagonal[diagonal_sum].push_back(temp_drone);
        }
        
        long long total_paani = (long long)kitne_drones * kitni_raatein;
        
        for (map<long long, vector<drouneing_force> >::iterator it = group_by_diagonal.begin(); it != group_by_diagonal.end(); ++it) {
            vector<drouneing_force>& ek_group = it->second;
            
            vector<drouneing_force> east_drones;
            vector<drouneing_force> north_drones;
            
            for (size_t d_idx = 0; d_idx < ek_group.size(); d_idx++) {
                if (ek_group[d_idx].testooo == 'E') {
                    east_drones.push_back(ek_group[d_idx]);
                } else {
                    north_drones.push_back(ek_group[d_idx]);
                }
            }
            
            for (size_t e_idx = 0; e_idx < east_drones.size(); e_idx++) {
                for (size_t n_idx = 0; n_idx < north_drones.size(); n_idx++) {
                    if (north_drones[n_idx].porrr >= east_drones[e_idx].porrr) {
                        long long kis_raat_miley = north_drones[n_idx].porrr - east_drones[e_idx].porrr;
                        if (kis_raat_miley < kitni_raatein) {
                            if (east_drones[e_idx].heee_z < north_drones[n_idx].heee_z) {
                                total_paani--;
                            } else if (north_drones[n_idx].heee_z < east_drones[e_idx].heee_z) {
                                total_paani--;
                            }
                        }
                    }
                }
            }
        }
        
        cout << total_paani << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    apni_duniya();
    
    return 0;
}