import sys
def solution():
    dataa = sys.stdin.read().split()
    if not dataa:
        return
    
    iteration = iter(dataa)
    test = int(next(iteration))
    
    out = []
    for items in range(test):
        neo = int(next(iteration))
        rar = int(next(iteration))
        
        c_1 = 0
        c_2 = 0
        possible = True
        
        for items in range(neo):
            time = int(next(iteration))
            if not possible:
                continue
            
            if min(c_1, c_2) <= time:
                if c_1 <= c_2:
                    c_1 = max(time, c_2) + rar
                else:
                    c_2 = max(time, c_1) + rar
            else:
                possible = False
        
        if possible:
            out.append("YES")
        else:
            out.append("NO")
            
    print('\n'.join(out))

if __name__ == '__main__':
    solution()