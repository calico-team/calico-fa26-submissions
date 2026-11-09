def solve(N, R, A):
    final = True
    i = 0
    a = A
    while i < N:
        if a[i+1] - a[i] >= R:
            i += 1
            final = True
        else:
            print('NO')
            final = False
            break

        if final == True:
            print('YES')
            break

    return ""

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
