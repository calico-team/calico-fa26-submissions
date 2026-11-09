def guess(gu,k):
    pass


n=int(input())
for i in range(n):
    try:
        n,kn=list(map(int,input().split()))
    except:
        n, kn = list(map(int, input().split()))
    try:
        k=list(input().split())
    except:
        k = list(input().split())
    s=" "*n
    for j in range(kn):
        print(k[j]*n,flush=True)
        sc=input()

        if sc=="CORRECT":
            break

        flag=True
        for l in range(len(s)):
            if sc[l]!="_":
                s=s[:l]+sc[l]+s[l+1:]
            if s[l]==" ":
                flag=False
        if flag:
            print(s,flush=True)
            input()
            break