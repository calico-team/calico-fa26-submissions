def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
   
    found = ["?"] * N

    for letter in A:
        attempt = ""

        for pos in range(N):
            if found[pos] == "?":
                attempt += letter
            else:
                attempt += found[pos]

        print_guess(attempt)

        result = read_string()

        if result == "CORRECT":
            return

        for pos in range(N):
            if result[pos] != "_":
                found[pos] = result[pos]

    final_word = "".join(found)
    print_guess(final_word)
    result = read_string()


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
