def solve():
    for _ in range(int(input())):
        n, m, k = map(int,input().split())
        p = [int(i)-1 for i in input().split()]
        d = [0] * n
        o = []
        h = [0] * n
        for i in range(n):
            if p[i] != -1:
                d[p[i]] += 1
        for i in range(n):
            while d[i] == 0:
                d[i] -= 1
                o.append(i)
                if p[i] != -1:
                    d[p[i]] -= 1
                    i = p[i]
                else:
                    break
        for x in o[::-1]:
            if p[x] != -1:
                h[x] = h[p[x]] + 1
        cnt = [0] * n
        for i in range(n):
            cnt[h[i]] += 1
        ans = m * k
        cur = 0
        for i in range(min(n,m)):
            cur += cnt[i]
            ans = min(ans, m * k - (i + 1) * k + cur)
        ans = min(ans, n)
        print(ans)
solve()
