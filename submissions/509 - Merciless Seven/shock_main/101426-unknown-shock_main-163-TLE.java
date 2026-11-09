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
            for(int row = 0; row < city.length; row++)
            {
                for(int col = 0; col<city[0].length;col++)
                {
                    int distX = eq[0]-row;
                    int distY = eq[1]-col;
                    if(distX*distX + distY*distY<=eq[2]*eq[2])
                    {
                        int sizeometer = eq[2]*eq[2] - distX*distX - distY*distY + 1;
                       // if(sizeometer>city[row][col])
                            city[row][col]=sizeometer;
                    }
                }
            }
            if(eq[2]==0)
            {
                city[eq[0]][eq[1]]=1;
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