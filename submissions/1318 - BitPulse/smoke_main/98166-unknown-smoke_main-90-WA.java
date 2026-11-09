import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        while (T-- > 0) {
            int N = sc.nextInt(), R = sc.nextInt();
            long t1 = 0, t2 = 0;
            boolean ok = true;
            for(int i=0;i<N;i++){
                long a = sc.nextLong();
                if(!ok) continue;
                if(t1 <= t2){
                    if(t1 <= a){
                        long oldt1 = t1;
                        t1 = a + R;
                        if(oldt1 <= a && t2 <= a){
                            t2 = Math.max(t2, t1);
                        }
                    }else ok=false;
                }else{
                    if(t2 <= a){
                        long oldt2 = t2;
                        t2 = a + R;
                        if(oldt2 <= a && t1 <= a){
                            t1 = Math.max(t1, t2);
                        }
                    }else ok=false;
                }
            }
            System.out.println(ok?"YES":"NO");
        }
    }
}