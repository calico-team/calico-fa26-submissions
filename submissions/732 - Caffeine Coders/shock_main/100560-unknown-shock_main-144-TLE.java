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
class Shock {

    public static int[][] solve(int N, int M, int Q, List<int[]> earthquakes) {
        int[][] i = new int[N][M];
        for(int f = 0; f<N; f++){
            for(int j = 0; j<M; j++){
                i[f][j]=0;
            }
        }
        for(int s = 0; s<Q; s++){
            for (int r = 0; r < N; r++) {
                for (int c = 0; c < M; c++) {
                    int p = getLocalPower(earthquakes.get(s)[0], earthquakes.get(s)[1], earthquakes.get(s)[2], r, c);
                    if(p > 0){
                        i[r][c] = p;
                    }
                }
            }
        }
        return i;
    }

    public static int getLocalPower(int pi, int ci, int ri, int r, int c) {
        double j = (ri*ri)-((Math.pow(r-pi, 2)) + (Math.pow(c-ci, 2))) + 1;
        return (int) j;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for(int f = 0; f<T; f++) {
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
            System.out.println();
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
