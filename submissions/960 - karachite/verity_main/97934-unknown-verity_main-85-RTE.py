from streamlit import feedback


def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    # YOUR CODE HERE
    result=['?']*N
    for letters in A:
        attemptes=''.join(result[ind] if result[ind]!='?' else letters
                          for ind in range(N)
                          )
        print_guess(attemptes)
        feedback=read_string().strip()
        if feedback=="Correct":
            return
        for ind in range(N):
            if feedback[ind]!='_':
                result[ind]=feedback[ind]
    print_guess(''.join(result))
    feedback=read_string().strip()
    if feedback=="Correct":
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
