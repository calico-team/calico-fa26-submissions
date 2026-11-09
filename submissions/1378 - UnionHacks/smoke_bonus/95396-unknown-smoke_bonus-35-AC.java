import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;
public class Omen {
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

    public static void main(String[] args) throws IOException {
        Input in =new Input();
        StringBuilder out= new StringBuilder();
        int t= in.nextInt();
        for (int test=0;test < t; test++) {
            int n =in.nextInt();
            int r= in.nextInt();
            long first=0;
            long second =0;
            boolean can=true;
            for (int i=0; i<n;i++) {
                int time= in.nextInt();
                if(time <first) {
                    can =false;
                }
                else {
                    first=second;
                    second = Math.max(time,second) +r;
                }
            }
            if(can) {
                out.append("YES\n");
            }
            else {
                out.append("NO\n");
            }
        }
        System.out.print(out);
    }
}