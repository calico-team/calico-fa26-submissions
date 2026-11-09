import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.*;

class Shock {
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out);

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

    public static void main(String[] args) throws IOException {
        int T = Integer.parseInt(in.readLine());
        for(int f = 0; f<T; f++) {
            String[] temp = in.readLine().split(" ");
            int N = Integer.parseInt(temp[0]);
            int M = Integer.parseInt(temp[1]);
            int Q = Integer.parseInt(temp[2]);
            List<int[]> earthquakes = new ArrayList<>();
            for (int i = 0; i < Q; i++) {
                String[] tem = in.readLine().split(" ");
                int X = Integer.parseInt(tem[0]);
                int Y = Integer.parseInt(tem[1]);
                int P = Integer.parseInt(tem[2]);
                earthquakes.add(new int[]{X, Y, P});
            }
            int[][] answer = solve(N, M, Q, earthquakes);
            out.println();
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    if (j > 0) out.print(" ");
                    out.print(answer[i][j]);
                }
                out.println();
            }
        }
        out.flush();
    }
}
