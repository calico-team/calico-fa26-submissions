def solve(N: int, K: int, A: list[str]) -> None:
    ans = [''] * N

    for j in range(K - 1):
        char = A[j]

        guess = ''.join(x if x else char for x in ans)

        print_guess(guess)
        response = read_string()

        if response == "CORRECT":
            return

        for i in range(N):
            if response[i] != '_':
                ans[i] = response[i]

    last = A[K - 1]
    guess = ''.join(x if x else last for x in ans)

    print_guess(guess)
    read_string()


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