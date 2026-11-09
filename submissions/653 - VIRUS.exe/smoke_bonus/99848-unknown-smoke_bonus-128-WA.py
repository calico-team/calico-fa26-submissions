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
    import sys
    inp = sys.stdin.buffer.read().split()
    i=0
    t=int(inp[i])
    i+=1
    out=[]
    
    for _ in range(t):
        n,r=int(inp[i] ), int(inp[i+1])
        i+=2
        a=list(map(int,inp[i:i+n]))
        i+=n
        out.append(Problem2(r,a))
        print("\n".join(out))