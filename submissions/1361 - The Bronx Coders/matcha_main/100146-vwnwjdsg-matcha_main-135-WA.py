import sys

def maximize_flavors(days, low_list, high_list):
    fixed_xor = 0
    active_Left = []
    active_Right = []
    
    for i in range(days):
        lo = low_list[i]
        hi = high_list[i]
        if lo == hi:
            fixed_xor ^= lo
        else:
            active_Left.append(lo)
            active_Right.append(hi)
            
    result = 0
    num_active = len(active_Left)
    
    for bit in range(29, -1, -1):
        threshold = 1 << bit
        all_ones = (threshold << 1) - 1
        
        bit_xor = (fixed_xor >> bit) & 1
        straddling = -1
        can_fill_all = False
        
        for i in range(num_active):
            lo = active_Left[i]
            hi = active_Right[i]
            
            if lo == 0 and hi == all_ones:
                can_fill_all = True
                break
                
            if hi < threshold:
                continue
            elif lo >= threshold:
                bit_xor ^= 1
                active_Left[i] = lo - threshold
                active_Right[i] = hi - threshold
            else:
                if straddling != -1:
                    can_fill_all = True
                    break
                straddling = i
                
        if can_fill_all:
            result |= all_ones
            break
            
        if straddling != -1:
            result |= threshold
            if bit_xor == 1:
                active_Right[straddling] = threshold - 1
            else:
                active_Left[straddling] = 0
                active_Right[straddling] -= threshold
        elif bit_xor == 1:
            result |= threshold
            
    return result

def run_matcha():
    tokens = sys.stdin.read().split()
    if not tokens:
        return
    
    pos = 0
    total_cases = int(tokens[pos])
    pos += 1
    outputs = []
    
    for _ in range(total_cases):
        count = int(tokens[pos])
        pos += 1
        
        l_arr = [int(tokens[pos + j]) for j in range(count)]
        pos += count
        
        r_arr = [int(tokens[pos + j]) for j in range(count)]
        pos += count
        
        outputs.append(str(maximize_flavors(count, l_arr, r_arr)))
        
    print("\n".join(outputs))

if __name__ == "__main__":
    run_matcha()