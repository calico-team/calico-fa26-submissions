#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int FAR = 1000000000;

int rows, cols, queries;
char grid[10][4005];
int fromR[100005], fromC[100005], toR[100005], toC[100005], timeLimit[100005];
int shortest[100005];

vector<int> steps, line;
bool canStand(char tile, int mode)
{
    if (tile == '.')
        return true;
    if (tile == 'B')
        return mode == 0;
    return mode == 1;
}

void work(int lo, int hi, vector<int> &group)
{
    if (lo > hi || group.empty())
        return;

    int centre = (lo + hi) / 2;
    vector<int> leftPart, rightPart;
    for (int id : group)
    {
        int smallCol = min(fromC[id], toC[id]);
        int bigCol = max(fromC[id], toC[id]);
        if (bigCol < centre)
            leftPart.push_back(id);
        else if (smallCol > centre)
            rightPart.push_back(id);
    }

    int span = hi - lo + 1;
    int stateCount = span * rows * 2;
    steps.assign(stateCount, FAR);
    line.resize(stateCount);

    for (int row = 0; row < rows; row++)
    {
        for (int mode = 0; mode < 2; mode++)
        {
            if (!canStand(grid[row][centre], mode))
                continue;

            fill(steps.begin(), steps.end(), FAR);
            int front = 0, back = 0;
            int origin = (((centre - lo) * rows + row) << 1) | mode;
            steps[origin] = 0;
            line[back++] = origin;

            while (front < back)
            {
                int now = line[front++];
                int nowMode = now & 1;
                int cell = now >> 1;
                int nowRow = cell % rows;
                int nowCol = lo + cell / rows;
                int taken = steps[now];

                if (grid[nowRow][nowCol] == '.')
                {
                    int other = now ^ 1;
                    if (steps[other] == FAR)
                    {
                        steps[other] = taken + 1;
                        line[back++] = other;
                    }
                }

                for (int way = 0; way < 4; way++)
                {
                    int newRow = nowRow, newCol = nowCol;
                    if (way == 0)
                        newRow--;
                    else if (way == 1)
                        newRow++;
                    else if (way == 2)
                        newCol--;
                    else
                        newCol++;
                    if (newRow < 0 || newRow >= rows || newCol < lo || newCol > hi)
                        continue;
                    if (!canStand(grid[newRow][newCol], nowMode))
                        continue;
                    int next = (((newCol - lo) * rows + newRow) << 1) | nowMode;
                    if (steps[next] == FAR)
                    {
                        steps[next] = taken + 1;
                        line[back++] = next;
                    }
                }
            }

            for (int id : group)
            {
                // Ben always starts in blue mode
                int toCentre = steps[(((fromC[id] - lo) * rows + fromR[id]) << 1)];
                if (toCentre >= FAR)
                    continue;
                for (int endMode = 0; endMode < 2; endMode++)
                {
                    if (!canStand(grid[toR[id]][toC[id]], endMode))
                        continue;
                    int fromCentre = steps[(((toC[id] - lo) * rows + toR[id]) << 1) | endMode];
                    if (fromCentre >= FAR)
                        continue;
                    if (toCentre + fromCentre < shortest[id])
                        shortest[id] = toCentre + fromCentre;
                }
            }
        }
    }

    work(lo, centre - 1, leftPart);
    work(centre + 1, hi, rightPart);
}

int main()
{
    int tests;
    scanf("%d", &tests);
    while (tests--)
    {
        scanf("%d %d %d", &rows, &cols, &queries);
        for (int i = 0; i < rows; i++)
            scanf("%s", grid[i]);

        vector<int> everyone(queries);
        for (int i = 0; i < queries; i++)
        {
            scanf("%d %d %d %d %d", &fromR[i], &fromC[i], &toR[i], &toC[i], &timeLimit[i]);
            shortest[i] = FAR;
            everyone[i] = i;
        }

        work(0, cols - 1, everyone);

        for (int i = 0; i < queries; i++)
            puts(shortest[i] <= timeLimit[i] ? "YES" : "NO");
    }
    return 0;
}