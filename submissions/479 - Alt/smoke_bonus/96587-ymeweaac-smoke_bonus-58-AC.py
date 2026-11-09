import sys

def problem_2bonus():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    iterator = iter(input_data)
    num_test_cases = int(next(iterator))
    results = []

    for _ in range(num_test_cases):
        num_requests = int(next(iterator))
        recharge_cooldown = int(next(iterator))
        
        timestamps = [int(next(iterator)) for _ in range(num_requests)]
        
        current_charges = 2
        next_recharge_time = float('inf')
        can_fulfill_all = True
        
        for current_time in timestamps:
            while current_charges < 2 and next_recharge_time <= current_time:
                current_charges += 1
                if current_charges < 2:
                    next_recharge_time += recharge_cooldown
                else:
                    next_recharge_time = float('inf')
            
            if current_charges > 0:
                current_charges -= 1
                if current_charges == 1:
                    next_recharge_time = current_time + recharge_cooldown
            else:
                can_fulfill_all = False
                break
                
        if can_fulfill_all:
            results.append("YES")
        else:
            results.append("NO")
            
    print('\n'.join(results))

if __name__ == '__main__':
    problem_2bonus()
