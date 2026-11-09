
import sys

def solve():
    input = sys.stdin.buffer.readline
    t = int(input())
    results = []

    for _ in range(t):
        n, r = map(int, input().split())
        a = list(map(int, input().split()))

        first = 0
        second = 0
        possible = True

        for time in a:
            if first > time:
                possible = False
                break

            first, second = second, max(second, time) + r

        results.append("YES" if possible else "NO")

    sys.stdout.write("\n".join(results))


if __name__ == "__main__":
    solve()
