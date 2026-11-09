import sys

def main():
    readline = sys.stdin.readline
    t = int(readline())
    for _ in range(t):
        n, k = map(int, readline().split())
        chars = readline().split()
        known = [None] * n
        for c in chars:
            guess = "".join(x if x is not None else c for x in known)
            print(guess, flush=True)
            resp = readline().strip()
            if resp == "CORRECT":
                break
            for i, ch in enumerate(resp):
                if ch != "_":
                    known[i] = ch

main()