    import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;
public class Aftershock {
    static int[] next;
    static class Input {
        BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st =new StringTokenizer("");
        int nextInt() throws IOException {
            while(!st.hasMoreTokens()) {
                st= new StringTokenizer(br.readLine());
            }
            return Integer.parseInt(st.nextToken());
        }
    }
    static int find(int cell) {
        while(next[cell]!=cell) {
            next[cell]=next[next[cell]];
            cell =next[cell];
        }
        return cell;
    }
    static int[] readings(int n,int m, int[] rows,int[] cols,int[] power) {
        int stride=m+1;
        next =new int[n*stride];
        for (int i=0;i<next.length;i++) {
            next[i]=i;
        }
        int[] value =new int[n*m];
        for (int quake=power.length-1;quake>=0; quake--) {
            int r=rows[quake];
            int c =cols[quake];
            int p= power[quake];
            int square =p*p;
            for (int row=r-p;row<=r+p; row++) {
                int dy =row-r;
                int leftOver=square-dy*dy;
                int reach =(int)Math.sqrt(leftOver);
                int base=row*stride;
                int end =base+c+reach;
                int cell=find(base+c-reach);
                while(cell<=end) {
                    int col=cell-base;
                    int dx =col-c;
                    value[row*m+col]=leftOver-dx*dx+1;
                    next[cell] =find(cell+1);
                    cell=next[cell];
                }
            }
        }
        return value;
    }
    public static void main(String[] args) throws IOException {
        Input in =new Input();
        StringBuilder out= new StringBuilder();
        int rounds =in.nextInt();
        while(rounds-- >0) {
            int n= in.nextInt();
            int m =in.nextInt();
            int q= in.nextInt();
            int[] rows =new int[q];
            int[] cols=new int[q];
            int[] power =new int[q];
            for (int i=0;i<q; i++) {
                rows[i] =in.nextInt();
                cols[i]=in.nextInt();
                power[i] =in.nextInt();
            }
            int[] value=readings(n,m,rows,cols,power);
            for (int row=0;row<n;row++) {
                for (int col=0;col<m; col++) {
                    if(col>0) {
                        out.append(' ');
                    }
                    out.append(value[row*m+col]);
                }
                out.append('\n');
            }
        }
        System.out.print(out);
    }
}