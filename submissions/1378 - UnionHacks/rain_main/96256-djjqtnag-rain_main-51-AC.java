import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.StringTokenizer;
public class DroneRain {
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
    static class Drone implements Comparable<Drone> {
        int x;
        int diag;
        int east;
        Drone(int x,int y, char dir) {
            this.x=x;
            diag= x+y;
            east = dir=='E' ? 1 : 0;
        }
        public int compareTo(Drone other) {
            if(diag != other.diag) {
                return Integer.compare(diag,other.diag);
            }
            return Integer.compare(x, other.x);
        }
    }
    static long countBlocked(Drone[] drones,int k) {
        Arrays.sort(drones);
        int left=0;
        int east =0;
        long lost=0;
        for (int right=0;right < drones.length; right++) {
            Drone current =drones[right];
            while(left<right && (drones[left].diag!=current.diag || current.x-drones[left].x >= k)) {
                east-=drones[left].east;
                left++;
            }
            if(current.east==0) {
                lost +=east;
            }
            east+= current.east;
        }
        return lost;
    }
    public static void main(String[] args) throws IOException {
        Input in =new Input();
        StringBuilder out= new StringBuilder();
        int rounds =in.nextInt();
        while(rounds-- > 0) {
            int n= in.nextInt();
            int k =in.nextInt();
            Drone[] drones= new Drone[n];
            for (int i=0;i<n; i++) {
                int x =in.nextInt();
                int y= in.nextInt();
                in.nextInt();
                char dir =in.next().charAt(0);
                drones[i]=new Drone(x,y,dir);
            }
            long answer= (long)n*k-countBlocked(drones,k);
            out.append(answer).append('\n');
        }
        System.out.print(out);
    }
}