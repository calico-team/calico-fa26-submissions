import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    it = iter(input_data)
    t = int(next(it))
    out = []
    
    for _ in range(t):
        n = int(next(it))
        a = [int(next(it)) - 1 for _ in range(n)]
        v = [int(next(it)) for _ in range(n)]
        
       
        ans = [0] * n
        
        for i in range(n):
            path_vals = []
            curr_node = i
            max_h = 0
            val = 0
         
            limit = min(n * 2 + 5, n * 2)
            for _ in range(limit):
                x = v[curr_node]
                path_vals.append(x)
                val ^= x
                if val > max_h:
                    max_h = val
                curr_node = a[curr_node]
                
            ans[i] = max_h
            
        out.append(" ".join(map(str, ans)))
        
    print("\n".join(out))

if __name__ == '__main__':
    solve()