def solve(N, R, A):
    r = [0, 0]  # time when each charge becomes available
    
    for t in A:
        r.sort()
        
        if r[0] <= t:
            # Use the earliest available charge
            r[0] = t + R
        elif r[1] <= t:
            # Second charge available
            r[1] = t + R
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
