import sys
everything = sys.stdin.read().split()
cases = int(everything[0])
thing = 1
out = []
for _ in range(cases):
    n = int(everything[thing])
    k = int(everything[thing + 1])
    thing += 2
    drones = []
    for _ in range(n):
        x = int(everything[thing])
        y = int(everything[thing + 1])
        d = everything[thing + 3]
        thing += 4
        dx = 1 if d != "N" else 0
        dy = 1 if d == "N" else 0
        drones.append((x, y, dx, dy))
    rain = n
    for t in range(1, k):
        dm = set()
        for x, y, dx, dy in drones:
            dm.add((x + t * dx, y + t * dy))
        rain += len(dm)
    out.append(str(rain))
sys.stdout.write("\n".join(out) + "\n")