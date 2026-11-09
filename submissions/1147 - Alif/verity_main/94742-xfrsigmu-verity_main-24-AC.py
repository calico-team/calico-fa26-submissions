import sys

def rd():
    return sys.stdin.readline().strip()

def go(N, A):
    fixed = [None] * N
    idx = [0] * N

    while True:
        cur = [fixed[i] if fixed[i] is not None else A[idx[i]] for i in range(N)]
        s = "".join(cur)
        print(s, flush=True)

        r = rd()
        if r == "CORRECT":
            return

        for i in range(N):
            if fixed[i] is None:
                if r[i] == "_":
                    idx[i] += 1
                else:
                    fixed[i] = cur[i]

def main():
    t = int(rd())
    for _ in range(t):
        n, k = map(int, rd().split())
        A = rd().split()
        go(n, A)

if __name__ == "__main__":
    main()