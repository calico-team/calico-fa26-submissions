def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    # YOUR CODE HERE
    res = [None for _ in range(N)]

    for c in A:
        print_guess(c.capitalize() * N)  # guess all caps to check
        s = read_string().strip()
        for j, c2 in enumerate(s):
            if c2 != "_":
                res[j] = c.capitalize()
        if None not in res:
            break

    print_guess("".join(res))
    read_string()  # idgaf


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


if __name__ == "__main__":
    main()
