import sys

def solve(n, r, a):
    charges = 2
    done = 0
    for t in a:
        while charges < 2 and done <= t:
            charges += 1
            if charges < 2:
                done += r
        if charges == 0:
            return "NO"
        if charges == 2:
            done = t + r
        charges -= 1
    return "YES"

def main():
    data = sys.stdin.buffer.read().split()
    idx = 0
    t = int(data[idx]); idx += 1
    out = []
    for _ in range(t):
        n = int(data[idx]); r = int(data[idx + 1]); idx += 2
        a = data[idx:idx + n]; idx += n
        out.append(solve(n, r, map(int, a)))
    print("\n".join(out))

main()
