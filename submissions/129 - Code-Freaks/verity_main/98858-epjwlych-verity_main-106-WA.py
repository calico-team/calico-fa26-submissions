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
    response_from_judge=""
    guess_string=""
    limit=100
    indexes=[]
    while True:

        for i in range(0,N):

            if i in indexes:
                guess_string=guess_string+response_from_judge[i]
            else:
                temp=random.choice(A)
                guess_string=guess_string+temp
        print_guess(guess_string)
        response_from_judge=read_string()
        indexes=[]

        if response_from_judge=="CORRECT":
            break
        for i in range(0,N):
            if response_from_judge[i]!="_":
                indexes.append(i)

        guess_string=""
        if limit==0:
            break
        limit=limit-1
    pass

def read_string():
    """
    Reads a single string from standard input.
    """
    s = input()
    return s

def print_guess(guess):
    """S
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
