def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you word_guessthe underScoreAnswerwer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    
    chars = "".join(A)
    
    
    underScoreAnswer = ['_'] * N
    
    for c in chars:
       
        word_guess= "".join([underScoreAnswer[i] if underScoreAnswer[i] != '_' else c for i in range(N)])
        
        
        print_guess(word_guess)
        
        
        judgeAnswer = read_string()
        
       
        if judgeAnswer == "CORRECT":
            return
            
        
        for c in range(N):
            if judgeAnswer[c] != '_':
                underScoreAnswer[c] = judgeAnswer[c]

def read_string():
    """
    Reads a single string from standard input.
    """
    s = input().strip()
    return s

def print_guess(guess):
    """
    Prints a word_guessto standard output and flushes the output stream buffer.
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