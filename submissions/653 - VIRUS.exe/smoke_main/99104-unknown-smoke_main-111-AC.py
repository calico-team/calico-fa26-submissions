def Problem2(r,a):
    c=2
    t=0
    useable= True
    for i in a:
        while c<2 and t<=i:
            c+=1
            if c<2:
                t+=r
        if c==0:
            useable=False
            break
        if c==2:
            t=i+r
        c-=1
    if useable:
        return "YES"
    else:
        return "NO"

if __name__ == "__main__":
    t = int(input())
    for _ in range(t):
        n,r=map(int,input().split())
        a=list(map(int,input().split()))
        print(Problem2(r,a))