def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    # YOUR CODE HERE
    temp = [""] * N
    
    for char in A:
        guess = N * char
        print_guess(guess)
        judge_reply = read_string()
        if judge_reply == "CORRECT":
            return
        else:
            position = 0
            for c in judge_reply:
                if c != "_":
                    temp[position] = c
                    position += 1
                else:
                    position += 1
    
    print_guess("".join(temp))
    read_string()
        
    

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
