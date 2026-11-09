
import sys

def solve():
    input = sys.stdin.readline
    T = int(input())

    for _ in range(T):
        N, R = map(int, input().split())
        A = list(map(int, input().split()))

        first = 0
        second = 0
        possible = True

        for t in A:
            if first <= t:
                first = t + R
            elif second <= t:
                second = first + R
                first = first + R
            else:
                possible = False
                break

        print("YES" if possible else "NO")


if __name__ == "__main__":
    solve()
