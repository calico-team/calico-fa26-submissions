
import sys

def solve():
    input = sys.stdin.readline
    T = int(input())

    for _ in range(T):
        N = int(input())
        L = list(map(int, input().split()))
        R = list(map(int, input().split()))

        dp = {0}

        for l, r in zip(L, R):
            new_dp = set()
            for x in dp:
                for f in range(l, r + 1):
                    new_dp.add(x ^ f)
            dp = new_dp

        print(max(dp))


if __name__ == "__main__":
    solve()
