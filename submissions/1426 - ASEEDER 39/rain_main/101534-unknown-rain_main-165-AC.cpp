#include<bits/stdc++.h>
using namespace std;
int T;
int main(){
    scanf("%d", &T);
    while(T--){
        long long n,k;
        scanf("%lld%lld",&n,&k);
        vector<int> heng(n),zong(n); 
        vector<char> fangxiang(n); 
        
        for(int i=0;i<n;i++){
            int z;
            scanf("%d%d%d %c", &heng[i],&zong[i],&z,&fangxiang[i]);
        }
        set<pair<int,int>> chushi_weizhi;
        for(int i=0;i<n;i++){
            chushi_weizhi.insert(make_pair(heng[i], zong[i]));
        }
        long long buchongfu_shuliang = chushi_weizhi.size();
        map<int,vector<int>> xiangdong_points;
        for(int i=0;i<n;i++){
            if(fangxiang[i]=='E'){
                xiangdong_points[heng[i] + zong[i]].push_back(heng[i]);
            }
        }
        long long chonghe_shuliang=0;
        for(int j=0;j<n;j++){
            if(fangxiang[j]=='N'){
                int mubiao_he=heng[j]+zong[j];
                if(xiangdong_points.find(mubiao_he) != xiangdong_points.end()){
                    vector<int>& dong_heng_list = xiangdong_points[mubiao_he]; 
                    for(int i = 0; i < dong_heng_list.size(); i++){
                        int dong_heng = dong_heng_list[i]; 
                        long long xiangyu_shike = heng[j] - dong_heng; 
        
                        if(xiangyu_shike>=0&&xiangyu_shike<k){
                            chonghe_shuliang++;
                        }
                    }
                }
            }
        }
        printf("%lld\n", buchongfu_shuliang * k - chonghe_shuliang);
    }
    return 0;
}