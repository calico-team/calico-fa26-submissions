def query(nbrs):
    r1, c1, r2, c2 = map(int, input().split())
    if (r2, c2) in nbrs[(r1, c1)]:
        print("YES")
    else:
        print("NO")

def BFS(root, pzl, n, m):
    nbrs = {root}
    parseMe = [root]
    idx = 0

    while idx < len(parseMe):
        r1, c1 = parseMe[idx]
        idx += 1
        curr = pzl[r1][c1]
        for r2, c2 in {(r1-1, c1), (r1+1, c1),(r1, c1+1), (r1, c1-1)}:
            if 0 <= r2 < n and 0 <= c2 < m:
                if (r2, c2) not in nbrs:
                    nbr = pzl[r2][c2]

                    if curr == "." or nbr == "." or curr == nbr:
                        nbrs.add((r2, c2))
                        parseMe.append((r2, c2))

    return nbrs

def solve():
    n, m, q = map(int, input().split())
    pzl = [input() for _ in range(n)]

    nbrs = {}

    for r in range(n):
        for c in range(m):
            if (r, c) not in nbrs:
                nbrs_set = BFS((r, c), pzl, n, m)

                for pos in nbrs_set:
                    nbrs[pos] = nbrs_set

    for _ in range(q):
        query(nbrs)

def main():
    t = int(input())
    for _ in range(t):
        solve()

if __name__ == "__main__":
    main()