
import sys

def solve():
    input = sys.stdin.readline
    T = int(input())

    for _ in range(T):
        N, K = map(int, input().split())
        A = input().split()

        ans = ['_'] * N

        for ch in A:
            guess = ''.join(
                ans[i] if ans[i] != '_' else ch
                for i in range(N)
            )

            print(guess, flush=True)
            response = input().strip()

            if response == "CORRECT":
                break

            for i in range(N):
                if response[i] != '_':
                    ans[i] = response[i]


if __name__ == "__main__":
    solve()
