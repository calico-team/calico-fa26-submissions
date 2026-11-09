def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    secret_characters = random_randint(1,100)
    guess = 100
    hidden_string = "### Hidden string ### "
    print(f"Welcome! We need to guess the scret_number b/w 1 and 100. you have {guess} attempts.")

    for attempts in range ( 1, guess+1):
        try:
            guess = int(f"input[{attempts}/{guess}] Enter your guess:")
        except ValueError:
            print("Invalid Input. Enter valid number.")
            continue
    if guess == secret_characters:
        print(f"CORRECT")
    else:
        print(f"respond with{hidden_string}")
    for guess in range(N):
        if hidden_string != "_":
            print(f"_")
        
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
