def solve(N: int, K: int, A: list) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    known = [None] * N
    for ch in A[:-1]:
        print_guess(ch * N)
        res = read_string()
        if res == "CORRECT":
            return
        for i in range(min(N, len(res))):
            if res[i] != '_':
                known[i] = ch
    print_guess(''.join(c if c is not None else A[-1] for c in known))
    read_string()

def read_string():
    """
    Reads a single string from standard input.
    """
    try:
        s = input().strip()
        while s == "":
            s = input().strip()
    except EOFError:
        exit()
    if s == "WRONG_ANSWER":
        exit()
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