import sys

def merafunction(N, R, A):
  paisy = 2
  agla = 0

  for t in A:
    while paisy < 2 and agla <= t:
      paisy += 1
      if paisy < 2:
        agla += R

    if paisy == 0:
      return "NO"

    if paisy == 2:
      agla = t + R

    paisy -= 1

  return "YES"


def main():
  banda = sys.stdin.read().split()
  if not banda:
    return
  T = int(banda[0].lstrip("\ufeff"))
  pos = 1
  out = []

  for _ in range(T):
    N = int(banda[pos])
    R = int(banda[pos + 1])
    pos += 2

    A = [int(x) for x in banda[pos : pos + N]]
    pos += N

    out.append(merafunction(N, R, A))
  sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
  main()