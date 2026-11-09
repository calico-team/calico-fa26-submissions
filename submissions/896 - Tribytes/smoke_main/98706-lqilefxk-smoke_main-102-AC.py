import sys
from collections import deque


def can_serve(cooldown, times):
    pending = deque()   # moments when used charges become ready again
    ready_at = 0        # moment the latest scheduled recharge finishes
    for now in times:
        while pending and pending[0] <= now:
            pending.popleft()
        if len(pending) == 2:
            return "NO"
        ready_at = (now if now > ready_at else ready_at) + cooldown
        pending.append(ready_at)
    return "YES"


def run():
    tokens = sys.stdin.read().split()
    pos = 0
    cases = int(tokens[pos]); pos += 1
    answers = []
    for _ in range(cases):
        count = int(tokens[pos]); cooldown = int(tokens[pos + 1]); pos += 2
        times = [int(x) for x in tokens[pos:pos + count]]
        pos += count
        answers.append(can_serve(cooldown, times))
    sys.stdout.write("\n".join(answers) + "\n")


run()
