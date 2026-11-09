import java.io.*;
import java.util.*;

public class Calicodrone {
    static int lowerBound(long[] arr, int n, long target) {
        int left = 0, right = n;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in) );

        int t = Integer.parseInt(br.readLine().trim());
        while (t-- > 0){
            StringTokenizer st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken());
            long k = Long.parseLong(st.nextToken());
            
            long[] east=  new long[n];
            long[] north = new long[n];
 
            int nc = 0;
            int ec = 0;
        
            for (int i = 0; i < n; i++){
                st = new StringTokenizer(br.readLine());
                int x= Integer.parseInt(st.nextToken());
                int y = Integer.parseInt(st.nextToken());
                int z =Integer.parseInt(st.nextToken());
                char dir = st.nextToken().charAt(0);

                long key = ((long)(x + y) << 32) | x;
                if (dir == 'N'){

                    north[nc] = key;
                    nc++;
                }
                else if (dir == 'E'){

                    east[ec] = key;
                    
                    ec++;
                    
                }
            }
            Arrays.sort(north, 0, nc);
            
            long blocked = 0;

            for (int i = 0; i < ec; i++){
                long key = east[i];
                int left = lowerBound(north, nc, key);
                int right = lowerBound(north, nc, key + k);
                blocked += right - left;
        
            }
            System.out.println((long) n*k -blocked);

        }
        
    }
} 