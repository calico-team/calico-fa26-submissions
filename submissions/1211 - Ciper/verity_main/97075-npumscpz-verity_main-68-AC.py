def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    # YOUR CODE HERE
    data = [''] * N

    for chr in A:
        char_list = []
        for i in range(N):
            if data[i] != '':
                char_list.append(data[i])
            else:
                char_list.append(chr)
        
        guess = "".join(char_list)
        print_guess(guess)
        
        respns = read_string().strip()
        if respns == "CORRECT":
            return
        
        for i in range(min(N, len(respns))):
            if respns[i] != '_':
                data[i] = respns[i]
    

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
