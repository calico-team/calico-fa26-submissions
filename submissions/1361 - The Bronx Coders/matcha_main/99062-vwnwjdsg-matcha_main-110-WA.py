import sys

def compute_max_xor(count, low_arr, high_arr):
    fixed_xor = 0
    bucket_size = [0] * 30
    free_from_low = [0] * 30
    free_from_high = [0] * 30
    
    for idx in range(count):
        lo = low_arr[idx]
        hi = high_arr[idx]
        xor_diff = lo ^ hi
        
        if xor_diff == 0:
            fixed_xor ^= lo
            continue
            
        msb = xor_diff.bit_length() - 1
        lower_mask = (1 << msb) - 1
        upper_mask = ~((1 << (msb + 1)) - 1)
        
        fixed_xor ^= (lo & upper_mask)
        bucket_size[msb] += 1
        free_from_low[msb] |= (~lo) & lower_mask
        free_from_high[msb] |= hi & lower_mask
        
    best_total = 0
    unlocked_bits = 0
    
    for bit in range(29, -1, -1):
        current_bit = (fixed_xor >> bit) & 1
        k = bucket_size[bit]
        
        if k >= 2:
            best_total |= (1 << (bit + 1)) - 1
            break
        elif k == 1:
            best_total |= (1 << bit)
            if current_bit == 1:
                unlocked_bits |= free_from_low[bit]
            else:
                unlocked_bits |= free_from_high[bit]
        else:
            if current_bit == 1:
                best_total |= (1 << bit)
            elif (unlocked_bits >> bit) & 1:
                best_total |= (1 << (bit + 1)) - 1
                break
                
    return best_total

def run_matcha():
    tokens = sys.stdin.read().split()
    if not tokens:
        return
    
    pos = 0
    num_tests = int(tokens[pos])
    pos += 1
    results = []
    
    for _ in range(num_tests):
        days = int(tokens[pos])
        pos += 1
        
        l_list = [int(tokens[pos + i]) for i in range(days)]
        pos += days
        
        r_list = [int(tokens[pos + i]) for i in range(days)]
        pos += days
        
        results.append(str(compute_max_xor(days, l_list, r_list)))
        
    print("\n".join(results))

if __name__ == "__main__":
    run_matcha()