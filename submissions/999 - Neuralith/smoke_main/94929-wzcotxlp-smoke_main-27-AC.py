
import sys

def solve():
    input = sys.stdin.buffer.readline
    t = int(input())
    ans = []

    for _ in range(t):
        n, r = map(int, input().split())
        times = map(int, input().split())

        first = 0
        second = 0
        possible = True

        for time in times:
            if first > time:
                possible = False
                break

            # Recharge the used charge after the other
            # pending recharge has completed.
            new_time = max(time, second) + r

            first, second = second, new_time

        ans.append("YES" if possible else "NO")

    sys.stdout.write("\n".join(ans))


if __name__ == "__main__":
    solve()
