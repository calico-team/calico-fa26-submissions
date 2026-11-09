// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

struct Drone {
    int x;
    int y;
    int z;

    bool operator<(const Drone& other) const {
        return x + y < other.x + other.y;
    }
};

int bs(vector<Drone> arr, int target) {
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2; 

        if (arr[mid].x + arr[mid].y == target) {
            return mid;
        }
        
        if (arr[mid].x + arr[mid].y < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

int main() {
	int t;
    cin >> t;
    while (t--){
        int n;
        int k;
        cin >> n;
        cin >> k;
        vector<Drone> dn;
        vector<Drone> de;
        for (int i = 0; i < n; i++){
            int x;
            cin >> x;
            int y;
            cin >> y;
            int z;
            cin >> z;
            char d;
            cin >> d;
            if (d == 'N'){
                dn.push_back({x, y, z});
            }
            else {
                de.push_back({x, y, z});
            }
        }
        sort(de.begin(), de.end());
        long long out = n * k;
        for (Drone d : dn){
            int l = bs(de, d.x + d.y);
            if (l != -1){
                if (d.x - de[l].x < k && d.x - de[l].x > 0){
                    out--;
                }
                for (int i = l - 1; i > -1; i--){
                    if (de[i].x + de[i].y == d.x + d.y){
                        if (d.x - de[i].x < k && d.x - de[i].x > 0){
                            out--;
                        }
                    }
                    else {
                        break;
                    }
                }
                for (int i = l + 1; i < (int)de.size(); i++){
                    if (de[i].x + de[i].y == d.x + d.y){
                        if (d.x - de[i].x < k && d.x - de[i].x > 0){
                            out--;
                        }
                    }
                    else {
                        break;
                    }
                }
            }
        }
        cout << out << endl;
    }
}
