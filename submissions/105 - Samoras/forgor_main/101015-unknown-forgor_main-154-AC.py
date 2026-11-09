import sys
import heapq

mod=1000001

def encode(adj,n):
    if n==2:
        return []
    degree=[len(adj[i]) for i in range(n+1)]
    leaves=[i for i in range(1,n+1) if degree[i]==1]
    heapq.heapify(leaves)
    code=[]

    for i in range(n-2):
        leaf=heapq.heappop(leaves)
        for node in adj[leaf]:
            if degree[node]>0:
                code.append(node)
                degree[node]-=1
                degree[leaf]-=1
                if degree[node]==1:
                    heapq.heappush(leaves,node)
                break

    return code


def decode(code,n):
    if n==2:
        return [(1,2)]

    degree=[1]*(n+1)
    for node in code:
        degree[node]+=1

    leaves=[i for i in range(1,n+1) if degree[i]==1]
    heapq.heapify(leaves)
    edges=[]

    for node in code:
        leaf=heapq.heappop(leaves)
        edges.append((leaf,node))
        degree[leaf]-=1
        degree[node]-=1
        if degree[node]==1:
            heapq.heappush(leaves,node)

    a=heapq.heappop(leaves)
    b=heapq.heappop(leaves)
    edges.append((a,b))
    return edges


def main():
    data=sys.stdin.buffer.read().split()
    if not data:
        return

    phase=data[0].decode()
    pos=1
    n=int(data[pos])
    pos+=1

    if phase=="FIRST":
        adj=[[] for i in range(n+1)]

        for i in range(n-1):
            u=int(data[pos])
            v=int(data[pos+1])
            pos+=2
            adj[u].append(v)
            adj[v].append(u)

        code=encode(adj,n)
        check=sum(code)%mod if code else 0
        result=code+[check,0]
        sys.stdout.write(" ".join(map(str,result)))

    else:
        values=list(map(int,data[pos:pos+n]))

        if n==2:
            sys.stdout.write("1 2")
            return

        code=values[:n-2]
        missing=-1

        for i in range(n):
            if values[i]==-1:
                missing=i
                break

        if missing<n-2:
            known=sum(code[i] for i in range(n-2) if i!=missing)
            code[missing]=(values[n-2]-known)%mod

        edges=decode(code,n)
        sys.stdout.write("\n".join(str(u)+" "+str(v) for u,v in edges))


if __name__=="__main__":
    main()
