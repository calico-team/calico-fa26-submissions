import java.io.*;
import java.util.*;
public class p5 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        for(int t=Integer.parseInt(br.readLine());t>0;t--){
            StringTokenizer st = new StringTokenizer(br.readLine());
            int n=Integer.parseInt(st.nextToken());
            int m=Integer.parseInt(st.nextToken());
            int queries=Integer.parseInt(st.nextToken());
            char[][] grid = new char[n][m];
            for(int i=0;i<n;i++){
                String s = br.readLine();
                for(int j=0;j<m;j++) {
                    grid[i][j] = s.charAt(j);
                }
            }
            int[][]moves = new int[][]{{0,1,0},{0,-1,0},{1,0,0},{-1,0,0},{0,0,1}};

            int[][] component = new int[n][m];
            int curr=1;
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++) {
                    if(component[i][j]==0){
                        Queue<int[]> q = new ArrayDeque<>();
                        int[][][] visited = new int[n][m][2];
                        q.add(new int[]{i,j,0});

                        while(!q.isEmpty()){
                            int[] stuff = q.poll();
                            int x = stuff[0];
                            int y = stuff[1];
                            int color=stuff[2]; //0 --> blue, 1 --> red
                            if(x<0||x>=n||y<0||y>=m){
                                continue;
                            }
                            if(visited[x][y][color]>0){
                                continue;
                            }

                            if(grid[x][y]=='R'&&color==0||grid[x][y]=='B'&&color==1) {
                                continue;
                            }
                            visited[x][y][color]=curr;
                            component[x][y]=curr;

                            for(int k=0;k<5;k++){
                                int newX=x+moves[k][0];
                                int newY=y+moves[k][1];
                                int newColor=Math.abs(moves[k][2]-color);
                                if(newX<0||newX>=n||newY<0||newY>=m||(visited[newX][newY][newColor]==1)||(grid[newX][newY]=='R'&&newColor==0||grid[newX][newY]=='B'&&newColor==1)){
                                    continue;
                                }
                                q.add(new int[]{newX,newY,newColor});
                            }


                        }
                        curr++;
                    }
                }
            }





            for(int i=0;i<queries;i++){
                st = new StringTokenizer(br.readLine());
                int x1=Integer.parseInt(st.nextToken());
                int y1=Integer.parseInt(st.nextToken());
                int x2=Integer.parseInt(st.nextToken());
                int y2=Integer.parseInt(st.nextToken());
                if(component[x1][y1]==component[x2][y2]){
                    System.out.println("YES");
                } else{
                    System.out.println("NO");
                }


            }


        }

    }
}
