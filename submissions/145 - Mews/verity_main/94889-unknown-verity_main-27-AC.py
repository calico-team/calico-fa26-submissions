import sys


def solve_case(N, K, A):
    known = [None] * N
    j = 0
    while True:
        g = "".join(known[i] if known[i] is not None else A[min(j, K - 1)] for i in range(N))
        print(g, flush=True)
        resp = sys.stdin.readline().strip()
        if resp == "CORRECT":
            return
        for i in range(N):
            if resp[i] != '_':
                known[i] = resp[i]
        j += 1


def read_your_input():
    T = int(sys.stdin.readline())
    for _ in range(T):
        N, K = map(int, sys.stdin.readline().split())
        A = sys.stdin.readline().split()
        solve_case(N, K, A)


if __name__ == "__main__":
    read_your_input()