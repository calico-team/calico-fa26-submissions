import sys


def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    arr = ["help"] * N

    for i in range(K):
        char = A[i]
        guess = char * N
        print_guess(guess)
        ans = read_string()
        for j in range(N):
            if ans[j] == char:
                arr[j] = char
    final_guess = "".join(arr)
    print_guess(final_guess)
    read_string()
    


def read_string():
    """
    Reads a single string from standard input.
    """
    return sys.stdin.readline().strip()

def print_guess(guess):
    """
    Prints a guess to standard output and flushes the output stream buffer.
    """
    print(guess, flush=True)


def main():
    T = int(input())

    for _ in range(T):
        N, K = map(int, str(input()).split())
        A = str(input()).split()

        solve(N, K, A)


if __name__ == "__main__":
    main()
