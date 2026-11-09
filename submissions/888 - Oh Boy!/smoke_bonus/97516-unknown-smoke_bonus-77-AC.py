def solve(N, R, A):
    smokeTimer = R*2
    valid = True
    for i in range(len(A)):
        if smokeTimer < (R*2):
            smokeTimer += A[i]-A[i-1]
            if smokeTimer > R*2:
                smokeTimer = R*2
        if smokeTimer < R:
            valid = False
        smokeTimer -= R
    if valid == False:
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
