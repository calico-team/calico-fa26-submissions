def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    # YOUR CODE HERE
    knownChar = [None] * N

    for currentChar in A:
        guessStr = []

        for i in range(N):
            if knownChar[i] is not None:
                guessStr.append(knownChar[i])
            else:
                guessStr.append(currentChar)

        guessStr = "".join(guessStr)

        print_guess(guessStr)

        judgeResponse = read_string()

        if judgeResponse == "CORRECT":
            return

        for i in range(N):
            if judgeResponse[i] != "_":
                guessStr[i] = judgeResponse[i]

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
