import sys

SAMPLE = """5
5 10
20 30 40 50 60
7 100
1 2 3 4 5 6 7
4 10
1 2 12 13
8 5
5 10 17 30 36 45 50 56
9 30
20 70 80 90 100 190 210 220 250
"""

if len(sys.argv) > 1 and sys.argv[1] == "test":
    text = SAMPLE
else:
    text = sys.stdin.read()

data = text.split()
pos = 0
t = int(data[pos])
pos += 1

for _ in range(t):
    n = int(data[pos])
    r = int(data[pos + 1])
    pos += 2
    requests = data[pos:pos + n]
    pos += n

    charges = 2   
    ready = 0     
    ok = True

    for x in requests:
        a = int(x)

        while charges < 2 and ready <= a:
            charges += 1
            if charges < 2:
                ready += r

        if charges == 0:
            ok = False
            break

        if charges == 2:
            ready = a + r
        charges -= 1

    print("YES" if ok else "NO")