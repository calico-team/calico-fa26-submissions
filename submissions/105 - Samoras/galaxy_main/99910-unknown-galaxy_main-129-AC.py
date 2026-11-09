import sys

def solve():
    data=sys.stdin.buffer.read().split()
    if not data:
        return
    it=iter(data)
    tests=int(next(it))
    answers=[]

    for test in range(tests):
        n=int(next(it))
        m=int(next(it))
        q=int(next(it))
        grid=[next(it).decode() for i in range(n)]

        size=2*n*m
        parent=list(range(size))

        def find(x):
            while parent[x]!=x:
                parent[x]=parent[parent[x]]
                x=parent[x]
            return x

        def union(a,b):
            a=find(a)
            b=find(b)
            if a!=b:
                parent[a]=b

        def index(r,c,mode):
            return 2*(r*m+c)+mode

        def active(ch,mode):
            return ch=="." or (ch=="B" and mode==0) or (ch=="R" and mode==1)

        for r in range(n):
            for c in range(m):
                if grid[r][c]==".":
                    union(index(r,c,0),index(r,c,1))

        for r in range(n):
            for c in range(m):
                for mode in range(2):
                    if not active(grid[r][c],mode):
                        continue

                    if c+1<m and active(grid[r][c+1],mode):
                        union(index(r,c,mode),index(r,c+1,mode))

                    if r+1<n and active(grid[r+1][c],mode):
                        union(index(r,c,mode),index(r+1,c,mode))

        for query in range(q):
            rs=int(next(it))
            cs=int(next(it))
            re=int(next(it))
            ce=int(next(it))

            start=find(index(rs,cs,0))
            answer="NO"

            for mode in range(2):
                if active(grid[re][ce],mode):
                    if find(index(re,ce,mode))==start:
                        answer="YES"
                        break

            answers.append(answer)

    sys.stdout.write("\n".join(answers))

if __name__=="__main__":
    solve()
