import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    iterator = iter(input_data)
    T = int(next(iterator))
    
    out = []
    for _ in range(T):
        N = int(next(iterator))
        L = [int(next(iterator)) for _ in range(N)]
        R = [int(next(iterator)) for _ in range(N)]
        
        current_intervals = [(L[i], R[i], True, True) for i in range(N)]
        
        ans = 0
        for bit in range(29, -1, -1):
            forced_1 = 0
            forced_0 = 0
            flex = 0
            
            next_intervals_if_0 = []
            next_intervals_if_1 = []
            
            can_0 = True
            can_1 = True
            
            for l, r, tight_l, tight_r in current_intervals:
                lb = (l >> bit) & 1
                rb = (r >> bit) & 1
                
                if tight_l and tight_r and l == r:
                    val = lb
                    if val == 0:
                        forced_0 += 1
                        next_intervals_if_0.append((l, r, True, True))
                        next_intervals_if_1.append(None)
                    else:
                        forced_1 += 1
                        next_intervals_if_0.append(None)
                        next_intervals_if_1.append((l, r, True, True))
                elif tight_l and tight_r and l_prefix_match(l, r, bit):
                    if lb == 0 and rb == 1:
                        flex += 1
                        next_intervals_if_0.append((l, r, True, False))
                        next_intervals_if_1.append((l, r, False, True))
                    elif lb == 0 and rb == 0:
                        forced_0 += 1
                        next_intervals_if_0.append((l, r, True, True))
                        next_intervals_if_1.append(None)
                    else:
                        forced_1 += 1
                        next_intervals_if_0.append(None)
                        next_intervals_if_1.append((l, r, True, True))
                else:
                    if tight_l and not tight_r:
                        if lb == 1:
                            forced_1 += 1
                            next_intervals_if_0.append(None)
                            next_intervals_if_1.append((l, r, True, False))
                        else:
                            flex += 1
                            next_intervals_if_0.append((l, r, True, False))
                            next_intervals_if_1.append((l, r, False, False))
                    elif not tight_l and tight_r:
                        if rb == 0:
                            forced_0 += 1
                            next_intervals_if_0.append((l, r, False, True))
                            next_intervals_if_1.append(None)
                        else:
                            flex += 1
                            next_intervals_if_0.append((l, r, False, False))
                            next_intervals_if_1.append((l, r, False, True))
                    else:
                        flex += 1
                        next_intervals_if_0.append((l, r, False, False))
                        next_intervals_if_1.append((l, r, False, False))
            
            p0 = forced_1 % 2
            p1 = (forced_1 + 1) % 2
            
            can_achieve_1 = False
            if flex > 0:
                can_achieve_1 = True
            else:
                if p1 == 1:
                    can_achieve_1 = True
                else:
                    can_achieve_1 = False
            
            if can_achieve_1:
                ans |= (1 << bit)
                
                new_ints = []
                for idx, interval in enumerate(current_intervals):
                    if next_intervals_if_1[idx] is not None:
                        new_ints.append(next_intervals_if_1[idx])
                    else:
                       
                        pass
                
            else:
                ans |= (0 << bit)
                
        out.append(str(ans))
        
    print('\n'.join(out))

def l_prefix_match(l, r, bit):
    return (l >> (bit + 1)) == (r >> (bit + 1))

if __name__ == '__main__':
    solve()