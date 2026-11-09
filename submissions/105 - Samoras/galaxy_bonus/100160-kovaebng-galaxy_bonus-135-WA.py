import sys

def solve():
    data=sys.stdin.buffer.read().split()
    it=iter(data)
    tests=int(next(it))
    answers=[]
    dot=46
    blue=66
    red=82

    for test in range(tests):
        n=int(next(it))
        m=int(next(it))
        q=int(next(it))
        grid=[next(it) for i in range(n)]

        total=n*m*2
        parent=list(range(total))
        size=[1]*total

        def find(x):
            while x!=parent[x]:
                parent[x]=parent[parent[x]]
                x=parent[x]
            return x

        def union(a,b):
            a=find(a)
            b=find(b)
            if a==b:
                return
            if size[a]<size[b]:
                a,b=b,a
            parent[b]=a
            size[a]+=size[b]

        def state(r,c,mode):
            return ((r*m+c)*2)+mode

        for r in range(n):
            row=grid[r]
            for c in range(m):
                ch=row[c]
                current=state(r,c,0)

                if ch==dot:
                    union(current,current+1)

                if ch==dot or ch==blue:
                    if c+1<m:
                        next_ch=row[c+1]
                        if next_ch==dot or next_ch==blue:
                            union(current,state(r,c+1,0))
                    if r+1<n:
                        next_ch=grid[r+1][c]
                        if next_ch==dot or next_ch==blue:
                            union(current,state(r+1,c,0))

                if ch==dot or ch==red:
                    current+=1
                    if c+1<m:
                        next_ch=row[c+1]
                        if next_ch==dot or next_ch==red:
                            union(current,state(r,c+1,1))
                    if r+1<n:
                        next_ch=grid[r+1][c]
                        if next_ch==dot or next_ch==red:
                            union(current,state(r+1,c,1))

        for query in range(q):
            rs=int(next(it))
            cs=int(next(it))
            rt=int(next(it))
            ct=int(next(it))

            start=state(rs,cs,0)
            destination=1 if grid[rt][ct]==bytes([red]) else 0
            end=state(rt,ct,destination)

            if find(start)==find(end):
                answers.append("YES")
            else:
                answers.append("NO")

    sys.stdout.write("\n".join(answers))

if __name__=="__main__":
    solve()
