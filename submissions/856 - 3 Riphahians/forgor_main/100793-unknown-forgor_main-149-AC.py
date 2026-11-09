import sys

def solve():
    input=sys.stdin.buffer.readline
    phase=input().strip()
    n=int(input())
    if phase==b"FIRST":
        a=[[] for i in range(n+1)]
        for i in range(n-1):
            x,y=map(int,input().split())
            a[x].append(y)
            a[y].append(x)
        p=[0]*(n+1)
        count=0
        stack=[1]
        while stack:
            x=stack.pop()
            for y in a[x]:
                if y!=p[x]:
                    p[y]=x
                    count^=x
                    stack.append(y)
        p[1]=count
        del a
        print(" ".join(map(str,p[1:])))
    else:
        a=list(map(int,input().split()))
        count=0
        j=0
        for i in range(n):
            if a[i]==-1:
                j=i
            else:
                count^=a[i]
        a[j]=count
        for i in range(1,n):
            print(i+1,a[i])

solve()
