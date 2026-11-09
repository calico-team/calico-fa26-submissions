import sys

def solve():
    input=sys.stdin.buffer.readline
    quantity=int(input())
    for i in range(quantity):
        n,m,k=map(int,input().split())
        p=list(map(int,input().split()))
        a=[[] for i in range(n+1)]
        for i in range(n):
            a[p[i]].append(i+1)
        count=[0]*(n+1)
        stack=[(0,0)]
        while stack:
            x,time=stack.pop()
            for y in a[x]:
                count[time+1]+=1
                stack.append((y,time+1))
        ans=min(n,m*k)
        total=0
        for time in range(1,min(n,m)+1):
            ans=min(ans,total+(m-time+1)*k)
            total+=count[time]
        print(min(ans,total))

solve()
