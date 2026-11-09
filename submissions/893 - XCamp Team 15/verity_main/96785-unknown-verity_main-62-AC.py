
def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    # YOUR CODE HERE
    #A is letters in a list
    know=[None]*N
    for x in A:
        char=[]
        for i in range(N):
            if know[i]!=None:
                char.append(know[i])
            else:
                char.append(x)
        print_guess("".join(char))
        into=read_string()
        if into=="CORRECT":
            return
        for i in range(N):
            if into[i]!="_":
                know[i]=into[i]
                    
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
#this took me way too long :\
#One of our teamates are not here gng