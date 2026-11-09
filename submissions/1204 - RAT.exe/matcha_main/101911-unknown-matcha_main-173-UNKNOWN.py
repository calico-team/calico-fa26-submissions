import sys

def main():
    data=sys.stdin.buffer.read().split()
    p=0
    T=int(data[p]); p += 1
    out=[]
    for _ in range(T):
        n=int(data[p]); p += 1
        L=data[p:p+n]; p += n
        R=data[p:p+n]; p += n
        Cfix=0
        groups=[[] for _ in range(30)]
        Li=[0]*n; Ri=[0]*n
        for i in range(n):
            l=int(L[i]); r=int(R[i])
            Li[i]=l;Ri[i]=r
            x=l^r
            if x==0:
                Cfix^=l
            else:
                b=x.bit_length()-1
                Cfix^=(l >>(b + 1))<<(b + 1)
                groups[b].append(i)

        C=Cfix
        cnt=[0]*30
        ans=0

        def addbits(s, delta):
            while s:
                lb=s & -s
                cnt[lb.bit_length()-1]+=delta
                s^=lb

        for k in range(29, -1, -1):
            grp=groups[k]
            t=len(grp)
            ck=(C >> k) & 1
            nk=cnt[k]
            if t==0:
                if nk==0:
                    ans|=ck<<k
                    continue
                if ck==1 or nk>=2:
                    ans|=(1<<(k+1))-1
                    break
                ans |= 1<<k
                continue
            if nk >= 1:
                ans |= (1<<(k+1))-1
                break
            g = 1^ck
            ans|=1<<k
            mask=(1<<k) - 1
            lowers=0
            cands=[]
            for i in grp:
                rp=Ri[i]&mask
                u=mask-(Li[i]&mask)
                if rp>=u:
                    mx, mn=rp, u
                    lowers+=1
                else:
                    mx, mn=u, rp
                addbits(mx,1)
                cands.append((mx,mn))
            uppers_parity=(t-g)&1
            Cn = C^mask if uppers_parity else C
            if (lowers&1)!=g:
                best_d=99
                for mx,mn in cands:
                    d=(mx^mn).bit_length()-1
                    if d<best_d:
                        best_d=d
                if best_d==-1:
                    chosen = (0, 0)
                else:
                    chosen=None
                    bk=None
                    seen=set()
                    for mx, mn in cands:
                        if (mx^mn).bit_length()-1==best_d and (mx,mn) not in seen:
                            seen.add((mx,mn))
                            key=0
                            for j in range(best_d-1,-1,-1):
                                key=key*3+((mn>>j)&1)-((mx>>j)&1)+1
                            if bk is None or key>bk:
                                bk=key; chosen=(mx,mn)
                addbits(chosen[0],-1)
                addbits(chosen[1],1)
            C=Cn
        out.append(ans)
    print("\n".join(map(str,out)))

main()
