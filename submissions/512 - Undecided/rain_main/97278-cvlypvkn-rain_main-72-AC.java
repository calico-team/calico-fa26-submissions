

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
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

            ArrayList<long[]> h = new ArrayList<>();
            HashMap<Long, ArrayList<Long>> v = new HashMap<>();

            for(int i=0;i<N;i++){
                st = new StringTokenizer(reader.readLine());
                long x = Long.parseLong(st.nextToken());
                long y = Long.parseLong(st.nextToken());
                st.nextToken();
                if(st.nextToken().equals("E")) h.add(new long[]{x,y});
                else v.computeIfAbsent(x+y,k->new ArrayList<>()).add(x);
            }
            for (ArrayList<Long> xs : v.values()) Collections.sort(xs);

            for(long[] d : h){
                long x = d[0];
                long y = d[1];

                ArrayList<Long> xs = v.get(x+y);
                if(xs==null)continue;
                int l = lb(xs,x+1);
                int r = lb(xs,x+K);
                count -= r-l;
            }
            System.out.println(count);
        }
    }
    static int lb(ArrayList<Long> arr, long t){
        int l = 0;
        int r = arr.size();

        while(l<r){
            int mid = l+(r-l)/2;

            if(arr.get(mid)<t){
                l=mid+1;
            }else{
                r=mid;
            }
        }
        return l;
    }
}
