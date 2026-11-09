import sys


def main():
    rd = sys.stdin.readline
    wr = sys.stdout.write
    fl = sys.stdout.flush
    t = int(rd())
    for _ in range(t):
        n, k = map(int, rd().split())
        a = rd().split()
        known = [None] * n
        for c in a:
            guess = ''.join([x if x is not None else c for x in known])
            wr(guess + '\n')
            fl()
            res = rd().strip()
            if res == 'CORRECT':
                break
            for i, ch in enumerate(res):
                if ch != '_':
                    known[i] = ch


main()
