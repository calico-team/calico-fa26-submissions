t=int(input())
for z in range(t):
    n,m,q=map(int,input().split())
    tot=n*m
    g=[]
    for i in range(n):
        g.append(input())
    c=[]
    for i in range(2*tot):
        c.append(0)
    M=[(1,0),(-1,0),(0,1),(0,-1)]
    k=0
    for i in range(2*tot):
        if c[i]!=0:continue
        w=i//tot
        x=i%tot//m
        y=i%tot%m
        if w==0 and g[x][y]=="R":continue
        if w==1 and g[x][y]=="B":continue
        k+=1
        c[i]=k
        s=[(x,y,w)]
        h=0
        while h<len(s):
            x,y,w=s[h];h+=1
            if w==0:bad="R"
            else:bad="B"
            if g[x][y]=="." and c[x*m+y+(1-w)*tot]==0:
                c[x*m+y+(1-w)*tot]=k
                s.append((x,y,1-w))
            for dx,dy in M:
                u=x+dx
                v=y+dy
                if 0<=u<n and 0<=v<m:
                    if g[u][v]!=bad and c[u*m+v+w*tot]==0:
                        c[u*m+v+w*tot]=k
                        s.append((u,v,w))
    for i in range(q):
        a,b,e,f=map(int,input().split())
        r=c[a*m+b]
        if r==c[e*m+f] or r==c[e*m+f+tot]:
            print("YES")
        else:
            print("NO")
