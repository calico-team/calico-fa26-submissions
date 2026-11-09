def solve():
    t = int(input())

    for _ in range(t):
        n, r = map(int, input().split())
        a = list(map(int, input().split()))

        recharge = []
        available = 2
        possible = True

        for time in a:
            while recharge and recharge[0] <= time:
                recharge.pop(0)
                available += 1

            if available == 0:
                possible = False
                break

            available -= 1
            recharge.append(time + r)

        print("YES" if possible else "NO")


def read_your_input():
    solve()


if __name__ == "__main__":
    read_your_input()