import sys

t_cases = sys.stdin.readline().strip()
if not t_cases:
    sys.exit(0)

t = int(t_cases)
for i in range(t):
    n, e = [int(x) for x in sys.stdin.readline().split()]
    a = sys.stdin.readline().split()
    ans = ['_'] * n
    
    for c in a:
        g = "".join(ans[j] if ans[j] != '_' else c for j in range(n))
        
        print(g, flush=True)
        

        
        r = sys.stdin.readline().strip()
        if not r:
            break
      

        if r == "CORRECT":
            break
        



        for j in range(n):
            if j < len(r) and r[j] != '_':
                ans[j] = r[j]