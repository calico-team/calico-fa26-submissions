def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    smokes = 2
    time = 0

    cooldown = 0
    for x in A:

      while time < x:
        time += 1
        if time == cooldown and smokes < 2:
          smokes += 1
          if smokes < 2:
            cooldown = time + R #this for recharge so it keeps goin till the next recharge
       
      
      if smokes <= 0: 
        return "NO"
      if smokes == 2:
        cooldown = x + R 
      smokes -= 1
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
