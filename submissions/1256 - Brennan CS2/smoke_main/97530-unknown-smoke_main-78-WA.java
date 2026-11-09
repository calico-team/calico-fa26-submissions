import java.io.*;
import java.util.ArrayList;
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
            int first = 0;
            int second = 0;

            for(int j = 0; j < N; j++){
                if(list.get(j) - first >= R) {
                    first = list.get(j);
                }
                else  if(list.get(j) - second >= R) {
                    second = list.get(j);
                }
                else {
                    count++;
                    break;
                }
            }

            if(count == 0){
                bw.write("YES" + "\n");
            }
            else{
                bw.write("NO" + "\n");
            }
        }
        bw.close();
        br.close();
    }
}
