import sys

def solve_case_la():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    iterator = iter(input_data)
    num_test_cases = int(next(iterator))
    out = []
    
    for _ in range(num_test_cases):
        N = int(next(iterator))
        L = [0] * N
        for i in range(N):
            L[i] = int(next(iterator))
        R = [0] * N
        for i in range(N):
            R[i] = int(next(iterator))
            
        highest_diff_bit = -1
        for i in range(N):
            diff = L[i] ^ R[i]
            if diff > 0:
                bit_len = diff.bit_length() - 1
                if bit_len > highest_diff_bit:
                    highest_diff_bit = bit_len
        
        if highest_diff_bit == -1:
            ans = 0
            for i in range(N):
                ans ^= L[i]
            out.append(str(ans))
            continue
            
        ans = 0
        for i in range(N):
            ans ^= L[i]
        
        mask = (1 << (highest_diff_bit + 1)) - 1
        ans = (ans & ~mask) | mask
        
        out.append(str(ans))
        
    print('\n'.join(out))

if __name__ == '__main__':
    solve_case_la()
