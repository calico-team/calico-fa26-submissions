def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # Dono charges ki use time track karo
    # -infinity matlab "abhi tak use nahi hua" (available hai)
    used = [-10**18, -10**18]
    
    for t in A:
        # Charge 1 kab ready hoga?
        charge1_ready = used[0] + R
        
        # Charge 2 kab ready hoga?
        # Sequential rule: Charge 2 tab tak wait karta hai jab tak charge 1 recharge na ho
        charge2_ready = max(used[0] + R, used[1]) + R
        
        if charge1_ready <= t:
            # Charge 1 available hai, use karo
            used[0] = t
        elif charge2_ready <= t:
            # Charge 2 available hai, use karo
            used[1] = t
        else:
            # Koi charge available nahi
            return "NO"
        
        # used[0] hamesha pehle wala hona chahiye
        if used[0] > used[1]:
            used[0], used[1] = used[1], used[0]
    
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
