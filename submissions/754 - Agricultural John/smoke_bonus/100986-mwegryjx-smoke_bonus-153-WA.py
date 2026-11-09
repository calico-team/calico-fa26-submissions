def solve(N, R, A):
    recharge1= 0
    recharge2= 0
    for t in A:
        if t>=recharge1:
            recharge1 = t + R
        elif t>=recharge2:
            recharge2 = t + R
        else:
            return "NO"
    return "YES"
def main():
    T = int(input())
    for _ in range(T):
        N, R = map(int,input().split())
        A = list(map(int, input().split()))
        print(solve(N, R, A))

if __name__ == "__main__":
    main()