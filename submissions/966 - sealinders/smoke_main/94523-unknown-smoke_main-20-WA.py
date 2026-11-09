def thing(r,a):
    s=2
    n=0
    for f in a:
        #print(f,s,n,f-n>=r)
        if f-n>=r and (s==1 or s==0):#s==1/s==2 might save time over s<2?
            s+=1
            if f-n>=r*2 and s==1:
                s+=1
        if s==0:
            return 'NO'
        s-=1
        n=f
    return 'YES'
t=int(input())
for ttt in range(t):
    n,r=list(map(int,input().split(' ')))
    a=list(map(int,input().split(' ')))
    print(thing(r,a))
