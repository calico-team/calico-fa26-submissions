import sys
from math import isqrt

def solve():
    data=sys.stdin.buffer.read().split()
    if not data:
        return

    it=iter(data)
    tests=int(next(it))
    output=[]

    info=[]
    for p in range(501):
        p2=p*p
        points=[]
        for dr in range(-p,p+1):
            dr2=dr*dr
            dc=isqrt(p2-dr2)
            points.append((dr,dc,dr2))
        info.append(points)

    for test in range(tests):
        n=int(next(it))
        m=int(next(it))
        q=int(next(it))
        quakes=[]
        max_p=0

        for i in range(q):
            r=int(next(it))
            c=int(next(it))
            p=int(next(it))
            quakes.append((r,c,p))
            max_p=max(max_p,p)

        if max_p>=len(info):
            for p in range(len(info),max_p+1):
                p2=p*p
                points=[]
                for dr in range(-p,p+1):
                    dr2=dr*dr
                    dc=isqrt(p2-dr2)
                    points.append((dr,dc,dr2))
                info.append(points)

        ans=[0]*(n*m)
        size=n*(m+1)
        nxt=list(range(size))
        row_size=m+1

        for i in range(q-1,-1,-1):
            r,c,p=quakes[i]
            p2=p*p
            center=p2+1

            for dr,dc,dr2 in info[p]:
                row=r+dr
                left=max(0,c-dc)
                right=min(m-1,c+dc)

                if left>right:
                    continue

                base=row*row_size
                idx=base+left

                while nxt[idx]!=idx:
                    nxt[idx]=nxt[nxt[idx]]
                    idx=nxt[idx]

                if idx-base>right:
                    continue

                value=center-dr2
                row_start=row*m

                while idx-base<=right:
                    col=idx-base
                    diff=col-c
                    ans[row_start+col]=value-diff*diff

                    next_idx=idx+1
                    while nxt[next_idx]!=next_idx:
                        nxt[next_idx]=nxt[nxt[next_idx]]
                        next_idx=nxt[next_idx]

                    nxt[idx]=next_idx
                    idx=next_idx

        for r in range(n):
            start=r*m
            output.append(' '.join(map(str,ans[start:start+m])))

    sys.stdout.write('\n'.join(output))


if __name__=='__main__':
    solve()
