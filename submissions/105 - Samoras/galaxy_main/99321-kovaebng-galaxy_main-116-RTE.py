import sys

def solve():
    data=sys.stdin.buffer.read().split()
    if not data:
        return
    it=iter(data)
    tests=int(next(it))
    answers=[]

    for test in range(tests):
        n=int(next(it))
        m=int(next(it))
        k=int(next(it))
        parent=[0]*(n+1)

        for i in range(1,n+1):
            parent[i]=int(next(it))

        if m>=n:
            answers.append(str(n))
            continue

        tree=[[] for i in range(n+1)]
        roots=[]
        for i in range(1,n+1):
            p=parent[i]
            if p:
                tree[p].append(i)
            else:
                roots.append(i)

        depth=[0]*(n+1)
        stack=roots[:]

        while stack:
            node=stack.pop()
            for child in tree[node]:
                depth[child]=depth[node]+1
                stack.append(child)

        counts=[0]*m
        deepest=-1

        for i in range(1,n+1):
            d=depth[i]
            if d<m:
                counts[d]+=1
                deepest=max(deepest,d)

        if deepest==-1:
            answers.append("0")
            continue

        remaining=[0]*(n+1)
        for i in range(1,n+1):
            p=parent[i]
            if p and depth[i]<m and depth[p]<m:
                remaining[p]+=1

        leaves=[[] for i in range(deepest+1)]
        for i in range(1,n+1):
            if depth[i]<m and remaining[i]==0:
                leaves[depth[i]].append(i)

        leaf_depth=deepest
        while leaf_depth>=0 and not leaves[leaf_depth]:
            leaf_depth-=1

        total=sum(counts)
        current=0

        for d in range(deepest,-1,-1):
            current+=counts[d]
            limit=k*(m-d)

            while current>limit and leaf_depth>=d:
                node=leaves[leaf_depth].pop()
                counts[depth[node]]-=1
                current-=1
                total-=1

                p=parent[node]
                if p and depth[p]<m:
                    remaining[p]-=1
                    if remaining[p]==0:
                        leaves[depth[p]].append(p)

                while leaf_depth>=0 and not leaves[leaf_depth]:
                    leaf_depth-=1

        answers.append(str(total))

    sys.stdout.write("\n".join(answers))

if __name__=="__main__":
    solve()
