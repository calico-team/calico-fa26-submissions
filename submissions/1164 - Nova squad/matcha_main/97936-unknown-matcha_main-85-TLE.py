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
        
        # DP state over bit positions from MSB (29) down to 0
        # For each day i, state can be:
        # 0: bounded by both L_i and R_i
        # 1: bounded by R_i only (L_i bound broken)
        # 2: bounded by L_i only (R_i bound broken)
        # 3: FREE (both bounds broken)
        
        # We track valid combinations of (states_tuple) -> max XOR prefix
        dp = {tuple([0] * N): 0}
        
        for bit in range(29, -1, -1):
            new_dp = {}
            bit_val = 1 << bit
            
            for states, curr_xor in dp.items():
                # If any day is FREE (state 3), all lower bits can be forced to 1
                if any(s == 3 for s in states):
                    res = curr_xor | ((1 << (bit + 1)) - 1)
                    new_dp[states] = max(new_dp.get(states, -1), res)
                    continue
                
                # Build possible bit choices for each day at position `bit`
                day_options = []
                for i, s in enumerate(states):
                    l_b = (L[i] >> bit) & 1
                    r_b = (R[i] >> bit) & 1
                    
                    opts = []
                    if s == 0:  # Bounded by both
                        if l_b == r_b:
                            opts.append((l_b, 0))
                        else:  # l_b = 0, r_b = 1
                            opts.append((0, 2))  # Pick 0 -> bounded by L_i
                            opts.append((1, 1))  # Pick 1 -> bounded by R_i
                    elif s == 1:  # Bounded by R_i
                        if r_b == 1:
                            opts.append((0, 3))  # Pick 0 -> FREE
                            opts.append((1, 1))  # Pick 1 -> bounded by R_i
                        else:
                            opts.append((0, 1))  # Pick 0 -> bounded by R_i
                    elif s == 2:  # Bounded by L_i
                        if l_b == 0:
                            opts.append((1, 3))  # Pick 1 -> FREE
                            opts.append((0, 2))  # Pick 0 -> bounded by L_i
                        else:
                            opts.append((1, 2))  # Pick 1 -> bounded by L_i
                    
                    day_options.append(opts)
                
                # Branch over all valid daily choices for this bit position
                def explore(day_idx, xor_bit_acc, next_s_list):
                    if day_idx == N:
                        next_states = tuple(next_s_list)
                        val = curr_xor | (xor_bit_acc << bit)
                        if val > new_dp.get(next_states, -1):
                            new_dp[next_states] = val
                        return
                    
                    for b_val, nxt_s in day_options[day_idx]:
                        next_s_list.append(nxt_s)
                        explore(day_idx + 1, xor_bit_acc ^ b_val, next_s_list)
                        next_s_list.pop()
                
                explore(0, 0, [])
            
            # Prune states: if multiple state tuples have a day at state 3, keep max XOR
            pruned_dp = {}
            free_max = -1
            free_state = None
            
            for st, val in new_dp.items():
                if any(s == 3 for s in st):
                    if val > free_max:
                        free_max = val
                        free_state = st
                else:
                    if st not in pruned_dp or val > pruned_dp[st]:
                        pruned_dp[st] = val
            
            if free_state is not None:
                pruned_dp[free_state] = free_max
                
            dp = pruned_dp
        
        ans = max(dp.values())
        out.append(str(ans))

    print('\n'.join(out))

if __name__ == '__main__':
    solve()