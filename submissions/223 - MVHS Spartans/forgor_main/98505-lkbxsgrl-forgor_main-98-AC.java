import java.io.*;
import java.util.*;

public class Forgor{
	public static void main(String[] args) throws IOException{
        Forgor main = new Forgor();
        main.solve();
    }

    public void solve() throws IOException{
		BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        StringTokenizer st = new StringTokenizer(r.readLine());
        String phase = st.nextToken();
        boolean triple = false;
        
        if(phase.equals("FIRST")){ //phase 1
            st = new StringTokenizer(r.readLine());
            int n = Integer.parseInt(st.nextToken());

            ArrayList<Integer>[] adjacencyList = new ArrayList[n+1];
            for (int i = 1; i<=n; i++) {
                adjacencyList[i] = new ArrayList<>();
            }
            for(int i = 0; i<n-1; i++){
                st = new StringTokenizer(r.readLine());
                int u = Integer.parseInt(st.nextToken());
                int v = Integer.parseInt(st.nextToken());
                adjacencyList[u].add(v);
                adjacencyList[v].add(u);
            }

            int[] parents = new int[n+1];
            boolean[] visited = new boolean[n+1];

            LinkedList<Integer> q = new LinkedList<>();
            q.add(1);
            visited[1] = true;

            while(!q.isEmpty()){
                int u = q.poll();
                for (int vertex : adjacencyList[u]) {
                    if (!visited[vertex]) {
                        visited[vertex] = true;

                        parents[vertex] = u;
                        q.add(vertex);
                    }
                }
            }
            int[] A = new int[n+1];
            int summy = 0;
            for(int i=2; i<=n; i++){
                A[i] = parents[i];
                summy^=A[i];
            }

            A[1] = summy; // determine missing value

            StringBuilder sb = new StringBuilder();
            for(int i=1; i<=n; i++){
                if(i == n){
                    sb.append(A[i]);
                }else{
                    sb.append(A[i]);
                    sb.append(" ");
                }
            }
            System.out.println(sb.toString());
            
        }else if(phase.equals("SECOND")){ //ohase 2
            st = new StringTokenizer(r.readLine());
            int n = Integer.parseInt(st.nextToken());
            st = new StringTokenizer(r.readLine());
            
            int[] A = new int[n+1];
            int missing = -1;
            
            for(int i = 1; i<=n; i++){
                A[i] = Integer.parseInt(st.nextToken());
                if(A[i] == -1){
                    missing = i;
                }
            }
            
            if(missing != 1){ //if it is we dgaf
                int currXor = 0;
                for(int i = 2; i<=n; i++){
                    if(i!=missing){
                        currXor ^= A[i];
                    }
                }

                A[missing] = A[1]^currXor;
            }
            
            if(!triple){
                for (int i = 2; i <= n; i++) {
                    pw.println(i + " " + A[i]);
                }
            }else{
                pw.println("something wrong");
            }
        }
        pw.flush();
    }
}
