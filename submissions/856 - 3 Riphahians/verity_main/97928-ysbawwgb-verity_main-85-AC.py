import sys

input=sys.stdin.readline
quantity=int(input())
for i in range(quantity):
    n,k=map(int,input().split())
    a=input().split()
    ans=["_"]*n
    for x in a:
        for j in range(n):
            if ans[j]=="_":
                ans[j]=x
        print("".join(ans),flush=True)
        s=input().strip()
        if s=="CORRECT":
            break
        ans=list(s)