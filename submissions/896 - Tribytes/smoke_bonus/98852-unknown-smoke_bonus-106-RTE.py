import sys
from collections import deque


def check_round(gap, moments):
    busy = deque()      # when each spent charge will be back
    last_back = 0       # when the most recently queued recharge completes
    for moment in moments:
        while busy and busy[0] <= moment:
            busy.popleft()
        if len(busy) >= 2:
            return "NO"
        start = moment if moment > last_back else last_back
        last_back = start + gap
        busy.append(last_back)
    return "YES"


def entry():
    words = sys.stdin.buffer.read().split()
    cursor = 0
    rounds = int(words[cursor])
    cursor += 1
    results = []
    for _ in range(rounds):
        total = int(words[cursor])
        gap = int(words[cursor + 1])
        cursor += 2
        moments = [int(w) for w in words[cursor:cursor + total]]
        cursor += total
        results.append(check_round(gap, moments))
    sys.stdout.write("\n".join(results) + "\n")


entry()
