def solve(N: int, K: int, A: list[str]) -> None:
    solved = False
    guess = "_" * N
    counter = 0
    while solved == False and counter <= K:
        for i in range(N):
            if guess[i] == "_":
                guess = guess[:i]+A[counter]+guess[i+1:]
        print_guess(guess)
        judgeAnswer = read_string()
        if judgeAnswer == "CORRECT":
            solved = True
        counter += 1
        guess = judgeAnswer
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
