def solve(N, R, A):
    recharging_queue = []
    head_pointer=0
    next_possible_start_time =0
    for t in A:
        while head_pointer < len(recharging_queue) and recharging_queue[head_pointer] <= t:
            head_pointer +=1
        if (len(recharging_queue)- head_pointer) >= 2:
            return "NO"

        cooldown_start_time = max(t, next_possible_start_time)
        cooldown_end_time = cooldown_start_time + R
        recharging_queue.append(cooldown_end_time)
        next_possible_start_time = cooldown_end_time

    
    return "YES"


def main():
    T = int(input())
    for _ in range(T):
        temp = input().split()
        N = int(temp[0])
        R = int(temp[1])
        A = list(map(int, input().split()))
        print(solve(N, R, A))


if __name__ == '__main__':
    main()
