N = int(input())

for _ in range(N):
    n_d, n_n = [int(i) for i in input().split()]
    pos = []

    for _ in range(n_d):
        str_pos = input().split()
        ot = [int(i) for i in str_pos[:3]]
        ot.append(str_pos[3])
        pos.append(ot)

    pos = sorted(pos, key=lambda x: x[2], reverse=True)

    tot = 0
    for night in range(n_n):
        tot_pos = set()
        for d in range(n_d):
            curr_pos = pos[d]
            tot_pos.add(tuple(curr_pos[:2]))
            if curr_pos[-1] == 'E':
                curr_pos[0] += 1
            else:
                curr_pos[1] += 1
            pos[d] = curr_pos
        tot += len(tot_pos)
    print(tot)

