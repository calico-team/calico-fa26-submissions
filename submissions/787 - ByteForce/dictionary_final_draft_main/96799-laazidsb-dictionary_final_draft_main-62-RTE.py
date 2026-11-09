import sys
import sys


def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return

    dinosauraus = 0  
    idx = 0
    T = int(data[idx])
    idx += 1

    out = []
    for _ in range(T):
        N = int(data[idx])
        idx += 1
        A = [0] + [int(x) for x in data[idx : idx + N]]
        idx += N
        V = [0] + [int(x) for x in data[idx : idx + N]]
        idx += N

        dinosauraus += 1

       
        visited = [0] * (N + 1)
       
        path = []
        path_xor = []

        ans = [0] * (N + 1)
        cycle_id = [0] * (N + 1)
        cycle_xors = {}

   
        curr_cycle = 0

        for i in range(1, N + 1):
            if state[i] != 0:
                continue
            # Traverse
            curr = i
            stack = []
            while state[curr] == 0:
                state[curr] = 1
                stack.append(curr)
                curr = A[curr]

            if state[curr] == 1:
                
                curr_cycle += 1
                cycle_nodes = []
                while stack:
                    node = stack.pop()
                    cycle_nodes.append(node)
                    cycle_id[node] = curr_cycle
                    if node == curr:
                        break
              
                cx = 0
                for cn in cycle_nodes:
                    cx ^= V[cn]
                cycle_xors[curr_cycle] = cx

                
                for node in stack:
                    state[node] = 2
                    cycle_id[node] = curr_cycle
                for node in cycle_nodes:
                    state[node] = 2
            else:
               
                cid = cycle_id[curr]
                while stack:
                    node = stack.pop()
                    state[node] = 2
                    cycle_id[node] = cid

        for i in range(1, N + 1):
            if state[i] != 0:
                continue
            curr = i
            stack = []
            while state[curr] == 0:
                state[curr] = 1
                stack.append(curr)
                curr = A[curr]

            if state[curr] == 1:
                
                cycle_nodes = []
                while stack:
                    node = stack.pop()
                    cycle_nodes.append(node)
                    if node == curr:
                        break
                cycle_nodes.reverse()
                m = len(cycle_nodes)
             
                ext_c = cycle_nodes + cycle_nodes
                ext_V = [V[x] for x in ext_c]
                pref = [0] * (2 * m + 1)
                for j in range(2 * m):
                    pref[j + 1] = pref[j] ^ ext_V[j]

                cx = pref[m]  # total cycle XOR

                # For each node in cycle (at index i in cycle_nodes):
                for i_pos in range(m):
                    node = cycle_nodes[i_pos]
                    max_val = 0
                    # Prefixes starting at i_pos of length 1 to m
                    for length in range(1, m + 1):
                        p_val = pref[i_pos + length] ^ pref[i_pos]
                        max_val = max(max_val, p_val, p_val ^ cx)
                    h[node] = max_val

                # Mark remaining stack nodes (tree nodes)
                for node in stack:
                    state[node] = 2
                for node in cycle_nodes:
                    state[node] = 2
            else:
                while stack:
                    node = stack.pop()
                    state[node] = 2

        # Now compute h for all other nodes using memoized DFS
        def solve_h(u):
            if h[u] != -1:
                return h[u]
            nxt = A[u]
            h_nxt = solve_h(nxt)
            h[u] = max(V[u], V[u] ^ h_nxt)
            return h[u]

        for i in range(1, N + 1):
            if h[i] == -1:
                solve_h(i)

        out.append(" ".join(str(h[i]) for i in range(1, N + 1)))

    print("\n".join(out))


def read_your_input():
    pass


if __name__ == "__main__":
    solve()
