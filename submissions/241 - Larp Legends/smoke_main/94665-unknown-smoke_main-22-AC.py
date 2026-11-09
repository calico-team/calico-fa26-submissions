import sys


def solve(n, r, a):
    charges = 2
    ready = 0  # time the next charge is restored (only matters if charges < 2)
    for t in a:
        # process recharges first (sequential: next one starts when previous finishes)
        while charges < 2 and ready <= t:
            charges += 1
            if charges < 2:
                ready += r
        if charges == 0:
            return "NO"
        if charges == 2:
            ready = t + r  # recharge timer starts now
        charges -= 1
    return "YES"


def main():
    data = sys.stdin.read().split()
    idx = 0
    t = int(data[idx]); idx += 1
    out = []
    for _ in range(t):
        n = int(data[idx]); r = int(data[idx + 1]); idx += 2
        a = list(map(int, data[idx:idx + n])); idx += n
        out.append(solve(n, r, a))
    print("\n".join(out))


main()
