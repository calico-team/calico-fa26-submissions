def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    # YOUR CODE HERE

    confirmed_correct = "_" * N

    print(f"A: {A}")

    for letter in A:
        guess = confirmed_correct
        # print(f"og guess: {guess}")
        guess = guess.replace("_", letter)

        # print('printing guess')
        print_guess(guess)

        feedback = read_string()

        if feedback == "CORRECT":
            return

        # print(f"confirmed: {confirmed_correct}")
        # print(f"feedback: {feedback}")

        for i in range(len(feedback)):
            if feedback[i] != "_":
                # confirmed_correct[i] = feedback[i]
                confirmed_correct = confirmed_correct[:i] + feedback[i] + confirmed_correct[i + 1:]
                # print(f"updated confirmed: {confirmed_correct}")

        # print(f"new confirmed: {confirmed_correct}")
    

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
