t=int(input())
for i in range(t):
    n,k=map(int,input().split()); a=input().split(); f=[]; w=[]
    for j in range(n):
        f.append(0); w.append("")
    for c in a:
        g=[]
        for j in range(n):
            if f[j]==1: g.append(w[j])
            else: g.append(c)
        print("".join(g)); r=input()
        if r=="CORRECT": break
        for j in range(n):
            if r[j]!="_":
                f[j]=1; w[j]=r[j]