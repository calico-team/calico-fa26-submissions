def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """

    # YOUR CODE HERE
    corrects = [''] * N
    for i in range(K):
        guess = A[i] * N
        print_guess(guess)
        response = read_string()
        if response == "CORRECT":
            return
        for j, char in enumerate(response):
            if char == A[i]: #guessed correct for i'th -ity in j'th prosiition
                corrects[j] = char
        
    print_guess(''.join(corrects))
    if read_string() == "CORRECT":
        return

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
