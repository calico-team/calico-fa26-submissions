

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class DroneRain {
    public static void main(String[] args) throws IOException{
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(reader.readLine());

        while(T-->0){
            StringTokenizer st = new StringTokenizer(reader.readLine());
            long N = Integer.parseInt(st.nextToken());
            long K = Integer.parseInt(st.nextToken());
            long count = N*K;

            ArrayList<ArrayList<Integer>> h = new ArrayList<>();
            ArrayList<ArrayList<Integer>> v = new ArrayList<>();

            for(int i=0;i<N;i++){
                ArrayList<Integer> coords = new ArrayList<>();
                st = new StringTokenizer(reader.readLine());
                coords.add(Integer.parseInt(st.nextToken()));
                coords.add(Integer.parseInt(st.nextToken()));
                st.nextToken();
                if(st.nextToken().equals("E")) h.add(coords);
                else v.add(coords);
            }

            for(ArrayList<Integer> hd : h){
                for(ArrayList<Integer> vd : v){
                    if(vd.get(0)-hd.get(0)==hd.get(1)-vd.get(1) &&
                            vd.get(0)-hd.get(0)>0 &&
                            vd.get(0)-hd.get(0)<=K-1) count--;
                }
            }
            System.out.println(count);
        }
    }
}
