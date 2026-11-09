# cook your dish here
import sys


def solve():
  input_data = sys.stdin.read().split()
  if not input_data:
    return

  iterator = iter(input_data)
  try:
    T = int(next(iterator))
  except StopIteration:
    return

  out = []
  for _ in range(T):
    try:
      N = int(next(iterator))
      L = [int(next(iterator)) for _ in range(N)]
      R = [int(next(iterator)) for _ in range(N)]
    except StopIteration:
      break

    t_L = [True] * N
    t_R = [True] * N
    ans = 0

    for bit in range(29, -1, -1):
      forced0 = []
      forced1 = []
      free = []

      for i in range(N):
        l_b = (L[i] >> bit) & 1
        r_b = (R[i] >> bit) & 1
        tl = t_L[i]
        tr = t_R[i]

        if not tl and not tr:
          free.append(i)
        elif tl and tr:
          if l_b == 0 and r_b == 0:
            forced0.append(i)
          elif l_b == 1 and r_b == 1:
            forced1.append(i)
          else:
            free.append(i)
        elif tl and not tr:  # LOW_TIGHT
          if l_b == 0:
            free.append(i)
          else:
            forced1.append(i)
        else:  # HIGH_TIGHT
          if r_b == 0:
            forced0.append(i)
          else:
            free.append(i)

      c1 = len(forced1)
      cf = len(free)

      d = 1 if (cf > 0 or c1 % 2 == 1) else 0
      if d == 1:
        ans |= 1 << bit

      x_f = (d - c1) % 2 if cf > 0 else 0

      # Update states for FORCED_0
      for i in forced0:
        tl = t_L[i]
        tr = t_R[i]
        if tl and tr:
          t_L[i] = True
          t_R[i] = True
        elif tl and not tr:
          t_L[i] = True
          t_R[i] = False
        else:
          t_L[i] = False
          t_R[i] = True

      # Update states for FORCED_1
      for i in forced1:
        tl = t_L[i]
        tr = t_R[i]
        if tl and tr:
          t_L[i] = True
          t_R[i] = True
        elif tl and not tr:
          t_L[i] = True
          t_R[i] = False
        else:
          t_L[i] = False
          t_R[i] = True

      # Update states for FREE intervals
      for j, i in enumerate(free):
        chosen_bit = 1 if j < x_f else 0
        tl = t_L[i]
        tr = t_R[i]
        l_b = (L[i] >> bit) & 1
        r_b = (R[i] >> bit) & 1

        if not tl and not tr:
          t_L[i] = False
          t_R[i] = False
        elif tl and tr:
          if chosen_bit == 0:
            t_L[i] = True
            t_R[i] = False
          else:
            t_L[i] = False
            t_R[i] = True
        elif tl and not tr:
          if chosen_bit == 0:
            t_L[i] = True
            t_R[i] = False
          else:
            t_L[i] = False
            t_R[i] = False
        else:
          if chosen_bit == 0:
            t_L[i] = False
            t_R[i] = False
          else:
            t_L[i] = False
            t_R[i] = True

    out.append(str(ans))

  sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
  solve()