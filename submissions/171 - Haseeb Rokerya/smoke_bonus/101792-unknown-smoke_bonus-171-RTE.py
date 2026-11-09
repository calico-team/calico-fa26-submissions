# cook your dish here
import sys
from collections import deque

def solve(n: int, r: int, a: list[int]) -> str:
    available_charges = 2
    recharging_queue = deque()
    
    for current_time in a:
        while recharging_queue and recharging_queue[0] <= current_time:
            recharging_queue.popleft()
            available_charges = min(2, available_charges + 1)
            
        if available_charges == 0:
            return "NO"
            
        available_charges -= 1
        
        if not recharging_queue:
            finish_time = current_time + r
        else:
            finish_time = recharging_queue[-1] + r
            
        recharging_queue.append(finish_time)
        
    return "YES"

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    # Handle files starting directly with N and R (single test case)
    if len(input_data) > 1 and len(input_data) == int(input_data[0]) + 2:
        input_data.insert(0, '1')

    num_test_cases = int(input_data[0])
    pointer = 1
    results = []
    
    for _ in range(num_test_cases):
        n = int(input_data[pointer])
        r = int(input_data[pointer + 1])
        pointer += 2
        
        a = []
        for _ in range(n):
            a.append(int(input_data[pointer]))
            pointer += 1
            
        ans = solve(n, r, a)
        results.append(ans)
        
    print('\n'.join(results))

if __name__ == '__main__':
    main()