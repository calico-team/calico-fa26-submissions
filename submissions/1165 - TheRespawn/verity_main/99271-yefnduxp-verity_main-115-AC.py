def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    indices = [0] * N

    while True:
        guess = "".join(A[index] for index in indices)
        print_guess(guess)
        response = read_string()

        if response == "CORRECT":
            return

        if len(response) != N:
            raise ValueError("Invalid response received: {}".format(response))

        for i, character in enumerate(response):
            if character == "_":
                if indices[i] + 1 == K:
                    raise ValueError("No candidate characters remain at position {}".format(i))
                indices[i] += 1
            elif character != guess[i]:
                raise ValueError("Invalid response received: {}".format(response))
        
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
