def solve():
    for _ in range(int(input())):
        n, m, q = map(int,input().split())
        s = [[(0 if x=='.' else (1 if x == 'R' else 2)) for x in input()] for __ in range(n)]
        cc = [[-1] * m for __ in range(n)]
        dx = [1,0,-1,0]
        dy = [0,1,0,-1]
        cnt = 0
        for i in range(n):
            for j in range(m):
                if cc[i][j] != -1:
                    continue
                cc[i][j] = cnt
                st = [(i,j)]
                while len(st):
                    ci, cj = st[-1]
                    st.pop()
                    for d in range(4):
                        ni, nj = ci + dx[d], cj + dy[d]
                        if not (0 <= ni < n and 0 <= nj < m):
                            continue
                        if cc[ni][nj] != -1:
                            continue
                        if s[ci][cj] + s[ni][nj] == 3:
                            continue
                        cc[ni][nj] = cnt
                        st.append((ni,nj))
                cnt += 1
        for __ in range(q):
            rs, cs, re, ce = map(int,input().split())
            print("YES" if cc[rs][cs] == cc[re][ce] else "NO")
solve()
