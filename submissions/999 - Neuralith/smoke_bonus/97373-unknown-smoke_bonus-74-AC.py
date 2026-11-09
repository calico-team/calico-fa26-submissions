import sys

def main():
    data = sys.stdin.buffer.read().split()
    T = int(data[0]); p = 1
    out = []
    for _ in range(T):
        n = int(data[p]); R = int(data[p + 1]); p += 2
        a = b = 0
        ok = True
        for i in range(p, p + n):
            t = int(data[i])
            if a > t:
                ok = False
                break
            a, b = b, (t if t > b else b) + R
        p += n
        out.append("YES" if ok else "NO")
    print("\n".join(out))

main()