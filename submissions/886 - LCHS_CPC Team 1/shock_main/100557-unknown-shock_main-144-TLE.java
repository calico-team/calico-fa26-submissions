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
    private static int finderBuddy(int a, int b, int[][] nextCol){
        if(nextCol[a][b] == b){
            return b;
        }
        else{
            return finderBuddy(a, nextCol[a][b], nextCol);
        }
    }
    public static int[][] solve(int N, int M, int Q, List<int[]> earthquakes) {
        int[][] map = new int[N][M];
        int[][] nextCol = new int[N][M + 1];
        for (int i5 = 0; i5 < N; i5++) {
            for (int i6 = 0; i6 <= M; i6++) {
                nextCol[i5][i6] = i6;
            }
        }
        for(int i10 = (Q-1); i10 >= 0; i10--){
            int[] i = earthquakes.get(i10);
            int Row = i[0];
            int Col = i[1];
            int POWER = i[2];
            long POWER2 = (long) POWER * POWER;
            
            int HighRow = (int) Math.max(0, Row - POWER);
            int LowRow = (int) Math.max(0, Math.min(N-1, Row + POWER));
            for(int i2 = HighRow; i2<= LowRow; i2++){
                int Rdist = i2- Row;
                if((Rdist*Rdist) > POWER2){
                    continue;
                }
                int Cdist = (int) Math.sqrt(POWER2 - (Rdist*Rdist));
                int LowC = (int) Math.max(0, Col -Cdist);
                int HighC = (int) Math.min(M-1, Col + Cdist);
                int i4 = LowC;
                while(true){
                    i4 = finderBuddy(i2, i4, nextCol);
                    if(i4 >HighC){
                        break;
                    }
                    int holder = i4 - Col; 
                    map[i2][i4] = (int)((POWER2-(Rdist*Rdist)+1) - (holder*holder));
                    nextCol[i2][i4] = i4+1;
                    i4+=1;
                }
            }
        }
        return map;
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