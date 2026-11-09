import sys

def main():
    rd = sys.stdin.buffer.readline
    t = int(rd())
    out = []
    for _ in range(t):
        line = rd().split()
        while not line:
            line = rd().split()
        n = int(line[0]); r = int(line[1])
        c = 2
        ready = 0
        ok = True
        got = 0
        while got < n:
            parts = rd().split()
            if not parts:
                if rd.__self__.closed:
                    break
                continue
            for tok in parts:
                got += 1
                if not ok:
                    continue
                a = int(tok)
                while c < 2 and ready <= a:
                    c += 1
                    if c < 2:
                        ready += r
                if c == 0:
                    ok = False
                    continue
                if c == 2:
                    ready = a + r
                c -= 1
        out.append("YES" if ok else "NO")
    sys.stdout.write("\n".join(out) + "\n")

main()