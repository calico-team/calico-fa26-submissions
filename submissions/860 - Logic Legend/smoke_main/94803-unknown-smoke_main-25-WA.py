# Source: https://usaco.guide/general/io
import heapq

def solve(N: int, R: int, A: list[int]) -> str:
    charges = 2
    recharging = []  # Min-heap to store times when charges finish recharging
    
    for time in A:
        # 1. Process recharges that finish at or before the current request time
        while recharging and recharging[0] <= time:
            heapq.heappop(recharging)
            charges += 1
            if charges > 2:
                charges = 2
        
        # 2. Check if we have an available charge
        if charges > 0:
            charges -= 1
            heapq.heappush(recharging, time + R)
        else:
            return "NO"
            
    return "YES"


def main():
    import sys
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    T = int(input_data[0])
    idx = 1
    for _ in range(T):
        N = int(input_data[idx])
        R = int(input_data[idx+1])
        idx += 2
        
        A = []
        for _ in range(N):
            A.append(int(input_data[idx]))
            idx += 1
            
        print(solve(N, R, A))

if __name__ == "__main__":
    main()
