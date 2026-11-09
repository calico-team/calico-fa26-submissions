import random

t = int(input())

for _ in range(t):
    n, m, q = map(int, input().split())

    for _ in range(n):
        input()

    for _ in range(q):
        input()
        print(random.choice(["YES", "NO"]))