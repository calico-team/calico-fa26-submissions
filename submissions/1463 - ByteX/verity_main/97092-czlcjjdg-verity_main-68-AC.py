def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    known = [None] * N  # characters we've confirmed so far

    for j in range(K):
        
        ## Fill confirmed positions with their letter, the rest with the current letter.
        guess = ''.join(known[i] if known[i] is not None else A[j] for i in range(N))
        print_guess(guess)
        resp = read_string()

        if resp == "CORRECT":
            return

        ##Any non-underscore means that position of our guess was right.
        for i in range(N):
            if resp[i] != '_':
                known[i] = guess[i]


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
