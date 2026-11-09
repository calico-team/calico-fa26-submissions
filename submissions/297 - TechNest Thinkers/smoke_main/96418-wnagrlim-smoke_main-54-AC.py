import sys

def main():
    d = sys.stdin.read().split(); i =1; out = []
    for _ in range(int(d[0])):
        n, r = int(d[i]), int(d[i+1]); i += 2
        c, e, ok = 2, None, "Yes"
        for t in map(int, d[i : i+n]):
            while c < 2 and e <= t:
                c += 1; e = e + r if c < 2 else None
            if c == 0: ok = "No"; break
            c-= 1
            if e is None: e = t + r
        i += n; out.append(ok)
    print('\n'.join(out))
main()
    