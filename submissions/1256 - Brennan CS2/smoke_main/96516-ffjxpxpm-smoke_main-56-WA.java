import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.StringTokenizer;

public class Valorant {
    public static void main(String args[]) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        int T = Integer.parseInt(br.readLine());
        for(int i = 0; i < T; i++){
            ArrayList<Integer> list = new ArrayList<>();
            StringTokenizer st = new StringTokenizer(br.readLine());
            int N = Integer.parseInt(st.nextToken());
            int R = Integer.parseInt(st.nextToken());
            StringTokenizer st2 = new StringTokenizer(br.readLine());
            while(st2.hasMoreTokens()){
                list.add(Integer.parseInt(st2.nextToken()));
            }
            int count = 0;
            while(Math.abs(list.get(0) - list.get(2)) >= R || Math.abs(list.get(0) - list.get(2)) < R){
                for(int j = 2; j < N; j++){
                    if(Math.abs(list.get(j) - list.get(j - 1)) < R){
                        bw.write("NO" + "\n");
                        count++;
                        break;
                    }
                }
                break;
            }
            if(count == 0){
                bw.write("YES" + "\n");
            }
        }
        bw.close();
        br.close();
    }
}
