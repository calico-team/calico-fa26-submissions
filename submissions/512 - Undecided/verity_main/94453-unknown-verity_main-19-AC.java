

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class verity {
    public static void main(String[] args) throws IOException{
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int N = Integer.parseInt(reader.readLine());
        while(N-->0) {
            StringTokenizer st = new StringTokenizer(reader.readLine());
            int len = Integer.parseInt(st.nextToken());
            int k = Integer.parseInt(st.nextToken());

            StringBuilder s = new StringBuilder();
            s.append("_".repeat(Math.max(0, len)));
            st = new StringTokenizer(reader.readLine());
            for (int i = 0; i < k; i++){
                String temp = st.nextToken();
                for(int j=0;j<len;j++)System.out.print(s.charAt(j)=='_'?temp:s.charAt(j));
                System.out.println();
                s = new StringBuilder(reader.readLine());
                if(s.toString().equals("CORRECT"))break;
            }
        }
    }
}
