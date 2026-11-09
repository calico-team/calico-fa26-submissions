def solve():
    if input() == "FIRST":
        n = int(input())
        d = [0] * n
        x = [0] * n
        for i in range(n-1):
            u, v = map(int,input().split())
            u, v = u-1, v-1
            d[u] += 1
            d[v] += 1
            x[u] ^= v
            x[v] ^= u
        d[0] = -1
        for i in range(n):
            while d[i] == 1:
                d[i] -= 1
                d[x[i]] -= 1
                x[x[i]] ^= i
                i = x[i]
        x[0] = 0
        for i in range(1,n):
            x[0] ^= x[i]
        print(*x)
    else:
        n = int(input())
        a = list(map(int,input().split()))
        x = -1
        for v in a:
            x ^= v
        for i in range(n):
            if a[i] == -1:
                a[i] = x
        for i in range(1,n):
            print(i+1,a[i]+1)
solve()
