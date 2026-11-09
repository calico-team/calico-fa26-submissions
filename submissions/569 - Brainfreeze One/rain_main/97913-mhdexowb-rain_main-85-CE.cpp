#include <bits/stdc++.h>
using namespace std;

vector<int> ans;

struct hashFunction 
{
  size_t operator()(const vector<int> 
                    &myVector) const 
  {
    std::hash<int> hasher;
    size_t answer = 0;
    
    for (int i : myVector) 
    {
      answer ^= hasher(i) + 0x9e3779b9 + 
                (answer << 6) + (answer >> 2);
    }
    return answer;
  }
};

void printVector(vector<int> myVector)
{
  cout << "[ ";
  for(auto element : myVector)
    cout << element << ' ';
  cout << "]\n";
}

void print(unordered_set<vector<int>, 
           hashFunction> &unorderedsetOfVectors)
{
  for (auto it = unorderedsetOfVectors.begin();
       it != unorderedsetOfVectors.end();
       it++) 
  {
    // Each element is a vector
    printVector(*it);
  }
}

 
 
void solve(){
    int n, k; // n = drones, k = nights
    cin >> n >> k;
    
    vector<vector<int>> drones_cords;
    vector<int> drones_height;
    vector<string> drones_direction;
    
    for (int i=0; i<n; i++) {
        int x, y, z;
        string d;
        cin >> x >> y >> z >> d;
        vector<int> cords;
        cords.push_back(x);
        cords.push_back(y);
        
        drones_cords.push_back(cords);
        drones_height.push_back(z);
        drones_direction.push_back(d);
    }
    
    int cur = 0;
    
    for (int i=0; i<k; i++) {
        unordered_set<vector<int>, hashFunction> seen;
        
        for (vector<int> cord : drones_cords) {
            if (!(seen.contains(cord))) {
                seen.insert(cord);
            }
        }
        
        cur += seen.size();
        
        for (int i=0; i < drones_cords.size(); i++) {
            if (drones_direction[i] == "E") {
                drones_cords[i][0]++;
            } else {
                drones_cords[i][1]++;
            }
        }
    }
    ans.push_back(cur);
}
 
int main()
{
    int t;
    cin >> t;
    while (t--){
        solve();
    }
    for (int a: ans) {
        cout << a << "\n";
    }
    return 0;
}