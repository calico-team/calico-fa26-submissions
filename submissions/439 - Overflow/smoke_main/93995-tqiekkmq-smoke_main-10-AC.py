import sys

def main():
    data = sys.stdin.buffer.read().split()
    pos = 0
    t = int(data[pos]); pos += 1
    out = []
    for _ in range(t):
        n, r = int(data[pos]), int(data[pos + 1]); pos += 2
        ok = True
        ready = 2            # charges available right now
        coming = 0           # when the FRONT recharging charge lands
        for i in range(n):
            now = int(data[pos + i])
            # recharges are processed before requests at the same timestamp
            while ready < 2 and coming <= now:
                ready += 1
                coming += r   # the charge behind it lands R seconds later
            if ready == 0:
                ok = False    # front charge arrives after this request
                break
            ready -= 1        # throw the smoke
            if ready:
                coming = now + r   # it becomes the only charge in flight
            # else it queues behind the front one: lands at coming + r, already implicit
        pos += n
        out.append("YES" if ok else "NO")
    print("\n".join(out))

main()