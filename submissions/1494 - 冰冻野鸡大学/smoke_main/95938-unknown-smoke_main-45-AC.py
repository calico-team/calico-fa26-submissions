def solve(N, R, A):
    c = 2
    t = 0
    for x in A:
        while c < 2 and t <= x:
            c += 1
            if c < 2:
                t += R
        if c == 0:return "NO"
        if c == 2:
            t = x + R
        c -= 1
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
