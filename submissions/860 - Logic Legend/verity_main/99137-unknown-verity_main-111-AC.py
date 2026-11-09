# Source: https://usaco.guide/general/io
import sys

def solve():
    input = sys.stdin.readline
    t = int(input())

    for _ in range(t):
        n, k = map(int, input().split())
        chars = input().split()

        ans = ['?'] * n

        for ch in chars:
            guess = ''.join(ans[i] if ans[i] != '?' else ch for i in range(n))
            print(guess, flush=True)

            response = input().strip()
            if response == "CORRECT":
                break

            for i, c in enumerate(response):
                if c != '_':
                    ans[i] = c

if __name__ == "__main__":
    solve()

