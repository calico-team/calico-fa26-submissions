
import sys

def solve(N,M,Q,G,start,end):
    size=N*M*2
    parent=list(range(size))
    rank=[1]*size
    def find(x):
        while parent[x]!=x:
            parent[x]=parent[parent[x]]
            x=parent[x]
        return x
    def union(a,b):
        a=find(a)
        b=find(b)
        if a==b:
            return
        if rank[a]<rank[b]:
            a,b=b,a
        parent[b]=a
        rank[a]+=rank[b]

    for r in range(N):
        for c in range(M):
            ch=G[r][c]
            x=(r*M+c)*2

            if ch=='.':
                union(x,x+1)
            if ch!='R':
                if c+1<M and G[r][c+1]!='R':
                    union(x,x+2)
                if r+1<N and G[r+1][c]!='R':
                    union(x,x+2*M)

            if ch!='B':
                if c+1<M and G[r][c+1]!='B':
                    union(x+1,x+3)
                if r+1<N and G[r+1][c]!='B':
                    union(x+1,x+2*M+1)

    results=[]
    for (sr,sc),(er,ec) in zip(start,end):
        s=find((sr*M+sc)*2)
        t=(er*M+ec)*2
        ch=G[er][ec]

        if ch=='B':
            results.append("YES" if s==find(t) else "NO")
        elif ch=='R':
            results.append("YES" if s==find(t+1) else "NO")
        else:
            results.append("YES" if s==find(t) or s==find(t+1) else "NO")

    return results

def main():
    input=sys.stdin.buffer.readline
    T=int(input())
    for _ in range(T):
        N,M,Q=map(int,input().split())
        G=[input().strip() for _ in range(N)]
        start=[]
        end=[]
        for _ in range(Q):
            sr,sc,er,ec=map(int,input().split())
            start.append((sr,sc))
            end.append((er,ec))
        print('\n'.join(solve(N,M,Q,G,start,end)))

if __name__=='__main__':
    main()
