import sys
import io

SAMPLE = """5
5 10
20 30 40 50 60
7 100
1 2 3 4 5 6 7
4 10
1 2 12 13
8 5
5 10 17 30 36 45 50 56
9 30
20 70 80 90 100 190 210 220 250
"""


if len(sys.argv) > 1 and sys.argv[1] == "test":
    readline = io.BytesIO(SAMPLE.encode()).readline
else:
    readline = sys.stdin.buffer.readline

t = int(readline())
out = []
for _ in range(t):
    n, r = map(int, readline().split())
    a = list(map(int, readline().split()))

    f1 = 0 
    f2 = 0  
    ok = True
    for x in a:
        if x < f1:
            ok = False
            break
        f1, f2 = f2, max(x, f2) + r
    out.append("YES" if ok else "NO")

print("\n".join(out))