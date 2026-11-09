def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    initial_charges = 2
    next_charge= None

    for time in A:
        if next_charge is not None and time >= next_charge:
            status = min(2-initial_charges, (time-next_charge)//R+1)

            initial_charges +=status
            next_charge +=status*R


            if initial_charges ==2:
                next_charge=None

        if initial_charges ==0:
            return "NO"

        if initial_charges == 2:
            next_charge = time + R

        initial_charges-=1

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
