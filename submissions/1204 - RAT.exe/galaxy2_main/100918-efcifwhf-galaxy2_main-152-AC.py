import sys

def main():
    data=sys.stdin.buffer.read().split()
    p=0
    T=int(data[p]);p+=1
    out=[]
    INF=10**18
    for _ in range(T):
        N=int(data[p]);M=int(data[p+1]); Q=int(data[p+2]);p+=3
        G=[data[p+i].decode() for i in range(N)]; p+=N
        W2=2*N
        total=M*W2

        def active(r,c,m):
            ch=G[r][c]
            return ch=='.' or (ch=='B' and m==0) or (ch=='R' and m==1)

        adj=[() for _ in range(total)]
        for c in range(M):
            for r in range(N):
                for m in range(2):
                    if not active(r,c,m):
                        continue
                    u=(c*N+r)*2+m
                    nb=[]
                    if G[r][c]=='.':
                        nb.append(u^1)
                    if r>0 and active(r-1,c,m):
                        nb.append(u-2)
                    if r<N-1 and active(r+1,c,m):
                        nb.append(u+2)
                    if c>0 and active(r,c-1,m):
                        nb.append(u-W2)
                    if c<M -1 and active(r,c+1,m):
                        nb.append(u+W2)
                    adj[u]=tuple(nb)


        qs_,qd0,qd1,qK,qcs,qce=[],[],[],[],[],[]
        for i in range(Q):
            rs=int(data[p]); cs=int(data[p+1])
            re=int(data[p+2]); ce=int(data[p+3]); K=int(data[p+4]); p+=5
            qs_.append((cs*N+rs)*2)
            qd0.append((ce*N+re)*2 if active(re,ce,0)else-1)
            qd1.append((ce*N+re)*2+1 if active(re,ce,1)else-1)
            qK.append(K);qcs.append(cs);qce.append(ce)
        best=[INF]*Q

        def solve(lo,hi,qs):
            if lo>hi or not qs:
                return
            mid=(lo+hi)//2
            ulo=lo*W2
            uhi=(hi+1)*W2
            S=uhi-ulo
            dists=[]
            for r in range(N):
                for m in range(2):
                    if not active(r,mid,m):
                        continue
                    src=(mid*N+r)*2+m
                    d=[-1]*S
                    d[src-ulo]=0
                    frontier=[src]
                    step=0
                    while frontier:
                        step+=1
                        nxt=[]
                        for u in frontier:
                            for v in adj[u]:
                                if ulo <=v<uhi and d[v-ulo]<0:
                                    d[v-ulo]=step
                                    nxt.append(v)
                        frontier=nxt
                    dists.append(d)
            L=[];R=[]
            for qi in qs:
                s=qs_[qi]-ulo
                t0=qd0[qi]; t1=qd1[qi]
                b=best[qi]
                for d in dists:
                    ds=d[s]
                    if ds<0:
                        continue
                    if t0>=0:
                        dt=d[t0-ulo]
                        if dt>=0 and ds+dt<b:
                            b=ds+dt
                    if t1>=0:
                        dt=d[t1-ulo]
                        if dt>=0 and ds+dt<b:
                            b=ds+dt
                best[qi]=b
                if qcs[qi]<mid and qce[qi]<mid:
                    L.append(qi)
                elif qcs[qi]>mid and qce[qi]>mid:
                     R.append(qi)
            solve(lo,mid-1,L)
            solve(mid+1,hi,R)

        solve(0,M-1,list(range(Q)))
        for i in range(Q):
            out.append("YES" if best[i]<= qK[i] else "NO")
    print("\n".join(out))
main()
                            
                        

        
