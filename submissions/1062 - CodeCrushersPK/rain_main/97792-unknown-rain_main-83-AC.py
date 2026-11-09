def solve(N: int, K: int, L: list):
    total_pani = N * K
    drones_ka_group = {}
    for drone in L:
        x, y, z, simt = drone
        s_sum = x + y
        if s_sum not in drones_ka_group:
            drones_ka_group[s_sum] = {'E': [], 'N': []}
        drones_ka_group[s_sum][simt].append(x)
    for s_sum, simtain in drones_ka_group.items():
        east_waly_drones = sorted(simtain['E'])
        upr_waly_drones = sorted(simtain['N'])
        for mashriq_x in east_waly_drones:
            min_x = mashriq_x + 1
            max_x = mashriq_x + K - 1
            l, r = 0, len(upr_waly_drones)
            while l < r:
                mid = (l + r) // 2
                if upr_waly_drones[mid] < min_x:
                    l = mid + 1
                else:
                    r = mid
            left_index = l
            l, r = 0, len(upr_waly_drones)
            while l < r:
                mid = (l + r) // 2
                if upr_waly_drones[mid] <= max_x:
                    l = mid + 1
                else:
                    r = mid
            right_index = l
            takkar_ki_ginti = right_index - left_index
            total_pani -= takkar_ki_ginti
    return total_pani

def main():
    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        L = []
        for _ in range(N):
            X, Y, Z, D = input().split()
            L.append((int(X), int(Y), int(Z), D))

        print(solve(N, K, L))

if __name__ == '__main__':
    main()