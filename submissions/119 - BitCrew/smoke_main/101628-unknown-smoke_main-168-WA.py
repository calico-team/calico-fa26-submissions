def solve(N, R, A):
    f1 = 0
    f2 = 0

    for time in A:
     if f1 <= time:
        if f2 <= time:
           f1 = f2 + R
        else:
           f1 = time + R

     elif f2 <= time:
        if f1 > time:
           f2 = f1 + R

        else:
           f2 = time + R

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
