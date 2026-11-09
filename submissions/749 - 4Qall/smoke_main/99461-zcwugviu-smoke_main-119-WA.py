def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    charges = 2
    next_recharge_time = None
    i = 0
    for time in A:
      i += 1
      while next_recharge_time != None and next_recharge_time <= time:
        charges += 1
        if charges < 2:
          next_recharge_time += R
        else:
          next_recharge_time = None

      if charges > 0:
        charges -= 1
        if next_recharge_time is None and i+1 <= len(A):
          next_recharge_time = A[i]-A[i-1]
        else:
          next_recharge_time = 0
      else:
        return "NO"
      return "YES"


def main():
    T = int(input())
    for _ in range(T):
        temp = input().split()
        N = int(temp[0])
        R = int(temp[1])
        A = list(map(int, input().split()))
        print(solve(N, R, A))


if __name__ == '__main__':
    main()
