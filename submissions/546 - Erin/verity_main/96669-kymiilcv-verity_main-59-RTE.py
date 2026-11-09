for _ in range(int(input())):
    n,k=map(int,input().split())
    a=[x for x in input().split()]
    ans=['' for _ in range(n)]
    for c in a:
        print(c*n)
        s=input()
        for i in range(n):
            if s[i]!='_':
                ans[i]=s[i]
    print(''.join(ans))
    input()