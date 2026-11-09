# cook your dish here
import sys
from collections import deque

def solve(n: int, r: int, a: list[int]) -> str:
    available_charges = 2
    recharging_queue = deque()
    
    for current_time in a:
        # Free up any charges that have finished recharging by the current request time
        while recharging_queue and recharging_queue[0] <= current_time:
            recharging_queue.popleft()
            available_charges = min(2, available_charges + 1)
            
        if available_charges == 0:
            return "NO"
            
        available_charges -= 1
        
        # Smokes recharge sequentially
        if not recharging_queue:
            finish_time = current_time + r
        else:
            finish_time = recharging_queue[-1] + r
            
        recharging_queue.append(finish_time)
        
    return "YES"

def main():
    # Read from stdin
    raw_input = sys.stdin.read().split()
    
    # Fallback for testing: if stdin is empty or got polluted with non-integers, 
    # use the sample input so it doesn't crash.
    if not raw_input or not raw_input[0].isdigit():
        # Sample input fallback
        sample_input = """5
5 10
20 30 40 50 60
7 100
1 2 3 4 5 6 7
4 10
1 2 12 13
8 5
5 10 17 30 36 45 50 56
9 30
20 70 80 90 100 190 210 220 250"""
        raw_input = sample_input.split()

    num_test_cases = int(raw_input[0])
    pointer = 1
    results = []
    
    for _ in range(num_test_cases):
        n = int(raw_input[pointer])
        r = int(raw_input[pointer + 1])
        pointer += 2
        
        a = [int(raw_input[pointer + i]) for i in range(n)]
        pointer += n
            
        ans = solve(n, r, a)
        results.append(ans)
            
    print('\n'.join(results))

if __name__ == '__main__':
    main()