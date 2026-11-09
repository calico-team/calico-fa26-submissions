import sys


def chunks():
    # yields input words lazily, one physical line at a time
    for text_row in sys.stdin:
        for piece in text_row.split():
            yield piece


def program():
    fetch = chunks().__next__
    cases_left = int(fetch())
    replies = []
    while cases_left > 0:
        cases_left -= 1
        rows = int(fetch())
        cols = int(fetch())
        qty = int(fetch())
        sheet = [fetch() for _ in range(rows)]
        cells = rows * cols

        # kind[i]: 0 = plain, 1 = blue, 2 = red   (i = row * cols + col)
        kind = [0] * cells
        for ri in range(rows):
            for ci in range(cols):
                symbol = sheet[ri][ci]
                if symbol == 'B':
                    kind[ri * cols + ci] = 1
                elif symbol == 'R':
                    kind[ri * cols + ci] = 2

        # node = mode * cells + i  (mode 0 = blue world, mode 1 = red world)
        label = [-1] * (2 * cells)
        counter = 0
        for mode in range(2):
            wanted = mode + 1
            for i in range(cells):
                node0 = mode * cells + i
                if label[node0] != -1:
                    continue
                k0 = kind[i]
                if k0 != 0 and k0 != wanted:
                    continue
                label[node0] = counter
                todo = [node0]
                while todo:
                    node = todo.pop()
                    md = 1 if node >= cells else 0
                    idx = node - md * cells
                    want = md + 1
                    shift = md * cells
                    r_ = idx // cols
                    c_ = idx - r_ * cols
                    if r_ > 0:
                        j = idx - cols
                        kj = kind[j]
                        if (kj == 0 or kj == want) and label[shift + j] == -1:
                            label[shift + j] = counter
                            todo.append(shift + j)
                    if r_ + 1 < rows:
                        j = idx + cols
                        kj = kind[j]
                        if (kj == 0 or kj == want) and label[shift + j] == -1:
                            label[shift + j] = counter
                            todo.append(shift + j)
                    if c_ > 0:
                        j = idx - 1
                        kj = kind[j]
                        if (kj == 0 or kj == want) and label[shift + j] == -1:
                            label[shift + j] = counter
                            todo.append(shift + j)
                    if c_ + 1 < cols:
                        j = idx + 1
                        kj = kind[j]
                        if (kj == 0 or kj == want) and label[shift + j] == -1:
                            label[shift + j] = counter
                            todo.append(shift + j)
                    if kind[idx] == 0:
                        twin = (cells - shift) + idx
                        if label[twin] == -1:
                            label[twin] = counter
                            todo.append(twin)
                counter += 1

        for _ in range(qty):
            a = int(fetch())
            b = int(fetch())
            c = int(fetch())
            d = int(fetch())
            home = label[a * cols + b]
            spot = c * cols + d
            kd = kind[spot]
            if kd == 0:
                works = label[spot] == home or label[cells + spot] == home
            elif kd == 1:
                works = label[spot] == home
            else:
                works = label[cells + spot] == home
            replies.append("YES" if works else "NO")
    sys.stdout.write("\n".join(replies) + "\n")


program()
