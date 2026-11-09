import sys
from bisect import bisect_left, bisect_right

def solve():
   
    input_data = sys.stdin.read().split()
    if not input_data:
        return    
    T = int(input_data[0])
    idx = 1  
    out = []
    for _ in range(T):
        N = int(input_data[idx])
        K = int(input_data[idx+1])
        idx += 2
        
        groups_E = {}
        groups_N = {}
        for _ in range(N):
            X = int(input_data[idx])
            Y = int(input_data[idx+1])
            Z = int(input_data[idx+2])
            D = input_data[idx+3]
            idx += 4
            
            S = X + Y
            if D == 'E':
                if S not in groups_E:
                    groups_E[S] = []
                groups_E[S].append(X)
            else:
                if S not in groups_N:
                    groups_N[S] = []
                groups_N[S].append(X)
                
        blocked_count = 0
        
        for S in groups_N:
            if S in groups_E:
                e_list = sorted(groups_E[S])
                for xn in groups_N[S]:
                   
                    left_bound = xn - K + 1
                    right_bound = xn - 1
                    
                    if left_bound <= right_bound:
                       
                        l_idx = bisect_left(e_list, left_bound)
                        r_idx = bisect_right(e_list, right_bound)
                        blocked_count += max(0, r_idx - l_idx)
                        
        total_water = N * K - blocked_count
        out.append(str(total_water))
        
    print('\n'.join(out))

if __name__ == '__main__':
    solve()