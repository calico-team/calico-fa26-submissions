import sys

def solve():
    data = sys.stdin.read().split()
    if not data:
        return
    
    it = iter(data)
    t = int(next(it))
    
    out = []
    for _ in range(t):
        n = int(next(it))
        k = int(next(it))
        
        drones = []
        for _ in range(n):
            x = int(next(it))
            y = int(next(it))
            z = int(next(it))
            d = next(it)
            drones.append((x, y, z, d))
        
        total_rain = n * k
        loss = 0
        
        e_drones = [(d[0], d[1], d[2]) for d in drones if d[3] == 'E']
        n_drones = [(d[0], d[1], d[2]) for d in drones if d[3] == 'N']
        
        n_map = {}
        for xn, yn, zn in n_drones:
            s = xn + yn
            if s not in n_map:
                n_map[s] = []
            n_map[s].append((xn, yn, zn))
            
        for xe, ye, ze in e_drones:
            s = xe + ye
            if s in n_map:
                for xn, yn, zn in n_map[s]:
                    time = xn - xe
                    if 0 <= time < k:
                        if ze < zn:
                            loss += 1
                        elif zn < ze:
                            loss += 1
                            
        out.append(str(total_rain - loss))
        
    print('\n'.join(out))

if __name__ == '__main__':
    solve()