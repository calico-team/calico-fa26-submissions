import random

def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    # YOUR CODE HERE
    while True:
        string = ["_" for i in range(N)]
        guess = []
        previousGuess = [["_"] for i in range(N)]
        while True:
            for i in range(N):
                if string[i] == "_":
                    letter = A[random.randint(0, K-1)]
                    while letter in previousGuess[i]:
                        letter = A[random.randint(0, K-1)]
                    guess.append(letter)
                else:
                    guess.append(string[i])
            print_guess("".join(guess))
            response = read_string()
            if response == "CORRECT":
                return
            else:
                for i in range(len(guess)):
                    previousGuess[i].append(guess[i])
                string = response
                guess = []



        
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
