t=int(input())
for z in range(t):
    n,m,q=map(int,input().split())
    tot=n*m
    g=[]
    for i in range(n):
        g.append(input())
    sd=[]
    sv=[]
    M=[(1,0),(-1,0),(0,1),(0,-1)]
    for i in range(q):
        a,b,c,d=map(int,input().split())
        k=-1
        for j in range(len(sd)):
            if sd[j]==(c,d):k=j
        if k==-1:
            v=[]
            for j in range(2*tot):
                v.append(0)
            p=[]
            if g[c][d]!="R":
                v[c*m+d]=1
                p.append((c,d,0))
            if g[c][d]!="B":
                v[c*m+d+tot]=1
                p.append((c,d,1))
            h=0
            while h<len(p):
                x,y,w=p[h];h+=1
                if w==0:bad="R"
                else:bad="B"
                if g[x][y]=="." and v[x*m+y+(1-w)*tot]==0:
                    v[x*m+y+(1-w)*tot]=1
                    p.append((x,y,1-w))
                for dx,dy in M:
                    u=x+dx
                    s=y+dy
                    if 0<=u<n and 0<=s<m:
                        if g[u][s]!=bad and v[u*m+s+w*tot]==0:
                            v[u*m+s+w*tot]=1
                            p.append((u,s,w))
            sd.append((c,d))
            sv.append(v)
            k=len(sd)-1
        if sv[k][a*m+b]==1:
            print("YES")
        else:
            print("NO")