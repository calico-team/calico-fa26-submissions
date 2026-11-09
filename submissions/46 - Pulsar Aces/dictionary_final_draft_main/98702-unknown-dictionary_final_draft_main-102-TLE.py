largenumber = 1000000
def solve():
    n = int(input())
    first = [int(i) - 1 for i in input().split()]
    vals = [int(i) for i in input().split()]
    out = []
    for i in range(n):
        seen = set()
        word = i
        happiness = 0
        maxhappiness = 0
        while not (largenumber * happiness + word) in seen:
            #print(word, vals[word], first[word])
            seen.add(largenumber * happiness + word)
            happiness ^= vals[word]
            word = first[word]
            maxhappiness = max(maxhappiness, happiness)
        out.append(maxhappiness)
    print(' '.join([str(i) for i in out]))

for i in range(int(input())): solve()