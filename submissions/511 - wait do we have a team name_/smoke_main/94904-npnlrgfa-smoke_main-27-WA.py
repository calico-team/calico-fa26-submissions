def solve(n: int, r: int, smokes: list):
    safe = True
    for smoke in range(1, n):
        if smokes[smoke] - smokes[smoke - 1] < r:
            safe = False
    if safe:
        return "YES"
    else:
        return "NO"


t = int(input())
ans = []
for _ in range(t):
    n, r = map(int, input().split())
    smokes = list(map(int, input().split()))
    ans.append(solve(n, r, smokes))

print("\n".join(ans))
