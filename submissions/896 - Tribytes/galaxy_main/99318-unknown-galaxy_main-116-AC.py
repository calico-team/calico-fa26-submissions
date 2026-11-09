import sys


def word_feed():
    # Streams whitespace-separated words one input line at a time (low memory).
    for raw_line in sys.stdin:
        for word in raw_line.split():
            yield word


def launch():
    grab = word_feed().__next__
    scenarios = int(grab())
    verdicts = []
    for _ in range(scenarios):
        height = int(grab())
        width = int(grab())
        asks = int(grab())
        board = [grab() for _ in range(height)]
        area = height * width

        # flat colour table: 0 = neutral '.', 1 = blue 'B', 2 = red 'R'
        tint = [0] * area
        for y in range(height):
            line = board[y]
            base = y * width
            for x in range(width):
                ch = line[x]
                if ch == 'B':
                    tint[base + x] = 1
                elif ch == 'R':
                    tint[base + x] = 2

        # state id = phase * area + cell ; phase 0 = blue mode, phase 1 = red mode
        # a cell is usable in a phase if neutral, or colour matches the phase
        group = [-1] * (2 * area)
        total_groups = 0
        for phase in range(2):
            need = 1 if phase == 0 else 2
            for cell in range(area):
                start_state = phase * area + cell
                if group[start_state] != -1:
                    continue
                t0 = tint[cell]
                if t0 != 0 and t0 != need:
                    continue
                group[start_state] = total_groups
                pile = [start_state]
                while pile:
                    cur = pile.pop()
                    ph = cur // area
                    pos = cur - ph * area
                    need_now = 1 if ph == 0 else 2
                    yy = pos // width
                    xx = pos - yy * width
                    # walk to the four neighbours within the same phase
                    if yy > 0:
                        nb = pos - width
                        tn = tint[nb]
                        if (tn == 0 or tn == need_now) and group[ph * area + nb] == -1:
                            group[ph * area + nb] = total_groups
                            pile.append(ph * area + nb)
                    if yy < height - 1:
                        nb = pos + width
                        tn = tint[nb]
                        if (tn == 0 or tn == need_now) and group[ph * area + nb] == -1:
                            group[ph * area + nb] = total_groups
                            pile.append(ph * area + nb)
                    if xx > 0:
                        nb = pos - 1
                        tn = tint[nb]
                        if (tn == 0 or tn == need_now) and group[ph * area + nb] == -1:
                            group[ph * area + nb] = total_groups
                            pile.append(ph * area + nb)
                    if xx < width - 1:
                        nb = pos + 1
                        tn = tint[nb]
                        if (tn == 0 or tn == need_now) and group[ph * area + nb] == -1:
                            group[ph * area + nb] = total_groups
                            pile.append(ph * area + nb)
                    # spin: flip phase while standing on a neutral cell
                    if tint[pos] == 0:
                        other = (1 - ph) * area + pos
                        if group[other] == -1:
                            group[other] = total_groups
                            pile.append(other)
                total_groups += 1

        for _ in range(asks):
            sy = int(grab())
            sx = int(grab())
            ty = int(grab())
            tx = int(grab())
            src_group = group[sy * width + sx]          # start is neutral, blue mode
            goal = ty * width + tx
            goal_tint = tint[goal]
            if goal_tint == 0:
                good = (group[goal] == src_group) or (group[area + goal] == src_group)
            elif goal_tint == 1:
                good = group[goal] == src_group
            else:
                good = group[area + goal] == src_group
            verdicts.append("YES" if good else "NO")
    sys.stdout.write("\n".join(verdicts) + "\n")


launch()
