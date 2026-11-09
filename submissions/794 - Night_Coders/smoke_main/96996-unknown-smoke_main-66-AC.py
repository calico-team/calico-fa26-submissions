def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    present = 2
    recharging = []

    for time in A:


        while recharging and recharging[0] <= time:

            recharging.pop(0)
            present += 1

        if present == 0:


            return "NO"
        present -= 1

        if present == 1:
            
            recharging.append(time +   R)
        else:
            recharging.append(recharging[-1]  + R)

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
