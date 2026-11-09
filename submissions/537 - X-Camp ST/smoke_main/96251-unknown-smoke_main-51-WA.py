def solve(n, r, a):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    have = 2
    can = True

    i = 0
    time = 0

    while i < n:

      if r > a[0]:
        print('NO')
        can = False
        break

      time += r
      if have == 2:
        have += 0
      elif have < 2:
        have += 1

      if time >= a[i]:
        if have <= 0:
          print('NO')
          can = False
          break
        else:
          have -= 1
          time = 0
          i += 1

    if can:
      print('YES')
      return ""


def main():
    T = int(input())
    for _ in range(T):
        temp = input().split()
        N = int(temp[0])
        R = int(temp[1])
        A = list(map(int, input().split()))
        solve(N, R, A)


if __name__ == '__main__':
    main()