import sys


def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    iterator = iter(input_data)
    T = int(next(iterator))

    output = []
    for _ in range(T):
        N = int(next(iterator))
        R = int(next(iterator))

        c1 = 0
        c2 = 0
        possible = True

        for _ in range(N):
            t = int(next(iterator))
            if not possible:
                continue

            if c1 > t:
                possible = False
            else:
                new_ready = max(t, c2) + R
                c1 = c2
                c2 = new_ready

        output.append("YES" if possible else "NO")

    print("\n".join(output))


if __name__ == "__main__":
    solve()