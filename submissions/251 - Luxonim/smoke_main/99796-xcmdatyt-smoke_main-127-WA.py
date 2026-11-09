import sys

def solve():
    try:
        t = int(input())
    except EOFError:
        return
        
    out = []
    
    for _ in range(t):
        n, r = map(int, input().split())
        times = list(map(int, input().split()))
        
        current_charges = 2
        recharge_ready_time = 0
        ok = True
        
        for req in times:
            if current_charges > 0:
                current_charges -= 1
                if current_charges == 0:
                    recharge_ready_time = req + r
            else:
                if req >= recharge_ready_time:
                    recharge_ready_time += r
                else:
                    ok = False
                    break
                    
        if ok:
            out.append("YES")
        else:
            out.append("NO")
            
    print('\n'.join(out))

if __name__ == '__main__':
    solve()