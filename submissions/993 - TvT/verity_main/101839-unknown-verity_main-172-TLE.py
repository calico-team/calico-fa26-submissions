def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    guess = ["_"] * N
    default_char = A[0]


    for i in range(N):
            for item in A:
                guess[i] = item
                current_guess = "".join([c if c != "_" else default_char for c in guess])

                print_guess(current_guess)
                s=read_string()
                if s == "CORRECT": return
                if len(s) == N :
                    for j in range(N):
                        if s[j] != "_":
                            guess[j] = s[j]
                if guess[i] != "_": break

    # YOUR CODE HERE

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
