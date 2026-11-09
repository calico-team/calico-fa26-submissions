N = int(input())

for _ in range(N):
    n_d, n_n = [int(i) for i in input().split()]
    pos = []

    for _ in range(n_d):
        str_pos = input().split()
        ot = [int(i) for i in str_pos[:-1]]
        ot.append(str_pos[-1])
        pos.append(ot)

    pos = sorted(pos, key=lambda x: x[-2], reverse=True)

    tot = []

    for night in range(n_n):
        tot.append(set())
        for d in range(n_d):
            curr_pos = pos[d]

            tot[night].add(tuple(curr_pos[:2]))

            if curr_pos[-1] == 'E':
                curr_pos[0] += 1
            else:
                curr_pos[1] += 1
            pos[d] = curr_pos
    print(sum([len(a) for a in tot]))

