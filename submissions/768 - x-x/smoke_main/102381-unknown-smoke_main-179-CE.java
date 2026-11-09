import java.util.Scanner;
public class Main {
    public static void main(String [] args) {
        Scanner sc=new Scanner(System.in);
        int T=sc.nextInt();
        for(int i=1;i<=T;i++){
            int n=sc.nextInt();
            int r=sc.nextInt();
            int y=2;
            int k=-1;
            int flag=0;

            for(int j=1;j<=n;j++){
                int t=sc.nextInt();
                while(k != -1 && t - k >= r){
                    y++;
                    if(y == 2){
                        k = -1;
                    }else{
                        k += r;
                    }
                }
                if(y <= 0){
                    flag = 1;
                }
                if(flag == 1){
                    continue;
                }
                y -= 1;
                if (y < 2 && k == -1){
                    k = t;
                }
            }
            if(flag==1) System.out.println("NO");
            else System.out.println("YES");
        }
	sc.close();
    }
}