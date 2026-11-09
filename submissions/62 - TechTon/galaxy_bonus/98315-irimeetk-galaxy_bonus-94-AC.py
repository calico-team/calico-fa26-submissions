import sys
from collections import deque


def bld_cmpnntss(grid: list[str], rs: int, cs: int) -> list[int]:
    clls = rs * cs
    cmpnnts = [-1] * (2 * clls)
    nxt_cmpnnts = 0

    def is_active(tile: str, mode: int) -> bool:
        return tile == "." or tile == ("B" if mode == 0 else "R")

    for mode in range(2):
        for strt in range(clls):
            r, c = divmod(strt, cs)
            state = mode * clls + strt
            if cmpnnts[state] != -1 or not is_active(grid[r][c], mode):
                continue

            cmpnnts[state] = nxt_cmpnnts
            queue = deque([(strt, mode)])

            while queue:
                cll, curnt_mde = queue.popleft()
                r, c = divmod(cll, cs)

                if grid[r][c] == ".":
                    swtd_stte = (curnt_mde ^ 1) * clls + cll
                    if cmpnnts[swtd_stte] == -1:
                        cmpnnts[swtd_stte] = nxt_cmpnnts
                        queue.append((cll, curnt_mde ^ 1))

                for nxt_r, nxt_c in (
                    (r - 1, c),
                    (r + 1, c),
                    (r, c - 1),
                    (r, c + 1),
                ):
                    if not (0 <= nxt_r < rs and 0 <= nxt_c < cs):
                        continue

                    nxt_cll = nxt_r * cs + nxt_c
                    next_state = curnt_mde * clls + nxt_cll
                    if (
                        cmpnnts[next_state] == -1
                        and is_active(grid[nxt_r][nxt_c], curnt_mde)
                    ):
                        cmpnnts[next_state] = nxt_cmpnnts
                        queue.append((nxt_cll, curnt_mde))

            nxt_cmpnnts += 1

    return cmpnnts


def solve() -> None:
    deta = sys.stdin.buffer.read().split()
    if not deta:
        return

    tkn = 0
    tst_cass = int(deta[tkn])
    tkn += 1
    anrs = []

    for _ in range(tst_cass):
        rs, cs, qury_cnt = map(int, deta[tkn : tkn + 3])
        tkn += 3
        grid = [deta[tkn + r].decode() for r in range(rs)]
        tkn += rs

        clls = rs * cs
        cmpnnts = bld_cmpnntss(grid, rs, cs)

        for _ in range(qury_cnt):
            strt_r, strt_c, end_r, end_c = map(
                int, deta[tkn : tkn + 4]
            )
            tkn += 4

            strt_cll = strt_r * cs + strt_c
            end_cll = end_r * cs + end_c
            strt_cmpnnts = cmpnnts[strt_cll]
            dstintn = grid[end_r][end_c]

            if dstintn == "B":
                rechbl = strt_cmpnnts == cmpnnts[end_cll]
            elif dstintn == "R":
                rechbl = strt_cmpnnts == cmpnnts[clls + end_cll]
            else:
                rechbl = (
                    strt_cmpnnts == cmpnnts[end_cll]
                    or strt_cmpnnts == cmpnnts[clls + end_cll]
                )

            anrs.append("YES" if rechbl else "NO")

    sys.stdout.write("\n".join(anrs))


if __name__ == "__main__":
    solve()
