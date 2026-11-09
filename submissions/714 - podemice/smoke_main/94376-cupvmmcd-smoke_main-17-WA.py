def solve(num_reqs, times, recharge):
    smokes = 2
    last_time = None
    remaining_recharge = None
    for i in range(num_reqs):
        if smokes == 0:
            return "NO"
        smokes -= 1
        if remaining_recharge == None:
            last_time = times[i]
            remaining_recharge = 0
        else:
            smokes += (times[i] - last_time + remaining_recharge) // recharge
            remaining_recharge = (times[i] - last_time + remaining_recharge) % recharge
            if smokes >= 2:
                remaining_recharge = 0
                smokes = 2
        last_time = times[i]

    return "YES"



def main():
    T = int(input())
    for _ in range(T):
        n = input()
        times = list(map(int, input().split(" ")))
        N, R = n.split(" ")
        print(solve(int(N), times, int(R)))

main()
