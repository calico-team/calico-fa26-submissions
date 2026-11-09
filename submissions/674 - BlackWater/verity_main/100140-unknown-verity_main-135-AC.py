def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    my_known_characters = list('_' * N)

    for i in range(K):
        my_guess_str = ""

        for j in range(N):

            if my_known_characters[j] == "_":
                my_guess_str += A[i]
            else:
                my_guess_str += my_known_characters[j]

        print_guess(my_guess_str)
        my_judge_response = read_string()

        if my_judge_response == "CORRECT":
            break
        for j in range(N):
            if my_judge_response[j] != "_":
                my_known_characters[j] = my_judge_response[j]
    

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
