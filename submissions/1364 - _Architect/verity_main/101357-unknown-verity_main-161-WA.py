import sys


def solve():
  T = int(input())

  for _ in range(T):
    N, K = map(int, input().split())
    chars = input().split()

    # Start with a dummy guess using the first available character
    guess = [chars[0]] * N
    print("".join(guess))
    sys.stdout.flush()

    res = input().strip()
    if res == "CORRECT":
      continue

    # Figure out each character position one by one
    for i in range(N):
      if res[i] != "_":
        guess[i] = res[i]
        continue

      for c in chars:
        guess[i] = c
        print("".join(guess))
        sys.stdout.flush()

        res = input().strip()
        if res == "CORRECT":
          break
        if res[i] != "_":
          guess[i] = res[i]
          break

      if res == "CORRECT":
        break


if __name__ == "__main__":
  solve()