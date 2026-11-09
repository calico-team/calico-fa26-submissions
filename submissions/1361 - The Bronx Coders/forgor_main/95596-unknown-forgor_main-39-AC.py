import sys

def run_forgor():
    tokens = sys.stdin.read().split()
    if not tokens:
        return
    
    mode = tokens[0]
    num_nodes = int(tokens[1])
    MOD = 1000000
    
    if mode == "FIRST":
        graph = [[] for _ in range(num_nodes + 1)]
        pos = 2
        for _ in range(num_nodes - 1):
            a = int(tokens[pos])
            b = int(tokens[pos + 1])
            pos += 2
            graph[a].append(b)
            graph[b].append(a)
            
        par = [0] * (num_nodes + 1)
        par[num_nodes] = num_nodes
        stack = [num_nodes]
        
        while stack:
            node = stack.pop()
            for neighbor in graph[node]:
                if par[neighbor] == 0:
                    par[neighbor] = node
                    stack.append(neighbor)
                    
        recorded = [par[i] for i in range(1, num_nodes)]
        checksum = sum(recorded) % MOD
        recorded.append(checksum)
        
        print(*(recorded))
        
    else:
        values = [int(tokens[2 + i]) for i in range(num_nodes)]
        erased_idx = values.index(-1)
        
        if erased_idx < num_nodes - 1:
            known_sum = 0
            for i in range(num_nodes - 1):
                if i != erased_idx:
                    known_sum += values[i]
            values[erased_idx] = (values[num_nodes - 1] - known_sum) % MOD
            
        out_lines = [f"{i + 1} {values[i]}" for i in range(num_nodes - 1)]
        sys.stdout.write("\n".join(out_lines) + "\n")

if __name__ == "__main__":
    run_forgor()