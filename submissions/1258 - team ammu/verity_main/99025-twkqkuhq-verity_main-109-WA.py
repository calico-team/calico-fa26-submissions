def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    possibles = [list(A) for _ in range(N)]

    while True: 
        guess = ""
        for position in range(N):
            guess += possibles[position][0]
        print_guess(guess)

        reply = read_string().strip()
        if reply == "CORECT":
            return
        
        for position in range(N):
            if reply[position] != "_":
                possibles[position] = [reply[position]]
            else:
                possibles[position].remove(guess[position])

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
