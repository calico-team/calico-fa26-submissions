def solve(N, R, A):
    # YOUR CODE HERE
    i = 0
    while (i < N-1):
        if A[i] + R > A[i+1]:
            return "NO"
        i += 1
        #print(i)
    return "YES"

# python smoke_template.py < 00_main.in

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
