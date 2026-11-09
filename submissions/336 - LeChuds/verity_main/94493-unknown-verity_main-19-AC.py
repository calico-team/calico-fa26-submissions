import sys
input = sys.stdin.readline

for _ in range(int(input())):
    n, k = map(int, input().split())
    s = "_" * n
    for c in input().split():
        print(s.replace("_", c), flush=True)
        s = input().strip()
        if s == "CORRECT":
            break
