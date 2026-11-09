import sys
from collections import deque

def main():
    data=sys.stdin.read().split()
    p=0
    T=int(data[p]); p+=1
    out=[]
    for _ in range(T):
        N=int(data[p]); M=int(data[p+1]); Q=int(data[p+2]); p+=3
        G=data[p:p+N]; p+=N
        def active(r,c,m):
            ch=G[r][c]
            if ch==".":
                return True
            return (ch=='B' and m==0) or (ch=='R' and m==1)

        comp=[-1]*(N*M*2)
        cid=0
        for r in range(N):
            for c in range(M):
                for m in range(2):
                    s=(r*M+c)*2+m
                    if comp[s]!=-1 or not active(r,c ,m):
                        continue
                    comp[s]=cid
                    dq=deque([(r,c,m)])
                    while dq:
                        x,y,md=dq.popleft()
                        for dx,dy in ((1,0),(-1,0),(0,1),(0,-1)):
                                      nx,ny=x+dx,y+dy
                                      if 0<=nx<N and 0<=ny<M and active(nx,ny,md):
                                          ns=(nx*M+ny)*2+md
                                          if comp[ns]==-1:
                                              comp[ns]=cid
                                              dq.append((nx,ny,md))
                        if G[x][y]=='.':
                                      ns=(x*M+y)*2+(1-md)
                                      if comp[ns]==-1:
                                          comp[ns]=cid
                                          dq.append((x,y,1-md))
                    cid+=1
        for _ in range(Q):
                                      rs,cs,re,ce=(int(v) for v in data[p:p+4]); p+=4
                                      start=comp[(rs*M+cs)*2+0]
                                      ok=False
                                      for m in range(2):
                                          if active(re,ce,m) and comp[(re*M+ce)*2+m]==start:
                                              ok=True
                                              break
                                      out.append("YES" if ok else "NO")
    print("\n".join(out))
main()
                                      
