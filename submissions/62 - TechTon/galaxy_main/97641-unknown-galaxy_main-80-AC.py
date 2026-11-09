import sys
from collections import deque


def solve() -> None:
    deta = sys.stdin.buffer.read().split()
    if not deta:
        return

    tkn = 0
    tst_cass = int(deta[tkn])
    tkn += 1
    ansrs = []

    for _ in range(tst_cass):
        ros = int(deta[tkn])
        cos = int(deta[tkn + 1])
        quris = int(deta[tkn + 2])
        tkn += 3

        grid = [deta[tkn + i].decode() for i in range(ros)]
        tkn += ros

        cl_cnt = ros * cos
        cmponnts = [-1] * (2 * cl_cnt)
        cmponent_id = 0

        def active(cell: str, mode: int) -> bool:
            return cell == "." or (mode == 0 and cell == "B") or (
                mode == 1 and cell == "R"
            )

        for mode in range(2):
            for start in range(cl_cnt):
                row, col = divmod(start, cos)
                if cmponnts[mode * cl_cnt + start] != -1:
                    continue
                if not active(grid[row][col], mode):
                    continue

                cmponnts[mode * cl_cnt + start] = cmponent_id
                queue = deque([(start, mode)])

                while queue:
                    cl_i, curnt_md = queue.popleft()
                    curnt_r, curnt_cl = divmod(cl_i, cos)

                    if grid[curnt_r][curnt_cl] == ".":
                        other_state = (curnt_md ^ 1) * cl_cnt + cl_i
                        if cmponnts[other_state] == -1:
                            cmponnts[other_state] = cmponent_id
                            queue.append((cl_i, curnt_md ^ 1))

                    for nxt_r, nxt_cl in (
                        (curnt_r - 1, curnt_cl),
                        (curnt_r + 1, curnt_cl),
                        (curnt_r, curnt_cl - 1),
                        (curnt_r, curnt_cl + 1),
                    ):
                        if not (0 <= nxt_r < ros and 0 <= nxt_cl < cos):
                            continue

                        nxt_i = nxt_r * cos + nxt_cl
                        state = curnt_md * cl_cnt + nxt_i
                        if (
                            cmponnts[state] == -1
                            and active(grid[nxt_r][nxt_cl], curnt_md)
                        ):
                            cmponnts[state] = cmponent_id
                            queue.append((nxt_i, curnt_md))

                cmponent_id += 1

        for _ in range(quris):
            strt_r = int(deta[tkn])
            strt_cl = int(deta[tkn + 1])
            end_r = int(deta[tkn + 2])
            end_cl = int(deta[tkn + 3])
            tkn += 4

            strt_i = strt_r * cos + strt_cl
            end_i = end_r * cos + end_cl
            start_component = cmponnts[strt_i]
            dest = grid[end_r][end_cl]

            if dest == "B":
                reachable = start_component == cmponnts[end_i]
            elif dest == "R":
                reachable = start_component == cmponnts[cl_cnt + end_i]
            else:
                reachable = (
                    start_component == cmponnts[end_i]
                    or start_component == cmponnts[cl_cnt + end_i]
                )

            ansrs.append("YES" if reachable else "NO")

    sys.stdout.write("\n".join(ansrs))


if __name__ == "__main__":
    solve()
