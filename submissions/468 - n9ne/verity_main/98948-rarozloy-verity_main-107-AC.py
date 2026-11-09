def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    known = ['_'] * N

    for c in A:
        guess = ''.join(known[i] if known[i] != '_' else c for i in range(N))
        print_guess(guess)
        r = read_string()
        if r == "CORRECT":
            return
        
        for i in range(N):
            if r[i] != '_':
                known[i] = r[i]


def read_string():
    s = input()
    return s

def print_guess(guess):
    print(guess, flush=True)


def main():
    T = int(input())

    for _ in range(T):
        N, K = map(int, input().split())
        A = input().split()

        solve(N, K, A)


if __name__ == '__main__':
    main()