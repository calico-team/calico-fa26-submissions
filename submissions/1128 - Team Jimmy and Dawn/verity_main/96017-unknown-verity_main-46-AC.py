def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    known = [None] * N
    index = 0
    while True:
        guess = []
        for i in range(N):
            if known[i] is not None:
                guess.append(known[i])
            else:
                guess.append(A[index])

        guess = "".join(guess)
        print_guess(guess)
        response = read_string()

        if response == "CORRECT":
            break

        for i in range(N):
            if response[i] != "_":
                known[i] = response[i]
        index = (index + 1) % K


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