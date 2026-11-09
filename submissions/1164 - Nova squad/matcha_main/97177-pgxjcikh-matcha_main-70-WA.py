import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    T = int(input_data[0])
    idx = 1
    
    out = []
    for _ in range(T):
        N = int(input_data[idx])
        idx += 1
        
        L = [int(x) for x in input_data[idx : idx + N]]
        idx += N
        R = [int(x) for x in input_data[idx : idx + N]]
        idx += N
        
        dp = {0: -1}  # current_xor_sum: max_free_bit
        
        for i in range(N):
            l, r = L[i], R[i]
            if l == r:
                new_dp = {}
                for xor_val, free_b in dp.items():
                    new_dp[xor_val ^ l] = max(new_dp.get(xor_val ^ l, -2), free_b)
                dp = new_dp
            else:
                diff = l ^ r
                msb = diff.bit_length() - 1
                
                prefix_mask = ~((1 << (msb + 1)) - 1)
                common_prefix = l & prefix_mask
                
                new_dp = {}
                for xor_val, free_b in dp.items():
                    v1 = xor_val ^ common_prefix ^ (1 << msb)
                    f1 = max(free_b, msb - 1)
                    new_dp[v1] = max(new_dp.get(v1, -2), f1)
                    
                    v0 = xor_val ^ common_prefix
                    f0 = max(free_b, msb - 1)
                    new_dp[v0] = max(new_dp.get(v0, -2), f0)
                    
                pruned = {}
                for xor_val, free_b in new_dp.items():
                    if free_b not in pruned or xor_val > pruned[free_b]:
                        pruned[free_b] = xor_val
                
                dp = {v: k for k, v in pruned.items()}

        ans = 0
        for xor_val, free_b in dp.items():
            if free_b >= 0:
                mask = (1 << (free_b + 1)) - 1
                candidate = (xor_val | mask)
            else:
                candidate = xor_val
            ans = max(ans, candidate)
            
        out.append(str(ans))

    print('\n'.join(out))

if __name__ == '__main__':
    solve()