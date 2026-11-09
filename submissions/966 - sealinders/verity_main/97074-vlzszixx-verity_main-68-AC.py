t=int(input())
for ttt in range(t):
    n,k=list(map(int,input().split(' ')))
    a=input().split(' ')#
    p='_'*n
    i=0
    while True:
        p2=''
        for f in range(n):
            #print(p[f],p[f]=='_',a,a[i])
            if p[f]=='_':
                p2+=a[i]
            else :
                p2+=p[f]
        print(p2)
        i+=1
        p=input()
        if p=='CORRECT':
            break
        
