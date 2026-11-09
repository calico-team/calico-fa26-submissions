# smoke
def solve(n: int, r: int, smokes: list):
    charges = 2
    curr = 0
    for smoke in smokes:
        while charges < 2 and curr <= smoke:
            charges += 1
            curr += r
        if charges == 0:
            return "NO"
        if charges == 2:
            curr = smoke + r
        charges -= 1
    return "YES"


t = int(input())
ans = []
for _ in range(t):
    n, r = map(int, input().split())
    smokes = list(map(int, input().split()))
    ans.append(solve(n, r, smokes))

print("\n".join(ans))
