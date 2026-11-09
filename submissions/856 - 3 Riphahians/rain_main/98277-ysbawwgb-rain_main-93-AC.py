import sys

def solve():
    input=sys.stdin.buffer.readline
    quantity=int(input())
    for i in range(quantity):
        n,k=map(int,input().split())
        a=[]
        for j in range(n):
            x,y,z,d=input().split()
            x=int(x)
            y=int(y)
            a.append((x+y,x,d==b"E"))
        a.sort()
        ans=n*k
        count=0
        j=0
        for s,x,d in a:
            while a[j][0]!=s or x-a[j][1]>=k:
                if a[j][2]:
                    count-=1
                j+=1
            if d:
                count+=1
            else:
                ans-=count
        print(ans)

solve()
