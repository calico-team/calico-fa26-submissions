def solve(N, R, A):
    available = [0, 0]

    for time in A:
     if time >= available[0]:
        available[0] = time + R

     elif time >= available[1]:
        available[1] = time + R   

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
