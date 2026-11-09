def solve(N, R, A):
    
    recharge=[0,0]
    for j in A:
        if recharge[0] >j:
            return "NO"
        recharge[0]=max(recharge[0],j)+R
        recharge.sort()
            
        
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
