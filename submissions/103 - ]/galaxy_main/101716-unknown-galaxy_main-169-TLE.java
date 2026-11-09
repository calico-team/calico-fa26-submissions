import java.io.*;
import java.util.*;

public class E {
    static BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    static int n; static int m;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int t = Integer.parseInt(st.nextToken());
        while(t-->0){
            st = new StringTokenizer(br.readLine());
            n = Integer.parseInt(st.nextToken());
            m  = Integer.parseInt(st.nextToken());
            int q = Integer.parseInt(st.nextToken());
            String[] grid = new String[n];
            for (int i = 0; i < n; i++) {
                grid[i] = br.readLine();
            }
            ArrayList<Component> list = new ArrayList<>();
            ArrayList<HashSet<Integer>> adj = new ArrayList<>();
            int listI = 0;
            int[][] visited = new int[n][m];
            for (int i = 0; i < n; i++) {
                Arrays.fill(visited[i], -1);
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if(visited[i][j]==-1){
                        BFS(adj, list, grid, visited, i, j, listI, grid[i].charAt(j));
                        listI++;
                    }
                }
            }

            for (int i = 0; i < q; i++) {
                st = new StringTokenizer(br.readLine());
                int rS = Integer.parseInt(st.nextToken());
                int cS = Integer.parseInt(st.nextToken());
                int rE = Integer.parseInt(st.nextToken());
                int cE = Integer.parseInt(st.nextToken());
                int sCompNum = visited[rS][cS];
                int eCompNum = visited[rE][cE];

                boolean[] v = new boolean[adj.size()];
                bw.write(DFS(sCompNum, eCompNum, adj, v)?"yes\n":"no\n");
            }
        }
        bw.flush();
    }

    static void BFS(ArrayList<HashSet<Integer>> adj, ArrayList<Component> list, String[] grid,
                    int[][] visited, int i, int j, int k, char t){
        Queue<int[]> q = new LinkedList<>();
        q.add(new  int[] {i, j});
        list.add(new Component(t, k));
        adj.add(new HashSet<>());
        while(!q.isEmpty()){
            int[] pop = q.poll();
            if(pop[0]>=n||pop[0]<0||pop[1]>=m||pop[1]<0) continue;
            if(visited[pop[0]][pop[1]]!=-1){
                if(visited[pop[0]][pop[1]]!=k&&(t=='.'||grid[pop[0]].charAt(pop[1])=='.')) {
                    adj.get(k).add(visited[pop[0]][pop[1]]);
                    adj.get(visited[pop[0]][pop[1]]).add(k);
                }
                continue;
            }
            if(grid[pop[0]].charAt(pop[1])!=t) continue;
            visited[pop[0]][pop[1]] = k;
            q.add(new int[] {pop[0]-1, pop[1]});
            q.add(new int[] {pop[0]+1, pop[1]});
            q.add(new int[] {pop[0], pop[1]-1});
            q.add(new int[] {pop[0], pop[1]+1});
        }
    }

    static class Component {
        char type;
        ArrayList<Integer> point;
        int index;
        public Component(char t, int i) {
            type = t;
            point = new ArrayList<>();
            index = i;
        }
    }

    static boolean DFS(int start, int end, ArrayList<HashSet<Integer>> adj, boolean[] visited){
        if(start==end) return true;
        visited[start] = true;
        for (Integer i : adj.get(start)) {
            if(!visited[i]&& DFS(i, end, adj, visited)){
                return true;
            }
        }
        return false;
    }
}