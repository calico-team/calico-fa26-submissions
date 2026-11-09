def solve(N: int, K: int, A: list[str]) -> None:
    known = [None] * N
    r = 0

    while True:
        c = A[r % K]
        guess = ''.join(known[i] if known[i] is not None else c for i in range(N))
        print_guess(guess)
        resp = read_string()

        if resp == "CORRECT":
            return

        for i in range(N):
            if resp[i] != '_':
                known[i] = resp[i]

        r += 1


def read_string():
    """
    Reads a single string from standard input.
    """
    s = input()
    return s

def print_guess(guess):
    """
    Prints a guess to standard output and flushes the output stream buffer.
    """
    print(guess, flush=True)


def main():
    T = int(input())

    for _ in range(T):
        N, K = map(int, input().split())
        A = input().split()

        solve(N, K, A)


if __name__ == '__main__':
    main()
