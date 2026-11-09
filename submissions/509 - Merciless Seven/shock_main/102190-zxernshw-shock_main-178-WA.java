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

    public static int[][] solve(int N, int M, int Q, List<int[]> earthquakes)
    {
        int[][] city = new int[N][M];
        for(int eqNum = 0; eqNum<Q;eqNum++)
        {
            int[] eq = earthquakes.get(eqNum);
            for(int row = eq[1] - eq[2] - 1; row < city.length && row <  eq[1] + eq[2] + 2; row++)
            {
                for(int col = eq[0] - eq[2] - 1; col < city[0].length && col<eq[0] + eq[2] + 2;col++)
                {
                    int distX = eq[0]-row;
                    int distY = eq[1]-col;
                    if(distX*distX + distY*distY <= eq[2]*eq[2])
                    {
                        int sizeometer = eq[2]*eq[2] - distX*distX - distY*distY + 1;

                            city[row][col]=sizeometer;
                    }
                }
            }
        }
        return city;
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
