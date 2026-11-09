import sys
from collections import deque

def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]]) -> list[str]:
    """
    Return an array of Q strings, the i-th of which is "YES" if Big Ben can travel from start[i] to end[i], and "NO" otherwise.
    """
    
    results = []
    
    dr = [-1, 1, 0, 0]
    dc = [0, 0, -1, 1]
    
    
    memo = {}
    
    for i in range(Q):
        sr, sc = start[i]
        er, ec = end[i]
        
        
        if sr == er and sc == ec:
            results.append("YES")
            continue
            
        target_key = (er, ec)
        if target_key not in memo:
            num_states = N * M * 2
            visited = [False] * num_states
            queue = deque()
            
            target_blue = er * M * 2 + ec * 2 + 0
            queue.append(target_blue)
            visited[target_blue] = True
            
            if G[er][ec] == '.':
                target_red = er * M * 2 + ec * 2 + 1
                queue.append(target_red)
                visited[target_red] = True
                
            while queue:
                curr = queue.popleft()
                r = curr // (M * 2)
                rem = curr % (M * 2)
                c = rem // 2
                mode = rem % 2
                
                
                for d in range(4):
                    pr, pc = r - dr[d], c - dc[d]
                    if 0 <= pr < N and 0 <= pc < M:
                        ptile = G[pr][pc]
                        is_active = (ptile == '.') or (ptile == 'B' and mode == 0) or (ptile == 'R' and mode == 1)
                        if is_active:
                            p_state = pr * M * 2 + pc * 2 + mode
                            if not visited[p_state]:
                                visited[p_state] = True
                                queue.append(p_state)
                                
                if G[r][c] == '.':
                    p_mode = 1 - mode
                    p_state = r * M * 2 + c * 2 + p_mode
                    if not visited[p_state]:
                        visited[p_state] = True
                        queue.append(p_state)
                        
            memo[target_key] = visited
            
        visited_from_target = memo[target_key]
        start_state = sr * M * 2 + sc * 2 + 0
        if visited_from_target[start_state]:
            results.append("YES")
        else:
            results.append("NO")
            
    return results

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    T = int(input_data[0])
    idx = 1
    for _ in range(T):
        N = int(input_data[idx])
        M = int(input_data[idx+1])
        Q = int(input_data[idx+2])
        idx += 3
        
        G = []
        for _ in range(N):
            G.append(input_data[idx])
            idx += 1
            
        start, end = [], []
        for _ in range(Q):
            start_row = int(input_data[idx])
            start_col = int(input_data[idx+1])
            end_row = int(input_data[idx+2])
            end_col = int(input_data[idx+3])
            idx += 4
            start.append((start_row, start_col))
            end.append((end_row, end_col))
            
        outputs = solve(N, M, Q, G, start, end)
        for out in outputs:
            print(out)

if __name__ == '__main__':
    main()
