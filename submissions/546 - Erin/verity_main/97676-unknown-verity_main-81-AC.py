for _ in range(int(input())):
    n,k=map(int,input().split())
    a=[x for x in input().split()]
    ans=['' for _ in range(n)]
    done=False
    for c in a:
        print(c*n)
        s=input()
        if s=='CORRECT':
            done=True
            break
        for i in range(n):
            if s[i]!='_':
                ans[i]=s[i]
    if not done:
        print(''.join(ans))
        input()