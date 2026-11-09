
"""
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
"""
    
T = int(input())
for i in range(T):
    temp = input().split()
    N = int(temp[0])
    R = int(temp[1])
    A = list(map(int, input().split()))
    flag = 0
    for i in range(N):
        if i - 1 >= 0:
            if A[i] - A[i - 1] < R:
                flag = 1
                print( 'NO' )
                break
            else:
                flag = 0
    if flag == 0:
            print('YES')
