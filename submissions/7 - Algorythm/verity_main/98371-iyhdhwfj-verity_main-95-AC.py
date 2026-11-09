
def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """

    discovered = ['_'] * N

    for attempt in range(K):

        current_guess = ""

        for position in range(N):
            if discovered[position] != '_':
                current_guess += discovered[position]
            else:
                current_guess += A[attempt]

        print_guess(current_guess)

        response = read_string()

        if response == "CORRECT":
            return

        for position in range(N):
            if response[position] != '_':
                discovered[position] = response[position]


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

    for test_case in range(T):
        N, K = map(int, input().split())
        A = input().split()

        solve(N, K, A)


if __name__ == '__main__':
    main()
