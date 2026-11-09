
def solve(N: int, K: int, A: list[str]) -> None:
    """
    Output guesses until the hidden string is found.
    """

    answer = ["_"] * N

    for char in A:

        guess = ""

        for i in range(N):
            if answer[i] == "_":
                guess += char
            else:
                guess += answer[i]

        print_guess(guess)

        response = read_string()

        if response == "CORRECT":
            return

        for i in range(N):
            if response[i] != "_":
                answer[i] = response[i]

    # Final guess using all discovered characters
    print_guess("".join(answer))

    response = read_string()


def read_string():
    """
    Reads a single string from standard input.
    """
    s = input()
    return s


def print_guess(guess):
    """
    Prints a guess and flushes the output buffer.
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
