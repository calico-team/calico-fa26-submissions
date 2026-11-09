def solve(N, R, A):
   
    c1 = -1
    c2 = -1

    for t in A:
        
        if t < c1:
            return "NO"
        
        c3 = max(t, c2) + R
        c1, c2 = c2, c3

    return "YES"  


def main():
    T = int(input())

    for _ in range(T):
        N, R = map(int, input().split())
        A = list(map(int, input().split()))

        print(solve(N, R, A))


if __name__ == '__main__':
    main()

    


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
