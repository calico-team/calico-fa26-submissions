import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
class Solution {
    static String[] solve(int N, int M, int Q, String[] G, int[][] start, int[][] end) {
        boolean[][] brCorner = new boolean[N][M];
        int[] everyTile = new int[N*M];
        int[] liluziVert = {1,-1,0,0};
        int[] liluziHorizontal = {0,0,1,-1};
        int index = 0;
        brCorner[N - 1][M - 1] = true;
        everyTile[index++] = (((N-1)*M)+M-1);
        while(index>0){
            index--;
            int curTile = everyTile[index];
            int YCombinator = curTile/M;
            int XMarksTheSpot = curTile%M;
            for(int i=0;i<4;i++){
                int y = YCombinator + liluziVert[i];
                int x = XMarksTheSpot + liluziHorizontal[i];
                if (!(y < 0 || x < 0 || y >= N || x >= M)){
                    if (!(brCorner[y][x])){
                        if (!(G[YCombinator].charAt(XMarksTheSpot) + G[y].charAt(x) == 'R' + 'B')){
                            brCorner[y][x] = true;
                            everyTile[index] = y*M+x;
                            index++;
                        }
                    }
                }
            }
        }
        String[] answer = new String[Q];
        for(int i=0;i<Q;i++){
            if(brCorner[start[i][0]][start[i][1]]){
                answer[i] = "YES";
            } else {
                answer[i] = "NO";
            }
        }
        return answer;
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
