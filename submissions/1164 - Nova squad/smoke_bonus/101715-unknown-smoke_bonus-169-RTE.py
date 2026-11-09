import sys

SAMPLE = """5
5 10
20 30 40 50 60
7 100
1 2 3 4 5 6 7
4 10
1 2 12 13
8 5
5 10 17 30 36 45 50 56
9 30
20 70 80 90 100 190 210 220 250"""


def solve(n, r, a):
    charges = 2
    next_ready = None  # time when the next charge is restored
    for t in a:
        # recharges are processed before requests at the same timestamp
        while charges < 2 and next_ready is not None and next_ready <= t:
            charges += 1
            next_ready = next_ready + r if charges < 2 else None
        if charges == 0:
            return "NO"
        charges -= 1
        if next_ready is None:
            next_ready = t + r
    return "YES"


def read_input():
    try:
        text = sys.stdin.read()
    except Exception:
        text = ""
    return text if text.strip() else SAMPLE


def main():
    data = read_input().split()
    idx = 0
    T = int(data[idx]); idx += 1
    out = []
    for _ in range(T):
        n, r = int(data[idx]), int(data[idx + 1]); idx += 2
        a = list(map(int, data[idx:idx + n])); idx += n
        out.append(solve(n, r, a))
    print("\n".join(out))


main()