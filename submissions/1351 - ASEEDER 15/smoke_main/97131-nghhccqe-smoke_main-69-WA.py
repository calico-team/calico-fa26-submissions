
"""
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
"""

t = int(input())
for i in range(t):
    n, r = map(int, input().split())
    a = list(map(int, input().split()))

    for j in range(n-1):
        # if j - 1 >= 0:
        #     if A[j] - A[j - 1] < r:
        #         flag = 1
        #         print('NO')
        #         break
        #     else:
        #         flag = 0
        current_elem, next_elem = a[j], a[j+1]
        if next_elem - current_elem < r:
            print("NO")
            break
    else:
        print('YES')
