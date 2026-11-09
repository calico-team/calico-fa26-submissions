import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.StringTokenizer;
public class GalaxyPaths {
    static int n,m,width;
    static int[] edges,dist,queue;
    static byte[] degree;
    static boolean[] active,answer;
    static int[] source,target,limit,order;
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
    static void link(int from,int to) {
        edges[from*5+degree[from]++]=to;
    }
    static void build(char[][] grid) {
        width=2*n;
        int size=width*m;
        active =new boolean[size];
        edges=new int[size*5];
        degree =new byte[size];
        dist=new int[size];
        queue =new int[size];
        for (int col=0;col<m;col++) {
            for (int row=0;row<n; row++) {
                int cell=(col*n+row)*2;
                active[cell]=grid[row][col]!='R';
                active[cell+1] =grid[row][col]!='B';
            }
        }
        for (int col=0;col<m; col++) {
            for (int row=0;row<n;row++) {
                int cell =(col*n+row)*2;
                for (int mode=0;mode<2; mode++) {
                    int v=cell+mode;
                    if(!active[v]) {
                        continue;
                    }
                    if(row>0 && active[v-2]) {
                        link(v,v-2);
                    }
                    if(row+1<n && active[v+2]) {
                        link(v,v+2);
                    }
                    if(col>0 && active[v-width]) {
                        link(v,v-width);
                    }
                    if(col+1<m && active[v+width]) {
                        link(v,v+width);
                    }
                    if(grid[row][col]=='.') {
                        link(v,v^1);
                    }
                }
            }
        }
    }
    static void bfs(int start,int low,int high) {
        Arrays.fill(dist,low,high,-1);
        int head=0;
        int tail =1;
        queue[0]=start;
        dist[start] =0;
        while(head<tail) {
            int v=queue[head++];
            int base =v*5;
            for (int i=0;i<degree[v]; i++) {
                int to=edges[base+i];
                if(to<low || to>=high || dist[to]!=-1) {
                    continue;
                }
                dist[to] =dist[v]+1;
                queue[tail++]=to;
            }
        }
    }
    static void check(int from,int end) {
        for (int i=from;i<end;i++) {
            int id=order[i];
            if(answer[id]) {
                continue;
            }
            int first=dist[source[id]];
            if(first<0 || first>limit[id]) {
                continue;
            }
            int blue=dist[target[id]];
            int red =dist[target[id]+1];
            if(blue>=0 && first+blue<=limit[id]) {
                answer[id]=true;
            }
            if(red>=0 && first+red<=limit[id]) {
                answer[id] =true;
            }
        }
    }
    static void swap(int a,int b) {
        int hold=order[a];
        order[a] =order[b];
        order[b]=hold;
    }
    static void solve(int left,int right,int from,int end) {
        if(left>right || from>=end) {
            return;
        }
        int mid=(left+right)/2;
        int low =left*width;
        int high=(right+1)*width;
        for (int start=mid*width;start<(mid+1)*width; start++) {
            if(!active[start]) {
                continue;
            }
            bfs(start,low,high);
            check(from,end);
        }
        int leftEnd=from;
        for (int i=from;i<end;i++) {
            int id =order[i];
            if(!answer[id] && source[id]/width<mid && target[id]/width<mid) {
                swap(i,leftEnd++);
            }
        }
        int rightEnd =leftEnd;
        for (int i=leftEnd;i<end; i++) {
            int id=order[i];
            if(!answer[id] && source[id]/width>mid && target[id]/width>mid) {
                swap(i,rightEnd++);
            }
        }
        solve(left,mid-1,from,leftEnd);
        solve(mid+1,right,leftEnd,rightEnd);
    }
    public static void main(String[] args) throws IOException {
        Input in =new Input();
        StringBuilder out= new StringBuilder();
        int rounds =in.nextInt();
        while(rounds-- >0) {
            n=in.nextInt();
            m =in.nextInt();
            int q=in.nextInt();
            char[][] grid =new char[n][];
            for (int r=0;r<n;r++) {
                grid[r]=in.next().toCharArray();
            }
            build(grid);
            source =new int[q];
            target=new int[q];
            limit =new int[q];
            order=new int[q];
            answer =new boolean[q];
            int pending=0;
            for (int i=0;i<q; i++) {
                int sr =in.nextInt();
                int sc=in.nextInt();
                int er =in.nextInt();
                int ec=in.nextInt();
                limit[i] =in.nextInt();
                source[i]=(sc*n+sr)*2;
                target[i] =(ec*n+er)*2;
                if(source[i]==target[i]) {
                    answer[i]=true;
                }
                else if(Math.abs(sr-er)+Math.abs(sc-ec)<=limit[i]) {
                    order[pending++]=i;
                }
            }
            solve(0,m-1,0,pending);
            for (int i=0;i<q;i++) {
                if(answer[i]) {
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