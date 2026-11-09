import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;
public class GalaxyBonus {
    static int n,m;
    static char[][] grid;
    static int[][] group;
    static int[] queue;
    static int[] dr = {-1,1,0,0};
    static int[] dc= {0,0,-1,1};
    static class Input {
        BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st =new StringTokenizer("");
        String next() throws IOException {
            while(!st.hasMoreTokens()) {
                st= new StringTokenizer(br.readLine());
            }
            return st.nextToken();
        }
        int nextInt() throws IOException {
            return Integer.parseInt(next());
        }
    }
    static void fill(int row,int col, int id) {
        int head=0;
        int tail =0;
        queue[tail++]= row*m+col;
        group[row][col] =id;
        while(head<tail) {
            int cell=queue[head++];
            int r =cell/m;
            int c=cell%m;
            for (int d=0;d < 4; d++) {
                int nr=r+dr[d];
                int nc =c+dc[d];
                if(nr<0 || nr>=n || nc<0 || nc>=m) {
                    continue;
                }
                if(group[nr][nc]!=0) {
                    continue;
                }
                char from= grid[r][c];
                char to =grid[nr][nc];
                if(from!='.' && to!='.' && from!=to) {
                    continue;
                }
                group[nr][nc]=id;
                queue[tail++] =nr*m+nc;
            }
        }
    }
    public static void main(String[] args) throws IOException {
        Input in =new Input();
        StringBuilder out= new StringBuilder();
        int rounds =in.nextInt();
        while(rounds-- > 0) {
            n= in.nextInt();
            m =in.nextInt();
            int q= in.nextInt();
            grid=new char[n][];
            for (int r=0;r<n; r++) {
                grid[r] =in.next().toCharArray();
            }
            group =new int[n][m];
            queue=new int[n*m];
            int id=0;
            for (int r =0;r<n;r++) {
                for (int c=0;c < m; c++) {
                    if(group[r][c]==0) {
                        fill(r,c,++id);
                    }
                }
            }
            while(q-- >0) {
                int sr= in.nextInt();
                int sc =in.nextInt();
                int er= in.nextInt();
                int ec =in.nextInt();
                if(group[sr][sc]==group[er][ec]) {
                    out.append("YES\n");
                }
                else {
                    out.append("NO\n");
                }
            }
        }
        System.out.print(out);
    }
}