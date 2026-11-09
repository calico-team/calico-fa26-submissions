def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    confirmed_letters = [None] * N 

    for candidate_letter in A:
        current_guess = "".join( confirmed_letters[pos] if confirmed_letters[pos] else candidate_letter for pos in range(N) ) # build the current guess
        print_guess(current_guess)

        judge_reply = read_string().strip()

        if judge_reply == "CORRECT":
            return

        for pos in range(N): # If judge_reply[pos] is not an underscore, it means the letter at that position is correct, so save it in confirmed_letters.
            if judge_reply[pos] != "_":
                confirmed_letters[pos] = current_guess[pos]

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
