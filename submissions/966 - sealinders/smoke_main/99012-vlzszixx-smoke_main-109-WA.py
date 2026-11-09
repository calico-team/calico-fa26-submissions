def thing(r,a):
    s=2
    n=0
    m=0#if the first smoke is used up then turn m into f and once it
    #recharges then calculate the exact point at which it recharged and turn
    #m into that?
    for f in a:
        j=False
        u=n%r
        #print(f,s,n,f-n+u-m>=r,m,flush=True)
        if f-n+u-m>=r and (s==1 or s==0):#s==1/s==0 might save time over s<2?
            s+=1
            j=True
            if f-n+u-m>=r*2 and s==1:
                s+=1
        if s==0:
            return 'NO'
        elif s==2 and j:#second condition
            m=(n-u+r)%r
            #print('YAS')
        elif s==2:#first condition
            m=f%r
        s-=1
        #print(s,f-n+u)
        n=f
    #print(s)
    return 'YES'
t=int(input())
for ttt in range(t):
    n,r=list(map(int,input().split(' ')))
    a=list(map(int,input().split(' ')))
    print(thing(r,a))
