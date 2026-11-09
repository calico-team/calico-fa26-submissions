import sys
input = sys.stdin.readline

def find(depth, total, touse):
    # print("test case starts here")
    if depth > sm:
        return total
    if depth == sm:
        dih = []
        for i in touse:
            dih = dih + graph[i]
        # print(*dih)
        return find(depth + 1, total + min(len(dih), mx), [])
    else:
        special = []
        others = []
        for i in touse:
            for j in graph[i]:
                if j in graph:
                    special.append(j)
                else:
                    others.append(j)
        if len(special) > mx:
            special.sort(key = lambda x: len(graph[x]))
            special[:mx]
        # print(*special)
        # print(*others)
        return find(depth + 1, total + min(len(special) + len(others), mx), special)

for i in range(int(input())):
    cl,sm, mx = map(int, input().split())
    grid = [[] for _ in range(sm)]
    preq = list(map(int, input().split()))
    graph = {}
    for idx, itm in enumerate(preq):
        try:
            graph[itm].append(idx + 1)
        except:
            graph[itm] = [idx + 1]
    sys.stdout.write(f"{find(1, 0, [0])}\n")