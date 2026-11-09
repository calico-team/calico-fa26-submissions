import sys
from math import isqrt

def solve():
    input=sys.stdin.buffer.readline
    quantity=int(input())
    for i in range(quantity):
        n,m,q=map(int,input().split())
        a=[tuple(map(int,input().split())) for i in range(q)]
        ans=[0]*(n*m)
        p=list(range(n*m+1))
        b={}
        for r,c,power in reversed(a):
            if power not in b:
                b[power]=[isqrt(power*power-i*i) for i in range(-power,power+1)]
            for x,y in enumerate(b[power],r-power):
                base=x*m+c
                left=base-y
                right=base+y
                j=p[left]
                if j>right:
                    continue
                j=find(p,j)
                if j<=right:
                    count=power*power-(x-r)*(x-r)+1
                    while j<=right:
                        y=j-base
                        ans[j]=count-y*y
                        p[j]=find(p,j+1)
                        j=p[j]
                p[left]=j
        del p
        for i in range(n):
            print(" ".join(map(str,ans[i*m:(i+1)*m])))

def find(p,x):
    while p[x]!=x:
        p[x]=p[p[x]]
        x=p[x]
    return x

solve()
