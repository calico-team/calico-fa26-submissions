def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    # YOUR CODE HERE
    ans = [""] * N
    countFound = 0
    randomGuessed = False
    for character in set(A):
        print_guess(character*N)
        feedback = read_string()
        if feedback == "CORRECT":
            randomGuessed = True
            break
        else:
            for index in range(N):
                if feedback[index] != '_':
                    ans[index] = feedback[index]
                    countFound += 1
            if countFound == N:
                break
    if not randomGuessed:
        print_guess("".join(ans))
        read_string()

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
