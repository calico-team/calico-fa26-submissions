import sys
def solve_smoke(N, R, A):
    t1 = 0
    t2 = 0
    
    for t in A:
        if t >= t1:
            next_recharge = max(t, t2) + R
            t1 = t2
            t2 = next_recharge
        else:
            return "NO"
            
    return "YES"
def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    iterator = iter(input_data)
    T = int(next(iterator))
    for _ in range(T):
        N = int(next(iterator))
        R = int(next(iterator))
        A = []
        for _ in range(N):
            A.append(int(next(iterator))) 
        print(solve_smoke(N, R, A))
if __name__ == "__main__":
    main()
