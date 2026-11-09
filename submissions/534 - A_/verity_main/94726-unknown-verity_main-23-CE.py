def solve(N: int, K: int, A: list[str]) -> None:
  """
  Print a sequence of guesses until you guess the answer string.
  You may use the read_string() and print_guess() helper functions defined below.

  N: Length of the string
  K: Number of different -ities
  A: List containing the different -ities
  """
  guess = [_]*N
  for character in A:
      for i in range(N):
          if guess[i]=='_':
              guess[i]=character
      print_guess(''.join(map(str,guess))
      guess=list(read_string())
      if guess=['C','O','R','R'','E','C','T']:
          continue
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


def main():
  T = int(input())

  for _ in range(T):
      N, K = map(int, input().split())
      A = input().split()

      solve(N, K, A)


if __name__ == '__main__':
  main()
