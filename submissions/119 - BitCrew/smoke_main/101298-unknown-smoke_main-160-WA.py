def solve(N, R, A):
    c1 = 0
    c2 = 0
    
    for time in A:
     if time >= c1:
        c1 = max(time, c2) + R
        c2 = 0

     elif time >= c2 and c2 != 0:
        c2 = max(time, c2) + R

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
