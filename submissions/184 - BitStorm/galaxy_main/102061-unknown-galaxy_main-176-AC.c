
#include <stdio.h>

#define MAX 200
#define MAX_STATES 80000

char grid[MAX][MAX + 1];

int component[MAX][MAX][2];

int queue[MAX_STATES];

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

// Check whether a tile is accessible in the current mode
int isActive(char tile, int mode)
{
    if (tile == '.')
        return 1;

    if (mode == 0 && tile == 'B')
        return 1;

    if (mode == 1 && tile == 'R')
        return 1;

    return 0;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int N, M, Q;
        scanf("%d %d %d", &N, &M, &Q);

        // Read grid
        for (int i = 0; i < N; i++)
        {
            scanf("%s", grid[i]);
        }

        // Initialize components
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                for (int k = 0; k < 2; k++)
                {
                    component[i][j][k] = -1;
                }
            }
        }

        int componentID = 0;

        // Find all connected components using BFS
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                for (int mode = 0; mode < 2; mode++)
                {
                    // Skip inactive or already visited states
                    if (!isActive(grid[i][j], mode) ||
                        component[i][j][mode] != -1)
                    {
                        continue;
                    }

                    int front = 0;
                    int rear = 0;

                    // Start BFS
                    queue[rear++] = (i * M + j) * 2 + mode;

                    component[i][j][mode] = componentID;

                    while (front < rear)
                    {
                        int current = queue[front++];

                        // Decode current state
                        int r = current / (M * 2);
                        int c = (current / 2) % M;
                        int currentMode = current % 2;

                        // Explore four directions
                        for (int d = 0; d < 4; d++)
                        {
                            int nr = r + dr[d];
                            int nc = c + dc[d];

                            // Check grid boundaries
                            if (nr < 0 || nr >= N ||
                                nc < 0 || nc >= M)
                            {
                                continue;
                            }

                            // Check whether the next tile is accessible
                            if (isActive(grid[nr][nc], currentMode) &&
                                component[nr][nc][currentMode] == -1)
                            {
                                component[nr][nc][currentMode] = componentID;

                                queue[rear++] =
                                    (nr * M + nc) * 2 + currentMode;
                            }
                        }

                        // Spin is possible only on normal tiles
                        if (grid[r][c] == '.')
                        {
                            int nextMode = 1 - currentMode;

                            if (component[r][c][nextMode] == -1)
                            {
                                component[r][c][nextMode] = componentID;

                                queue[rear++] =
                                    (r * M + c) * 2 + nextMode;
                            }
                        }
                    }

                    componentID++;
                }
            }
        }

        // Answer queries
        while (Q--)
        {
            int rs, cs, re, ce;

            scanf("%d %d %d %d", &rs, &cs, &re, &ce);

            // Starting position is always normal
            // and initial mode is blue (0)
            int startComponent = component[rs][cs][0];

            int possible = 0;

            // Try reaching destination in blue mode
            if (isActive(grid[re][ce], 0) &&
                component[re][ce][0] == startComponent)
            {
                possible = 1;
            }

            // Try reaching destination in red mode
            if (isActive(grid[re][ce], 1) &&
                component[re][ce][1] == startComponent)
            {
                possible = 1;
            }

            if (possible)
                printf("YES\n");
            else
                printf("NO\n");
        }
    }

    return 0;
}
