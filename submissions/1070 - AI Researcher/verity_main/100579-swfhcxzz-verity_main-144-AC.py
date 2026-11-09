def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    char_found = [None] * N

    for current in A:
        guessed_char = ""

        for i in range(N):
            if char_found[i] is not None:
                guessed_char += char_found[i]
            else:

                guessed_char += current

        print_guess(guessed_char)

        result = read_string()

        if result == "CORRECT":
            return

        for i in range(N):
            if result[i] != "_":
                char_found[i] = result[i]


    

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
