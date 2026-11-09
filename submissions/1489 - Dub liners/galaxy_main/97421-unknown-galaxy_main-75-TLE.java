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

            for(int i=0;i<queries;i++){
                st = new StringTokenizer(br.readLine());
                int startX=Integer.parseInt(st.nextToken());
                int startY=Integer.parseInt(st.nextToken());
                int endX=Integer.parseInt(st.nextToken());
                int endY=Integer.parseInt(st.nextToken());
                boolean ans = false;
                Queue<int[]> q = new ArrayDeque<>();
                int[][][] visited = new int[n][m][2];
                q.add(new int[]{startX,startY,0});

                while(!q.isEmpty()){
                    int[] stuff = q.poll();
                    int x = stuff[0];
                    int y = stuff[1];
                    int color=stuff[2]; //0 --> blue, 1 --> red
                    if(x<0||x>=n||y<0||y>=m){
                        continue;
                    }
                    if(visited[x][y][color]==1){
                        continue;
                    }

                    if(grid[x][y]=='R'&&color==0||grid[x][y]=='B'&&color==1){
                        continue;
                    }
                    if(x==endX&&y==endY){
                        ans=true;
                        break;
                    }
                    visited[x][y][color]=1;

                    for(int j=0;j<5;j++){
                        int newX=x+moves[j][0];
                        int newY=y+moves[j][1];
                        int newColor=Math.abs(moves[j][2]-color);
                        if(newX<0||newX>=n||newY<0||newY>=m||(visited[newX][newY][newColor]==1)||(grid[newX][newY]=='R'&&newColor==0||grid[newX][newY]=='B'&&newColor==1)){
                            continue;
                        }
                        q.add(new int[]{newX,newY,newColor});
                    }


                }
                if(ans){
                    System.out.println("YES");
                } else{
                    System.out.println("NO");
                }


            }


        }

    }
}
