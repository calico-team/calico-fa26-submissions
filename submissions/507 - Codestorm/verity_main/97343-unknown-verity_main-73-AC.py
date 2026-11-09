
def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    # YOUR CODE HERE
    corr = set()
    guess = [A[0]] * N
    
    for j in range(K):
        for i in range(N):
            if i not in corr:
                guess[i] = A[(j + i) % K]
        print_guess("".join(guess))
        res = read_string()
        if res == "CORRECT":
            return
        for i in range(N):
            if res[i] != "_":
                guess[i] = res[i]
                corr.add(i)
                
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
