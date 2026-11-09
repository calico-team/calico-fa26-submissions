def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    # YOUR CODE HERE
    rem = ["_"]*N
    solved = False
    for letter in A:
        print_guess(letter*N)
        ans=read_string()

        if ans == "CORRECT":
            solved=True
            break
        else:
             for i in range(N):
                 if ans[i] != "_":
                    rem[i]=ans[i]
        
        if "_" not in rem:
           break
    if not solved:
         print_guess("".join(rem))
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
