def guess(gu,k):
    pass


n=int(input())
for i in range(n):
    n,kn=list(map(int,input().split()))
    k=list(input().split())
    s=" "*n
    for j in range(kn):
        print(k[j]*n,flush=True)
        sc=input()
        flag=True
        for l in range(len(s)):
            if sc[l]!="_":
                s=s[:l]+sc[l]+s[l+1:]
            if s[l]==" ":
                flag=False
        if flag:
            print(s,flush=True)
            continue