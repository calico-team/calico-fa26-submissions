
import java.io.*;



public class Main {
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) throws IOException {
        int t = Integer.parseInt(in.readLine());
        for(int i = 0; i<t; i++){
            String z1 = in.readLine();
            String z2 = in.readLine();
            String z12 = z1.substring(0,z1.indexOf(' '));
            String z13 = z1.substring(z1.indexOf(z12));
            int n = Integer.parseInt(z12);
            int r = Integer.parseInt(z13);
            int[] a = new int[n];
            for(int j = 0; j<n; j++){
                String z21 = z2.substring(0,z2.indexOf(' '));
                z2 = z2.substring(z2.indexOf(z21));
                a[j] = Integer.parseInt(z21);
            }
            int k = 2;
            int s = 0;
            int time1 = 0;
            int time2 = 0;
            int time3 = 0;
            for(int f = 0; f<n; f++){
                time1 = time2;
                time2 = time3;
                time3 = a[f];
                if(k<2&&(time3-time2>=r||(time3-time1>=r&&s==0))){
                    k+=1;
                    s = 2;
                }
                k-=1;
                s-=1;
                if(k<0){
                    break;
                }
            }
            if(k<0){
                out.println("NO");
            } else{
                out.println("YES");
            }
        }
    }
}