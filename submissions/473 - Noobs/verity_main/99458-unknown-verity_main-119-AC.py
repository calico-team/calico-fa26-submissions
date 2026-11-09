def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """

    found = ["_"] * N

    for letter in A:
        guess = ""
        
        for c in found:
            if c != "_":
                guess = guess + c
            else:
                guess = guess + letter

        print_guess(guess)

        reply = read_string().strip()
        if reply == "CORRECT":
            break

        for p in range(N):
            if reply[p] != "_":
                found[p] = reply[p]

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
