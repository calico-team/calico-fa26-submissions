def solve(N, R, A):
    recharge1 = 0
    recharge2 = 0
    for t in A:
        if t<recharge1:
            return "NO"
        recharge1, recharge2 = recharge2, max(t, recharge2) + R
    return "YES"
    
    
def main():
    T= int(input())
    for _ in range(T):
        N, R = map(int, input().split())
        A= list(map(int, input().split()))
        print(solve(N, R, A))
        
        
if __name__ == "__main__":
    main()