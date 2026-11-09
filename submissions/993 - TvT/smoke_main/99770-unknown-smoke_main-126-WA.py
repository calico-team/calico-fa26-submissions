def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE

    first_smoke =  1
    second_smoke = 1
    time = 0

    for _ in range(N):
        if _ == 0:
            first_smoke = 0
            time = 0
            continue

        elapsed = A[_] - A[_-1]
 
        recharges = elapsed // R
        time = elapsed % R + time

        if time >= R:
            recharges += time//R
            time = time % R

        for i in range (min(recharges,2)):
            if first_smoke == 0:
                first_smoke = 1
            elif second_smoke == 0:
                second_smoke = 1


        if first_smoke == 1 :
            first_smoke = 0
            
        elif (first_smoke == 0 and second_smoke == 1):
            second_smoke = 0
            
        else: 
            return "NO"
        
        
    return "YES"



def main():
    T = int(input())
    results = []
    for _ in range(T):
        temp = input().split()
        N = int(temp[0])
        R = int(temp[1])
        A = list(map(int, input().split()))
        results.append(solve(N, R, A))
    print('\n'.join(results))


if __name__ == '__main__':
    main()
