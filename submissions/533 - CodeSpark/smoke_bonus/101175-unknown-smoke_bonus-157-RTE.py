import sys

def main():
    data = sys.stdin.buffer.read().split()
    p = 0
    t = int(data[p]); p += 1
    out = []
    for _ in range(t):
        n = int(data[p]); r = int(data[p+1]); p += 2
        c = 2          # charges available
        ready = 0      # time the charge currently recharging is restored
        ok = True
        for j in range(p, p + n):
            a = int(data[j])
            while c < 2 and ready <= a:
                c += 1
                if c < 2:
                    ready += r
            if c == 0:
                ok = False
                break
            if c == 2:
                ready = a + r
            c -= 1
        p += n
        out.append("YES" if ok else "NO")
    print("\n".join(out))

main()