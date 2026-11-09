import sys

def solve():
    data = sys.stdin.read().split()
    
    if not data:
        return

    T = int(data[0])
    idx = 1
    out = []

    for _ in range(T):
        N = int(data[idx])
        R = int(data[idx + 1])
        idx += 2

        A = list(map(int, data[idx:idx + N]))
        idx += N

        
        recharge_times = []
        possible = True

        for t in A:
            
            while recharge_times and recharge_times[0] <= t:
                recharge_times.pop(0)

           
            if len(recharge_times) == 2:
                possible = False
                break

          
            if recharge_times:
                recharge_times.append(recharge_times[-1] + R)
            else:
                recharge_times.append(t + R)

        if possible:
            out.append("YES")
        else:
            out.append("NO")

    print("\n".join(out))


if _name_ == "_main_":
    solve()
