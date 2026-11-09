def solve(N: int, M: int, K: int, P: list[int]) -> int:
    bachay = [[] for _ in range(N + 1)]
    for i in range(1, N + 1):
        bachay[P[i - 1]].append(i)

    order = [0]
    i = 0
    while i < len(order):
        order.extend(bachay[order[i]])
        i += 1

    l_i = [1] * (N + 1)
    for j in range(len(order) - 1, -1, -1):
        v = order[j]
        hv = l_i[v]
        for c in bachay[v]:
            if l_i[c] >= hv:
                hv = l_i[c] + 1
        l_i[v] = hv

    max_h = max(l_i[1:])
    b_t = [[] for _ in range(max_h + 1)]
    for c in bachay[0]:
        b_t[l_i[c]].append(c)

    top = max_h
    r_y = len(bachay[0])
    total = 0
    for _ in range(M):
        while top > 0 and not b_t[top]:
            top -= 1
        if top == 0:
            break
        l_y = min(K, r_y)
        t_n , u_d = 0 , []
        h = top
        while t_n < l_y:
            b = b_t[h]
            while b and t_n < l_y:
                u_d.extend(bachay[b.pop()])
                t_n += 1
            h -= 1
        total += t_n
        r_y += len(u_d) - t_n
        for c in u_d:
            b_t[l_i[c]].append(c)

    return total

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()