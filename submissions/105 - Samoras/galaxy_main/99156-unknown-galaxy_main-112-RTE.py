import sys

def solve():
    data=sys.stdin.buffer.read().split()
    if not data:
        return

    it=iter(data)
    answers=[]
    tests=int(next(it))

    for test in range(tests):
        n=int(next(it))
        m=int(next(it))
        k=int(next(it))
        parent=[int(next(it)) for i in range(n)]

        parent=[0]+parent

        if n<=m:
            answers.append(str(n))
            continue

        children=[[] for i in range(n+1)]
        stack=[]

        for node in range(1,n+1):
            p=parent[node]
            if p==0:
                stack.append(node)
            else:
                children[p].append(node)

        depth=[0]*(n+1)
        while stack:
            node=stack.pop()
            for child in children[node]:
                depth[child]=depth[node]+1
                stack.append(child)

        counts=[0]*m
        for node in range(1,n+1):
            if depth[node]<m:
                counts[depth[node]]+=1

        deepest=m-1
        while deepest>=0 and counts[deepest]==0:
            deepest-=1

        if deepest<0:
            answers.append("0")
            continue

        child_count=[len(children[node]) for node in range(n+1)]

        for node in range(1,n+1):
            if depth[node]>=m:
                p=parent[node]
                if p:
                    child_count[p]-=1

        leaves=[[] for i in range(deepest+1)]
        for node in range(1,n+1):
            if depth[node]<m and child_count[node]==0:
                leaves[depth[node]].append(node)

        total=sum(counts)
        remaining=0
        leaf_level=deepest

        for level in range(deepest,-1,-1):
            remaining+=counts[level]
            capacity=k*(m-level)

            while remaining>capacity:
                while leaf_level>=level and not leaves[leaf_level]:
                    leaf_level-=1

                if leaf_level<level:
                    break

                node=leaves[leaf_level].pop()
                counts[depth[node]]-=1
                remaining-=1
                total-=1

                p=parent[node]
                if p and depth[p]<m:
                    child_count[p]-=1
                    if child_count[p]==0:
                        leaves[depth[p]].append(p)

        answers.append(str(total))

    sys.stdout.write("\n".join(answers))

if __name__=="__main__":
    solve()
