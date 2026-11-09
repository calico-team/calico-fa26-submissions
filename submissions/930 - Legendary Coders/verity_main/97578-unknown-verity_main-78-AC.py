def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    # YOUR CODE HERE
    abc=['_']*N
    de=[0]*N

    while True:
        tuk=""

        for i in range(N):
            if abc[i] =='_':
                tuk+=A[de[i]]
            else:
                tuk+=abc[i]
        print_guess(tuk)
        res=read_string()

        if res=="CORRECT":
            break

        for i in range(N):
            if res[i]!='_':
                abc[i]=res[i]
            else:
                de[i]+=1
            



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