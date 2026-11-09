import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.StringTokenizer;
public class TreeMemory {
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
    static void saveTree(Input in,int n) throws IOException {
        int[] first =new int[n+1];
        int[] to=new int[2*(n-1)];
        int[] link =new int[to.length];
        Arrays.fill(first,-1);
        int edge=0;
        for (int i=1;i<n;i++) {
            int u =in.nextInt();
            int v= in.nextInt();
            to[edge]=v;
            link[edge] =first[u];
            first[u]=edge++;
            to[edge] =u;
            link[edge]=first[v];
            first[v] =edge++;
        }
        int[] parent=new int[n+1];
        int[] queue =new int[n];
        int head=0;
        int tail =1;
        queue[0]=1;
        parent[1] =-1;
        while(head<tail) {
            int from=queue[head++];
            for (int e=first[from];e!=-1;e=link[e]) {
                int node =to[e];
                if(parent[node]!=0) {
                    continue;
                }
                parent[node]=from;
                queue[tail++] =node;
            }
        }
        StringBuilder out= new StringBuilder();
        int check =0;
        for (int node=2;node<=n; node++) {
            out.append(parent[node]).append(' ');
            check ^=parent[node];
        }
        out.append(check).append('\n');
        System.out.print(out);
    }
    static void restoreTree(Input in, int n) throws IOException {
        int[] saved =new int[n];
        int missing=-1;
        int check =0;
        for (int i=0;i<n; i++) {
            saved[i]=in.nextInt();
            if(saved[i]==-1) {
                missing=i;
            }
            else {
                check^=saved[i];
            }
        }
        saved[missing]=check;
        StringBuilder out =new StringBuilder();
        for (int i=0;i<n-1;i++) {
            out.append(i+2).append(' ').append(saved[i]).append('\n');
        }
        System.out.print(out);
    }
    public static void main(String[] args) throws IOException {
        Input in =new Input();
        String phase=in.next();
        int n= in.nextInt();
        if(phase.equals("FIRST")) {
            saveTree(in,n);
        }
        else {
            restoreTree(in,n);
        }
    }
}