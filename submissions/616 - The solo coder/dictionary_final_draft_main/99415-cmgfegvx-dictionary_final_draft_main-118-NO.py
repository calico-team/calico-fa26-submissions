import sys

def solve():
    # Open the input.txt file to read data directly
    try:
        with open('input.txt', 'r') as file:
            input_data = file.read().split()
    except FileNotFoundError:
        return

    if not input_data:
        return
    
    t = int(input_data[0])
    idx = 1
    
    for _ in range(t):
        n = int(input_data[idx])
        r = int(input_data[idx+1])
        idx += 2
        
        requests = []
        for i in range(n):
            requests.append(int(input_data[idx+i]))
        idx += n
        
        # Omen starts with 2 smoke charges
        available_smokes = 2
        
        # Queue to store the exact time when the NEXT smoke will be fully recharged
        recharge_queue = []
        
        possible = True
        
        for time in requests:
            # Step 1: Process recharges that have finished by the current time
            while recharge_queue and recharge_queue[0] <= time:
                recharge_queue.pop(0)
                available_smokes += 1
            
            # Step 2: If a smoke is available, use it
            if available_smokes > 0:
                available_smokes -= 1
                
                # Step 3: Calculate when this smoke will finish recharging
                if not recharge_queue:
                    # If no smoke is currently recharging, it starts right now
                    recharge_queue.append(time + r)
                else:
                    # If one is already recharging, this one ONLY starts recharging 
                    # when the previous one is fully restored.
                    # So, it finishes at (previous finish time + r)
                    recharge_queue.append(recharge_queue[-1] + r)
            else:
                # No smoke available, cannot fulfill the request
                possible = False
                break
                
        if possible:
            print("YES")
        else:
            print("NO")

if __name__ == "__main__":
    solve()