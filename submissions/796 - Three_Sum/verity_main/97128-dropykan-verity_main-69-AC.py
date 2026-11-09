import sys


def iqra_tester():
  input_data = sys.stdin
  output_data = sys.stdout

  line = input_data.readline()
  if not line:
    return

  total_tests = int(line.strip())

  for _ in range(total_tests):
    n, k = map(int, input_data.readline().split())
    words = input_data.readline().split()

    pos = [0] * n
    locked = [False] * n

    while True:
      guess = "".join(words[i] for i in pos)
      output_data.write(guess + "\n")
      output_data.flush()

      jawab = input_data.readline().strip()
      if not jawab or jawab == "CORRECT":
        break

      for i in range(n):
        if not locked[i]:
          if jawab[i] == "_":
            pos[i] += 1
          else:
            locked[i] = True


if __name__ == "__main__":
  iqra_tester()