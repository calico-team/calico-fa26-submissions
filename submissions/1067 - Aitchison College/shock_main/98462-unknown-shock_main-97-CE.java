import java.util.*;

/*
* Return an N by M grid displaying the reading of the block seismometers after all earthquakes occur.
*
* N: number of rows in the grid
* M: number of columns in the grid
* Q: number of earthquakes
* earthquakes: a list of arrays {X, Y, P}, where:
*     X: column of the epicenter
*     Y: row of the epicenter
*     P: power of the earthquake
*/
class Solution {

    public static int[][] solve(int N, int M, int Q, List<int[]> earthquakes) {
        for (int i = 0; i < Q; i++) {

            int R = earthquakes[i][0];
            int C = earthquakes[i][1];
            int P = earthquakes[i][2];

            for (int r = 0; r < N; r++) {
                for (int c = 0; c < M; c++) {

                    int distance = (r - R) * (r - R)
                            + (c - C) * (c - C);

                    if (distance <= P * P) {
                        grid[r][c] = P * P - distance + 1;
                    }
                }
            }
        }

        return grid[r][c];
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        while (T-- > 0) {
            int N = sc.nextInt();
            int M = sc.nextInt();
            int Q = sc.nextInt();
            List<int[]> earthquakes = new ArrayList<>();
            for (int i = 0; i < Q; i++) {
                int X = sc.nextInt();
                int Y = sc.nextInt();
                int P = sc.nextInt();
                earthquakes.add(new int[]{X, Y, P});
            }
            int[][] answer = solve(N, M, Q, earthquakes);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    if (j > 0) System.out.print(" ");
                    System.out.print(answer[i][j]);
                }
                System.out.println();
            }
        }
        sc.close();
    }
}
