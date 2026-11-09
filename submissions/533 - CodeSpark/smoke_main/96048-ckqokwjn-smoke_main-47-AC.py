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
        R = int(input_data[idx + 1])
        idx += 2
        
        times = []
        for _ in range(N):
            times.append(int(input_data[idx]))
            idx += 1
            
        charges = 2
        recharging = [] 
        possible = True
        
        for t in times:
            
            still_recharging = []
            for finish_time in recharging:
                if finish_time <= t:
                    charges += 1
                else:
                    still_recharging.append(finish_time)
            recharging = still_recharging
            
            if charges > 2:
                charges = 2
                
            if charges > 0:
                charges -= 1
                
                if len(recharging) == 0:
                    recharging.append(t + R)
                else:
                    recharging.append(recharging[-1] + R)
            else:
                possible = False
                break
                
        if possible:
            out.append("YES")
        else:
            out.append("NO")
            
    print("\n".join(out))

if __name__ == '__main__':
    solve()