import sys
from bisect import bisect_left, bisect_right
from collections import defaultdict


def kul_barish(drones, raatein):
    # x+y ke hisaab se group: sirf same diagonal wale E aur N drones mil sakte hain
    east = defaultdict(list)
    north = defaultdict(list)
    for x, y, z, d in drones:
        (east if d == "E" else north)[x + y].append(x)
    milaap = 0
    for s, n_list in north.items():
        if s not in east:
            continue
        e_list = sorted(east[s])
        for xn in n_list:
            
            milaap += bisect_right(e_list, xn) - bisect_left(e_list, xn - (raatein - 1))
    return len(drones) * raatein - milaap


def main():
    data = sys.stdin.buffer.read().split()
    i = 0
    t = int(data[i]); i += 1
    out = []
    for _ in range(t):
        n, k = int(data[i]), int(data[i + 1]); i += 2
        drones = []
        for _ in range(n):
            drones.append((int(data[i]), int(data[i + 1]), int(data[i + 2]), data[i + 3].decode()))
            i += 4
        out.append(str(kul_barish(drones, k)))
    print("\n".join(out))


if __name__ == "__main__":
    main()