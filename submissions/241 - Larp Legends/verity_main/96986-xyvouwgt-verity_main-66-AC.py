import sys


def main():
    t = int(sys.stdin.readline())
    for _ in range(t):
        n, k = map(int, sys.stdin.readline().split())
        letters = sys.stdin.readline().split()
        known = [None] * n
        for ch in letters:
            guess = "".join(c if c is not None else ch for c in known)
            print(guess, flush=True)
            resp = sys.stdin.readline().strip()
            if resp == "CORRECT":
                break
            for i in range(n):
                if resp[i] != "_":
                    known[i] = resp[i]


main()
