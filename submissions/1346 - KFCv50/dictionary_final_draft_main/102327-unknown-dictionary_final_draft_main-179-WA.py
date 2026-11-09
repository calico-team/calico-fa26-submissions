MAX_BIT = 30

def insert(base, x):
    for b in range(MAX_BIT, -1, -1):
        if (x >> b) & 1:
            if base[b] == 0:
                base[b] = x
                break
            else:
                x ^= base[b]

def get_max(base, x):
    res = x
    for b in range(MAX_BIT, -1, -1):
        if base[b] and (res ^ base[b]) > res:
            res ^= base[b]
    return res

def main():
    import sys
    input = sys.stdin.read().split()
    ptr = 0
    N = int(input[ptr])
    ptr += 1
    A = [0]*(N+1)
    V = [0]*(N+1)
    for i in range(1, N+1):
        A[i] = int(input[ptr])
        V[i] = int(input[ptr+1])
        ptr += 2
    
    vis = [0]*(N+1) # 0未访问 1访问中 2已处理
    ans = [0]*(N+1)
    
    for u in range(1, N+1):
        if vis[u] != 0:
            continue
        path = []
        cur = u
        while True:
            if vis[cur] == 1:
                # 找到环：从cur在path里的位置开始是环
                idx = path.index(cur)
                cycle = path[idx:]
                chain = path[:idx]
                
                # 计算环前缀异或
                cyc_xor = []
                s = 0
                for node in cycle:
                    s ^= V[node]
                    cyc_xor.append(s)
                # 建环线性基
                base = [0]*(MAX_BIT+1)
                for val in cyc_xor:
                    insert(base, val)
                # 环上每个点答案
                s = 0
                for node in cycle:
                    s ^= V[node]
                    ans[node] = get_max(base, s)
                    vis[node] = 2
                # 处理链（反向，从靠近环往外面）
                s = 0
                # 链是从起点到环入口，顺序：chain[0] -> chain[1] -> ... -> chain[-1] -> cycle[0]
                # 倒着遍历
                for node in reversed(chain):
                    s ^= V[node]
                    ans[node] = get_max(base, s)
                    vis[node] = 2
                break
            if vis[cur] == 2:
                # 当前路径走到已经处理好的点
                s = 0
                # 这条path全部是树链，通向已经处理好的节点
                for node in reversed(path):
                    s ^= V[node]
                    ans[node] = get_max(base, s)
                    vis[node] = 2
                break
            vis[cur] = 1
            path.append(cur)
            cur = A[cur]
    for i in range(1, N+1):
        print(ans[i])

if __name__ == "__main__":
    main()
