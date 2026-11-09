
import sys

t = int(input())

for _ in range(t):
    n, k = map(int, input().split())
    a = input().split()

    ans = [""] * n

    for c in a:
        guess = ""

        for j in range(n):
            if ans[j] == "":
                guess += c
            else:
                guess += ans[j]

        print(guess)
        sys.stdout.flush()

        result = input().strip()

        if result == "CORRECT":
            break

        for j in range(n):
            if result[j] != "_":
                ans[j] = result[j]
