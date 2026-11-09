#include <bits/stdc++.h>

using namespace std;

/**
 * Return an array of Q strings, the i-th of which is "YES"
 * if Big Ben can travel from start[i] to end[i] within K[i]
 * seconds, and "NO" otherwise.
 *
 * N: the number of rows in the grid
 * M: the number of columns in the grid
 * Q: the number of queries
 * G: the grid, where each tile is 'R', 'B', or '.'
 * start: the (row, column) of the starting tile of each query
 * end: the (row, column) of the ending tile of each query
 * K: the maximum number of seconds allowed for each query
 */
vector<string> solve(int N, int M, int Q, vector<string>& G, vector<pair<int, int>>& start, vector<pair<int, int>>& end, vector<int>& K) {
    int junk=5;
    int cn=0;
    int qq=1000000000;
    vector<int> x1(Q),y1(Q),x2(Q),y2(Q);
    for(int ii=0;ii<Q;ii++){
        x1[ii]=start[ii].first;
        y1[ii]=start[ii].second;
        x2[ii]=end[ii].first;
        y2[ii]=end[ii].second;
    }
    vector<vector<int> > v1(N,vector<int>(M,-1));
    vector<vector<int> > v2(N,vector<int>(M,-1));
    vector<int> w(M+2,0);
    int tmp=0;
    int j=0;
    while(j<M){
        w[j]=tmp;
        for(int o=0;o<N;o++){
            char hh=G[o][j];
            if(hh=='.'){
                v1[o][j]=tmp;
                tmp++;
                v2[o][j]=tmp;
                tmp=tmp+1;
            }else{
                if(hh=='B'){
                    v1[o][j]=tmp;
                    tmp++;
                }else{
                    if(hh=='R'){
                        v2[o][j]=tmp;
                        tmp++;
                    }
                }
            }
        }
        j++;
    }
    w[M]=tmp;
    w[M+1]=tmp;
    vector<array<int,5> > dat(tmp);
    vector<int> nn(tmp,0);
    for(int o=0;o<N;o++){
        for(int j=0;j<M;j++){
            if(v1[o][j]!=-1){
                int m=v1[o][j];
                if(o>0){
                    if(v1[o-1][j]!=-1){
                        dat[m][nn[m]]=v1[o-1][j];
                        nn[m]++;
                    }
                }
                if(o<N-1){
                    if(v1[o+1][j]!=-1){
                        dat[m][nn[m]]=v1[o+1][j];
                        nn[m]++;
                    }
                }
                if(j>0){
                    if(v1[o][j-1]!=-1){
                        dat[m][nn[m]]=v1[o][j-1];
                        nn[m]++;
                    }
                }
                if(j<M-1){
                    if(v1[o][j+1]!=-1){
                        dat[m][nn[m]]=v1[o][j+1];
                        nn[m]++;
                    }
                }
            }
            if(v2[o][j]!=-1){
                int mm=v2[o][j];
                if(o>0){
                    if(v2[o-1][j]!=-1){
                        dat[mm][nn[mm]]=v2[o-1][j];
                        nn[mm]++;
                    }
                }
                if(o<N-1){
                    if(v2[o+1][j]!=-1){
                        dat[mm][nn[mm]]=v2[o+1][j];
                        nn[mm]++;
                    }
                }
                if(j>0){
                    if(v2[o][j-1]!=-1){
                        dat[mm][nn[mm]]=v2[o][j-1];
                        nn[mm]++;
                    }
                }
                if(j<M-1){
                    if(v2[o][j+1]!=-1){
                        dat[mm][nn[mm]]=v2[o][j+1];
                        nn[mm]++;
                    }
                }
            }
            if(G[o][j]=='.'){
                int p1=v1[o][j];
                int p2=v2[o][j];
                dat[p1][nn[p1]]=p2;
                nn[p1]++;
                dat[p2][nn[p2]]=p1;
                nn[p2]++;
            }
        }
    }
    vector<int> yy(Q,0);
    vector<int> s1(Q,0),s2(Q,0),s3(Q,0);
    vector<int> ok;
    int u=0;
    while(u<Q){
        bool f=false;
        if(x1[u]==x2[u]){
            if(y1[u]==y2[u]){
                yy[u]=1;
                f=true;
            }
        }
        if(f==false){
            int i1=x1[u]-x2[u];
            if(i1<0){
                i1=i1*-1;
            }
            int i2=y1[u]-y2[u];
            if(i2<0){
                i2=i2*-1;
            }
            if((long long)(i1+i2)>K[u]){
                f=true;
            }
        }
        if(f==false){
            if(v1[x1[u]][y1[u]]==-1){
                f=true;
            }
        }
        if(f==false){
            s1[u]=v1[x1[u]][y1[u]];
            int pp=v1[x2[u]][y2[u]];
            int ww=v2[x2[u]][y2[u]];
            if(pp==-1){
                pp=ww;
            }
            if(ww==-1){
                ww=pp;
            }
            s2[u]=pp;
            s3[u]=ww;
            ok.push_back(u);
        }
        u++;
    }
    vector<int> dd(tmp+1,qq);
    vector<int> zq(tmp+1,0);
    vector<int> L1;
    vector<int> L2;
    vector<vector<int> > L3;
    L1.push_back(0);
    L2.push_back(M-1);
    L3.push_back(ok);
    while(L1.size()>0){
        int lll=L1.back();
        int rrr=L2.back();
        vector<int> qw=L3.back();
        L1.pop_back();
        L2.pop_back();
        L3.pop_back();
        if(qw.size()==0){
            continue;
        }
        int md=(lll+rrr)/2;
        vector<int> ee,ll1,rr1;
        for(int ii=0;ii<(int)qw.size();ii++){
            int uu=qw[ii];
            int h1=y1[uu]-md;
            if(h1<0){
                h1=-h1;
            }
            int h2=y2[uu]-md;
            if(h2<0){
                h2=-h2;
            }
            int h3=x1[uu]-x2[uu];
            if(h3<0){
                h3=-h3;
            }
            int lbb=h1+h2+h3;
            if(lbb<=K[uu]){
                ee.push_back(uu);
            }else{
                if(y1[uu]<md){
                    if(y2[uu]<md){
                        ll1.push_back(uu);
                    }
                }
                if(y1[uu]>md){
                    if(y2[uu]>md){
                        rr1.push_back(uu);
                    }
                }
            }
        }
        int nnn=ee.size();
        if(nnn>0){
            int o1=w[lll];
            int o2=w[rrr+1];
            int o3=o1;
            if(lll>0){
                o3=w[lll-1];
            }
            int o4=o2;
            if(rrr+1<M){
                o4=w[rrr+2];
            }
            int limm=0;
            for(int ii=0;ii<nnn;ii++){
                if(K[ee[ii]]>limm){
                    limm=K[ee[ii]];
                }
            }
            vector<long long> bst(nnn,(long long)4e18);
            int sss=w[md];
            while(sss<w[md+1]){
                for(int ii=o3;ii<o1;ii++){
                    dd[ii]=-1;
                }
                for(int ii=o1;ii<o2;ii++){
                    dd[ii]=qq;
                }
                for(int ii=o2;ii<o4;ii++){
                    dd[ii]=-1;
                }
                int hd=0;
                int tl=0;
                dd[sss]=0;
                zq[tl]=sss;
                tl++;
                while(hd<tl){
                    int cc=zq[hd];
                    hd++;
                    if(dd[cc]>=limm){
                        break;
                    }
                    cn++;
                    for(int kkk=0;kkk<nn[cc];kkk++){
                        int nbb=dat[cc][kkk];
                        if(dd[nbb]==qq){
                            dd[nbb]=dd[cc]+1;
                            zq[tl]=nbb;
                            tl++;
                        }
                    }
                }
                for(int ii=0;ii<nnn;ii++){
                    int uu=ee[ii];
                    int aq=dd[s1[uu]];
                    if(aq<qq){
                        int bz=dd[s2[uu]];
                        int bz2=dd[s3[uu]];
                        int bq2=bz;
                        if(bz2<bq2){
                            bq2=bz2;
                        }
                        if(bq2<qq){
                            long long tt2=(long long)aq+bq2;
                            if(tt2<bst[ii]){
                                bst[ii]=tt2;
                            }
                        }
                    }
                }
                sss++;
            }
            int ii=0;
            while(ii<nnn){
                int uu=ee[ii];
                if(bst[ii]<=K[uu]){
                    yy[uu]=1;
                }else{
                    if(y1[uu]<md){
                        if(y2[uu]<md){
                            ll1.push_back(uu);
                        }
                    }
                    if(y1[uu]>md){
                        if(y2[uu]>md){
                            rr1.push_back(uu);
                        }
                    }
                }
                ii++;
            }
        }
        if(lll<md){
            L1.push_back(lll);
            L2.push_back(md-1);
            L3.push_back(ll1);
        }
        if(md<rrr){
            L1.push_back(md+1);
            L2.push_back(rrr);
            L3.push_back(rr1);
        }
    }
    vector<string> res;
    for(int ii=0;ii<Q;ii++){
        if(yy[ii]==1){
            res.push_back("YES");
        }else{
            res.push_back("NO");
        }
    }
    return res;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int N, M, Q;
        cin >> N >> M >> Q;
        vector<string> G(N);
        for (int j = 0; j < N; j++) {
            cin >> G[j];
        }
        vector<pair<int, int>> start, end;
        vector<int> K;
        for (int j = 0; j < Q; j++) {
            int start_row, start_col, end_row, end_col, k;
            cin >> start_row >> start_col >> end_row >> end_col >> k;
            start.push_back({start_row, start_col});
            end.push_back({end_row, end_col});
            K.push_back(k);
        }

        for (string s : solve(N, M, Q, G, start, end, K)) {
            cout << s << '\n';
        }
    }
}