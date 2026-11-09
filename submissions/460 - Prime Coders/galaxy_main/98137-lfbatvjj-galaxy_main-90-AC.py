
from collections import deque


def solve(N: int, M: int, Q: int, G: list[str],
          start: list[tuple[int, int]],
          end: list[tuple[int, int]]) -> list[str]:

    total = N * M

    # Each cell has two possible states:
    # 0 = Blue mode, 1 = Red mode
    visited = [-1] * (2 * total)

    def is_active(r, c, mode):
        if G[r][c] == '.':
            return True

        if mode == 0 and G[r][c] == 'B':
            return True

        if mode == 1 and G[r][c] == 'R':
            return True

        return False

    component = 0

    # Find all connected components using BFS
    for mode in range(2):

        for r in range(N):
            for c in range(M):

                cell = r * M + c
                state = mode * total + cell

                if visited[state] != -1:
                    continue

                if not is_active(r, c, mode):
                    continue

                queue = deque([(r, c, mode)])
                visited[state] = component

                while queue:

                    x, y, current_mode = queue.popleft()

                    current_cell = x * M + y
                    current_state = current_mode * total + current_cell

                    # Move in four directions
                    directions = [
                        (-1, 0),
                        (1, 0),
                        (0, -1),
                        (0, 1)
                    ]

                    for dx, dy in directions:

                        nx = x + dx
                        ny = y + dy

                        if 0 <= nx < N and 0 <= ny < M:

                            if is_active(nx, ny, current_mode):

                                next_cell = nx * M + ny
                                next_state = (
                                    current_mode * total + next_cell
                                )

                                if visited[next_state] == -1:

                                    visited[next_state] = component
                                    queue.append(
                                        (nx, ny, current_mode)
                                    )

                    # Spin is allowed only on normal tiles
                    if G[x][y] == '.':

                        next_mode = 1 - current_mode
                        next_state = next_mode * total + current_cell

                        if visited[next_state] == -1:

                            visited[next_state] = component
                            queue.append(
                                (x, y, next_mode)
                            )

                component += 1

    # Answer all queries
    answers = []

    for i in range(Q):

        sr, sc = start[i]
        er, ec = end[i]

        # Starting mode is always Blue
        start_state = sr * M + sc

        # Destination can be reached in either mode
        end_blue = er * M + ec
        end_red = total + er * M + ec

        start_component = visited[start_state]

        if (visited[end_blue] == start_component or
                visited[end_red] == start_component):

            answers.append("YES")

        else:
            answers.append("NO")

    return answers


def main():
    T = int(input())

    for _ in range(T):
        N, M, Q = map(int, input().split())

        G = []

        for _ in range(N):
            G.append(input())

        start, end = [], []

        for _ in range(Q):
            start_row, start_col, end_row, end_col = map(int, input().split())

            start.append((start_row, start_col))
            end.append((end_row, end_col))

        for s in solve(N, M, Q, G, start, end):
            print(s)


if __name__ == '__main__':
    main()
