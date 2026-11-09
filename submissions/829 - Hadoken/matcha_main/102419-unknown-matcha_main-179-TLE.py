import sys

def solve():

    input_data_finder = sys.stdin.read().split()
    if not input_data_finder:
        return
        
    iterator = iter(input_data_finder)
    T = int(next(iterator))
    out = []
    
    for nope in range(T):
        N = int(next(iterator))
        L_arr = [int(next(iterator)) for _ in range(N)]
        R_arr = [int(next(iterator)) for _ in range(N)]

        D = [L_arr[i] ^ R_arr[i] for i in range(N)]
        Base = 0
        for x in L_arr:
            Base ^= x

        pref = [None] * N
        curr_b = [0] * 30
        basis_indices = set()
        
        for i in range(N):
            x = D[i]
            if x:
                for bit in range(29, -1, -1):
                    if (x >> bit) & 1:
                        if not curr_b[bit]:
                            curr_b[bit] = x
                            basis_indices.add(i)
                            break
                        x ^= curr_b[bit]

            pref[i] = list(curr_b)

        suff = [None] * N
        curr_b = [0] * 30
        for i in range(N - 1, -1, -1):
            x = D[i]
            if x:
                for bit in range(29, -1, -1):
                    if (x >> bit) & 1:
                        if not curr_b[bit]:
                            curr_b[bit] = x
                            break
                        x ^= curr_b[bit]
            suff[i] = list(curr_b)

        global_basis = pref[N - 1]

        special_bases = {}
        for i in basis_indices:
            b_excl = [0] * 30
            # Merge prefix basis
            if i > 0:
                for x in pref[i - 1]:
                    if x:
                        curr_x = x
                        for bit in range(29, -1, -1):
                            if (curr_x >> bit) & 1:
                                if not b_excl[bit]:
                                    b_excl[bit] = curr_x
                                    break
                                curr_x ^= b_excl[bit]
            # Merge suffix basis
            if i < N - 1:
                for x in suff[i + 1]:
                    if x:
                        curr_x = x
                        for bit in range(29, -1, -1):
                            if (curr_x >> bit) & 1:
                                if not b_excl[bit]:
                                    b_excl[bit] = curr_x
                                    break
                                curr_x ^= b_excl[bit]
            special_bases[i] = b_excl
            
        ans = Base
        val = Base

        for bit in range(29, -1, -1):
            if not ((val >> bit) & 1):
                if global_basis[bit]:
                    val ^= global_basis[bit]
        if val > ans:
            ans = val
            

        for i in range(N):
            L = L_arr[i]
            R = R_arr[i]
      
            M = D[i].bit_length() - 1 
            if M < 0:
                continue # L == R, no room to deviate
                
            curr_basis = special_bases[i] if i in basis_indices else global_basis
            
            # Check all valid bits strictly below the split where we can safely deviate
            for k in range(M):
                
                # Check deviation branching from L_i
                if not ((L >> k) & 1):
                    # Mask everything below k, and forcefully flip bit k to 1
                    P_C = ((L >> k) << k) ^ (1 << k)
                    
                    # Compute starting XOR sum removing standard L_i and inserting deviated P_C
                    val = Base ^ L ^ P_C
                    
                    # Greedily maximize higher bits using the available other intervals
                    for bit in range(29, k - 1, -1):
                        if not ((val >> bit) & 1):
                            if curr_basis[bit]:
                                val ^= curr_basis[bit]
                                
                    # Fill all bits below k with guaranteed 1s
                    cand = ((val >> k) << k) | ((1 << k) - 1)
                    if cand > ans:
                        ans = cand
                        
                # Check deviation branching from R_i
                if ((R >> k) & 1):
                    # Mask everything below k, and forcefully flip bit k to 0
                    P_C = ((R >> k) << k) ^ (1 << k)
                    
                    val = Base ^ L ^ P_C
                    
                    for bit in range(29, k - 1, -1):
                        if not ((val >> bit) & 1):
                            if curr_basis[bit]:
                                val ^= curr_basis[bit]
                                
                    cand = ((val >> k) << k) | ((1 << k) - 1)
                    if cand > ans:
                        ans = cand
                        
        out.append(str(ans))
        
    # Output all answers separated by newlines
    print('\n'.join(out))

if __name__ == '__main__':
    solve()