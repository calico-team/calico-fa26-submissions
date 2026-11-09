import java.io.*;

class Solution {
    /**
     * Return an array of Q strings, the i-th of which is "YES"
     * if Big Ben can travel from start[i] to end[i], and "NO"
     * otherwise.
     *
     * N: the number of rows in the grid
     * M: the number of columns in the grid
     * Q: the number of queries
     * G: the grid, where each tile is 'R', 'B', or '.'
     * start: the {row, column} of the starting tile of each query
     * end: the {row, column} of the ending tile of each query
     */
    static String[] solve(int N, int M, int Q, String[] G, int[][] start, int[][] end) {
        String[] result = new String[Q];

            int[] hor = {-1, 1, 0, 0};
       int[] ver = {0, 0, -1, 1};

    for (int q = 0; q < Q; q++) {

        boolean[][][] checks =      new boolean[N][M][2];

            int[] h = new int[N * M * 2];
        int[] v = new int[N * M * 2];
             int[] color =          new int[N * M * 2];

        int first =      0;
          int last = 0;

        int initalhorizontal =           start[q][0];
                      int initialvertical = start[q][1];

        int lasthorizontal = end[q][0];
                  int lastvertical = end[q][1];

        h[last] = initalhorizontal;
                    v[last] = initialvertical;
        color[last] = 0;
                     last++;

        checks[initalhorizontal][initialvertical][0] = true;

        boolean position = false;

        for (first = 0; first < last; first++) {

            int a = h[first];
                  int b = v[first];
                        int c = color[first];

            if (a == lasthorizontal && b == lastvertical) {
                position = true;
                break;
            }

            if (G[a].charAt(b) == '.') {

                int newColor = 1 - c;

                if (checks[a][b][newColor] == false) {

                    checks[a][b][newColor] = true;

                    h[last] = a;
                    v[last] = b;
                    color[last] = newColor;
                    last++;
                }
            }

            for (int i = 0; i < 4; i++) {

                int nexthorizontal = a + hor[i];
                   int nextvertical = b + ver[i];

                if (nexthorizontal >= 0 && nexthorizontal < N &&
                       nextvertical >= 0 && nextvertical < M) {

                    char ch = G[nexthorizontal].charAt(nextvertical);
                        boolean correct = false;

                    if (ch == '.') {
                          correct = true;}
                    
                    else if (ch == 'B' && c == 0) {
                             correct = true; }   
                    
                    else if (ch == 'R' && c == 1) {
                         correct = true;           }
                    

                    if (correct == true && checks[nexthorizontal][nextvertical][c] == false) {

                        checks[nexthorizontal][nextvertical][c] = true;

                         h[last] = nexthorizontal;
                             v[last] = nextvertical;
                        color[last] = c;
                           last++;           }
                       
                }
            }
        }

        if (position == true) {
            result[q] = "YES";
        }
        else {
            result[q] = "NO";
        }
    }

    return result;
    }

    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) throws IOException {
        int T = Integer.parseInt(in.readLine().trim());
        for (int t = 0; t < T; t++) {
            String[] temp = in.readLine().trim().split(" ");
            int N = Integer.parseInt(temp[0]);
            int M = Integer.parseInt(temp[1]);
            int Q = Integer.parseInt(temp[2]);
            String[] G = new String[N];
            for (int i = 0; i < N; i++) {
                G[i] = in.readLine().trim();
            }
            int[][] start = new int[Q][2];
            int[][] end = new int[Q][2];
            for (int i = 0; i < Q; i++) {
                temp = in.readLine().trim().split(" ");
                start[i][0] = Integer.parseInt(temp[0]);
                start[i][1] = Integer.parseInt(temp[1]);
                end[i][0] = Integer.parseInt(temp[2]);
                end[i][1] = Integer.parseInt(temp[3]);
            }

            for (String s : solve(N, M, Q, G, start, end)) {
                out.println(s);
            }
        }
        out.flush();
    }
}
