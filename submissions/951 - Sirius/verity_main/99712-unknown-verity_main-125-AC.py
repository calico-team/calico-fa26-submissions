def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    count = 0
    final_answer = [''] * N

    for character in A:
        count+=1
        my_guess = character * N
        print_guess(my_guess)

        valuation = read_string()
        if valuation == 'CORRECT':
            return
    
        for char in range(N):
            if valuation[char] != '_':
                final_answer[char] = valuation[char]

    final_answer_str = ''.join(final_answer)
    count +=1
    print_guess(final_answer_str)
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
