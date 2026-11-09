def thing(n,r,a):
    u=a[-1]
    s=2
    a=set(a)
    for f in range(u+1):
        if f%r==0 and s<2:
            s+=1
        if f in a:
            s-=1
        if s==-1:
            return 'NO'
    return 'YES'
t=int(input())
for ttt in range(t):
    n,r=list(map(int,input().split(' ')))
    a=list(map(int,input().split(' ')))
    print(thing(n,r,a))
