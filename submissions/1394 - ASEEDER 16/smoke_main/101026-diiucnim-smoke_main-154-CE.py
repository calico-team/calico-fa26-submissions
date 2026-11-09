def solve(N, R, A):

    # N: Number of smoke requests
    # R: Number of seconds needed for a smoke charge to recharge
    # A: List of timestamps where smokes are requested
    smoke = A.split()
    for i in range smoke:
        single = smoke(temp[i])
        next = smoke(temp[i+1])
	if next - single >  R:
    	     return false
    return true


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
