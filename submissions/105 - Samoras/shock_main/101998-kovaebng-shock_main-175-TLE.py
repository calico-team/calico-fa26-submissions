import sys
from math import isqrt

def main():
    data=sys.stdin.buffer.read().split()
    if not data:
        return
    it=iter(data)
    tests=int(next(it))
    maxp=500
    info=[]

    for p in range(maxp+1):
        length=2*p+1
        dc_list=[0]*length
        dr_list=[0]*length
        p2=p*p
        for dr in range(-p,p+1):
            dr2=dr*dr
            dc_list[dr+p]=isqrt(p2-dr2)
            dr_list[dr+p]=dr2
        info.append((dc_list,dr_list,p2))

    results=[]

    for test in range(tests):
        n=int(next(it))
        m=int(next(it))
        q=int(next(it))
        quakes=[]
        largest=0

        for i in range(q):
            r=int(next(it))
            c=int(next(it))
            p=int(next(it))
            quakes.append((r,c,p))
            largest=max(largest,p)

        for p in range(maxp+1,largest+1):
            length=2*p+1
            dc_list=[0]*length
            dr_list=[0]*length
            p2=p*p
            for dr in range(-p,p+1):
                dr2=dr*dr
                dc_list[dr+p]=isqrt(p2-dr2)
                dr_list[dr+p]=dr2
            info.append((dc_list,dr_list,p2))

        ans=[0]*(n*m)
        width=m+1
        nxt=list(range(n*width))
        remaining=[m]*n
        row_next=list(range(n+1))

        for i in range(q-1,-1,-1):
            center_r,center_c,p=quakes[i]
            dc_list,dr_list,p2=info[p]
            first=center_r-p
            last=center_r+p

            r=first
            while row_next[r]!=r:
                row_next[r]=row_next[row_next[r]]
                r=row_next[r]

            while r<=last:
                offset=r-center_r+p
                dc=dc_list[offset]
                dr2=dr_list[offset]
                left=center_c-dc
                right=center_c+dc
                base=r*width
                idx=base+left

                while nxt[idx]!=idx:
                    nxt[idx]=nxt[nxt[idx]]
                    idx=nxt[idx]

                if idx<=base+right:
                    value=p2+1-dr2
                    row_start=r*m
                    count=0

                    while idx<=base+right:
                        c=idx-base
                        diff=c-center_c
                        ans[row_start+c]=value-diff*diff
                        nxt[idx]=idx+1
                        count+=1
                        idx+=1

                        while nxt[idx]!=idx:
                            nxt[idx]=nxt[nxt[idx]]
                            idx=nxt[idx]

                    remaining[r]-=count

                next_row=r+1
                while row_next[next_row]!=next_row:
                    row_next[next_row]=row_next[row_next[next_row]]
                    next_row=row_next[next_row]

                if remaining[r]==0:
                    row_next[r]=next_row
                r=next_row

        lines=[]
        for r in range(n):
            start=r*m
            lines.append(" ".join(map(str,ans[start:start+m])))
        results.append("\n".join(lines))

    sys.stdout.write("\n".join(results))

if __name__=="__main__":
    main()
