def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.
  
    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    ans = ['_'] * N
    for c in A:
      guess = c * N
      print_guess(guess)
      val = read_string()
      if val == "CORRECT":
        return
      val = val.ljust(N, '_')
      for i in range(N):
        if val[i] == c:
          ans[i] = c
    final_guess = "".join(ans)
    print_guess(final_guess)
    val = read_string()
    if val == "CORRECT":
      return
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