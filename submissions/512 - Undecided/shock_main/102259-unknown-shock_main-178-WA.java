
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Earthquake {
    public static void main(String[] args)throws IOException{
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(reader.readLine());

        while(T-->0){
            StringTokenizer st = new StringTokenizer(reader.readLine());
            int N = Integer.parseInt(st.nextToken());
            int M = Integer.parseInt(st.nextToken());
            int Q = Integer.parseInt(st.nextToken());

            long[][] quakes = new long[Q][3];

            for(int i=0;i<Q;i++){
                st = new StringTokenizer(reader.readLine());
                quakes[i][0] = Integer.parseInt(st.nextToken());
                quakes[i][1] = Integer.parseInt(st.nextToken());
                quakes[i][2] = (long) Math.pow(Integer.parseInt(st.nextToken()),2);
            }

            for(int i=0;i<N;i++){
                for(int j=0;j<M;j++){
                    for(int k=Q-1;k>=0;k--){
                        boolean t = true;
                        if(Math.pow(quakes[k][0]-i,2)+Math.pow(quakes[k][1]-j,2)<=quakes[k][2]+1){
                            System.out.print((long)(quakes[k][2]-(Math.pow(quakes[k][0]-i,2)+Math.pow(quakes[k][1]-j,2))+1)+" ");
                            t = false;
                            break;
                        }
                        if(t)System.out.print(0+" ");
                    }
                }
                System.out.println();
            }
        }
    }
}
