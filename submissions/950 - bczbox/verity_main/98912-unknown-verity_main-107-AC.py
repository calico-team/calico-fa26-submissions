def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    # YOUR CODE HERE
    current = ["_"]*N
    for char in A:
        if "_" not in current:
            break


        # guess = []
        # for i in range(N):
        #     if current[i] != "_":
        #         guess.append(current[i])
        #     else:
        #         guess.append(char)

        guess_str = char*N
    
        # guess_str = "".join(guess)
        print_guess(guess_str)
        judge_feedback = read_string()

        if judge_feedback == "CORRECT":
            return
        
        for i in range(N):
            if judge_feedback[i] != "_":
                current[i] = judge_feedback[i]

    final_guess = "".join(current)
    print_guess(final_guess)
    final_feedback = read_string()
    if final_feedback == "CORRECT":
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
