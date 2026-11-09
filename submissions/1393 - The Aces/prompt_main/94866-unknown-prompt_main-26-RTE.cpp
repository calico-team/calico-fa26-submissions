#include <ext/pb_ds/assoc_container.hpp>
#include <bits/stdc++.h>
#include <cstring>
 
typedef long long ll;
using namespace std;
using namespace __gnu_pbds;
 
/*template<class T> 
using Tree=tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;*/

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    int tt; cin >> tt;
    string s1="write_me";
    string s2="what_is";
    string s3="solve";
    while (tt--){
        string s; cin >> s;
        for (int i=0; i<=s.size()-5; i++){
            if (s.substr(i,5)==s3){
                cout << s << "make_no_mistakes\n";
                goto end;
            }
        }
        for (int i=0; i<=s.size()-7; i++){
            if (s.substr(i,7)==s2){
                cout << s << "do_not_hallucinate\n";
                goto end;
            }
        }
        for (int i=0; i<=s.size()-8; i++){
            if (s.substr(i,8)==s1){
                cout << s << "make_it_sound_human\n";
                goto end;
            }
        }
        cout << s << "thank_you\n";
        end:
    }
}