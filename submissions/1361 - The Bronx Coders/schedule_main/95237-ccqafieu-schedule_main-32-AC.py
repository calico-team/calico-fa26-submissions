import sys
from collections import deque


def level_sizes(courses, prereq):
    kids = [[] for _ in range(courses + 1)]
    for c in range(1, courses + 1):
        kids[prereq[c]].append(c)
    sizes = []
    frontier = deque(kids[0])
    while frontier:
        sizes.append(len(frontier))
        for _ in range(len(frontier)):
            node = frontier.popleft()
            frontier.extend(kids[node])
    return sizes


def best_count(courses, semesters, cap, prereq):
    taken = 0
    limit = None
    for lvl, size in enumerate(level_sizes(courses, prereq)):
        room = cap * (semesters - lvl) + taken
        limit = room if limit is None else min(limit, room)
        if taken + size > limit:
            return limit
        taken += size
    return taken


def run():
    tokens = iter(sys.stdin.buffer.read().split())
    answers = []
    for _ in range(int(next(tokens))):
        courses = int(next(tokens))
        semesters = int(next(tokens))
        cap = int(next(tokens))
        prereq = [0] * (courses + 1)
        for c in range(1, courses + 1):
            prereq[c] = int(next(tokens))
        answers.append(str(best_count(courses, semesters, cap, prereq)))
    print("\n".join(answers))


if __name__ == "__main__":
    run()
