def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.

    Strategy: for each possible character, guess a string made entirely of it
    (keeping already-known positions). The judge reveals every position equal
    to that character. After cycling through all K characters every position is
    known, so a final full guess is correct. At most K + 1 <= 27 guesses.
    """
    known = [None] * N

    for c in A:
        if all(x is not None for x in known):
            break
        guess = ''.join(known[i] if known[i] is not None else c for i in range(N))
        print_guess(guess)
        resp = read_string()
        if resp == "CORRECT":
            return
        for i in range(N):
            if resp[i] != '_':
                known[i] = resp[i]

    # Every position is known now; submit the reconstructed string.
    guess = ''.join(known[i] if known[i] is not None else A[0] for i in range(N))
    print_guess(guess)
    resp = read_string()
    # resp == "CORRECT"; return to proceed to the next test case.


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
