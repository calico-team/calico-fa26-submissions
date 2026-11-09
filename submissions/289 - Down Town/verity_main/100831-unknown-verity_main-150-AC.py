import sys


def main():
    inp = sys.stdin
    t = int(inp.readline())
    for _ in range(t):
        n, k = map(int, inp.readline().split())
        a = inp.readline().split()
        known = [None] * n
        cand = [a[i % k :] + a[: i % k] for i in range(n)]
        while True:
            guess = []
            for i in range(n):
                if known[i] is not None:
                    guess.append(known[i])
                else:
                    guess.append(cand[i][0])
            print("".join(guess))
            sys.stdout.flush()
            resp = inp.readline().strip()
            if resp == "CORRECT":
                break
            for i in range(n):
                if known[i] is not None:
                    continue
                if resp[i] != "_":
                    known[i] = resp[i]
                else:
                    cand[i].pop(0)


main()
