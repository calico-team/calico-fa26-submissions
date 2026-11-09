def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    answer = ["_"] * N
    for i in range(K):
        guess = A[i] * N
        print_guess(guess)
        output = read_string()
        
        if(output == "CORRECT"):
            break

        for j in range(len(output)):
            if(output[j] != "_"):
                answer[j] = output[j]

    print_array(answer)
    read_string()

    # YOUR CODE HERE
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

def print_array(arr):
    str = ""
    for i in arr:
        str += i

    print_guess(str)


def main():
    T = int(input())

    for _ in range(T):
        N, K = map(int, input().split())
        A = input().split()

        solve(N, K, A)


if __name__ == '__main__':
    main()
