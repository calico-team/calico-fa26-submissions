def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    allcharge =2

    prepared =0

    for c in A:

        while allcharge <2 and prepared <=c:
            allcharge +=1

            if allcharge < 2:

                prepared +=R 

        if allcharge == 0:
            return "NO"
        
        if allcharge == 2:

            prepared = c + R

        allcharge -=1     

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
