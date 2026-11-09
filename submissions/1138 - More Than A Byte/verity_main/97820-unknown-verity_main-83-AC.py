def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    ans = ['?'] * N

    for b in A:
        guess = ''.join(ans[i] if ans[i] != '?' else b for i in range(N))
        
        print_guess(guess)
        res = read_string()

        if res == 'CORRECT':
            return

        for i in range(N):
            if res[i] != '_':
                ans[i] = res[i]
    pass

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
