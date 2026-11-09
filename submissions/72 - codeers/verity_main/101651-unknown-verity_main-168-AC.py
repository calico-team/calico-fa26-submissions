def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    # YOUR CODE HERE
    ans = ['_'] * N

    for c in A:
        guess = ''.join(
            ans[i] if ans[i]
 != '_'
    else c
            for i in range(N)        
            )
        print_guess(guess)

        response = read_string()
        if response == "CORRECT":
            return
        for i in range(N):
            if response[i] != '_':
                ans[i] = response[i]

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
