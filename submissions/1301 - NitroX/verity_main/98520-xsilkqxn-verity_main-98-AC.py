import random


def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    result = ["_"] * N
    remaining = set(range(N))

    for char in A:
        guess_chars = list(result)
        for i in remaining:
            guess_chars[i] = char

        guess = "".join(guess_chars)
        print_guess(guess)
        response = read_string()

        if response == "CORRECT":
            return

        # Lock revealed characters & remove solved indices from the set
        newly_solved = set()
        for idx in remaining:
            if response[idx] != "_":
                result[idx] = response[idx]
                newly_solved.add(idx)

        remaining -= newly_solved  # Remove solved positions

        # If all positions are solved early, stop guessing
        if not remaining:
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


if __name__ == "__main__":
    main()
