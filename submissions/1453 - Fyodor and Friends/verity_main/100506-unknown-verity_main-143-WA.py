def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    # YOUR CODE HERE
   
    word = [""] * N
    ret = ["_"] * N
    num = 0

    while ret != "CORRECT":
        for i in range(N):
            if ret[i] == "_":
                word[i] = A[num]
        num+=1
        print_guess("".join(word))
        ret = read_string()
        
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
    T = int(2)

    for _ in range(T):
        N, K = map(int, "26 26".split())
        A = "A B C D E F G H I J K L M N O P Q R S T U V W X Y Z".split()

        solve(N, K, A)


if __name__ == '__main__':
    main()
