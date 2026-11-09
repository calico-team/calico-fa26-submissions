def solve(N, R, A):
    charge1 = 0
    charge2 = 0

    for time in A:
     if time >= charge1:
        charge1 = time + R

     elif time >= charge2:
        charge2 = time + R   

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
