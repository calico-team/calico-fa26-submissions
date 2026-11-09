

def solve():
    n, k = map(int, input().split())
    c = list(input().split())

    ans = ["" for _ in range(n)]
    for i in range(k):
        print("".join([c[i] for _ in range(n)]))
        res = input().strip()
        if res == "CORRECT":
            return
        for j in range(n):
            if res[j] != "_":
                ans[j] = c[i]
    print("".join(ans))
    input()

for _ in range(int(input())):
    solve()
