def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    # YOUR CODE HERE
    answer_so_far=[]
    for i in range(N):
        answer_so_far.append("?")
    
    letter_num=0
    finished=False
    while finished==False and letter_num<K:
        current_letter = A[letter_num]
        guess=""
        for i in range(N):
            if answer_so_far[i]=="?":
                guess=guess+current_letter
            else:
                guess=guess+answer_so_far[i]
        print_guess(guess)
        result=read_string()

        if result=="CORRECT":
            finished=True
        else:
            for i in range(N):
                if result[i] != "_":
                    answer_so_far[i]=result[i]
            letter_num+=1

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
