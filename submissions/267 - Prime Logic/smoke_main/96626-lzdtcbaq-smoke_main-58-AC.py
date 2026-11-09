def solve(N, R,A):
    smokes = 2
    recharge = 0
    for t in A:
        while smokes <2 and recharge<=t:
            smokes += 1
            recharge += R
        if smokes == 0:
            return "NO"
        if smokes == 2:
            recharge = t + R
        smokes -= 1
    return "YES"

def main():
    T = int(input())
    for _ in range(T):
        N,R = map(int, input().split())
        A = list(map(int, input().split()))
        print(solve(N,R,A))

if __name__ == "__main__":
    main()