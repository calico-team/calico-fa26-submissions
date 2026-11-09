import sys

def problem2():
    input_data = sys.stdin.read().split()
    
    if not input_data:
        return

    testcases = int(input_data[0])
    idx = 1
    
    output_results = []
    for _ in range(testcases):
        num_requests = int(input_data[idx])
        recharge_time = int(input_data[idx+1])
        idx += 2
        
        timestamps = [int(x) for x in input_data[idx : idx + num_requests]]
        idx += num_requests
        
        charges = 2
        restore_times = []
        possible = True
        
        for t in timestamps:
            while restore_times and restore_times[0] <= t:
                charges += 1
                restore_times.pop(0)
                
            if charges == 0:
                possible = False
                break
                
            charges -= 1
            
            if len(restore_times) == 0:
                restore_times.append(t + recharge_time)
            else:
                restore_times.append(restore_times[0] + recharge_time)
                
        if possible:
            output_results.append("YES")
        else:
            output_results.append("NO")
            
    sys.stdout.write('\n'.join(output_results) + '\n')

if __name__ == '__main__':
    problem2()
