import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class p2 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        for(int t=Integer.parseInt(br.readLine());t>0;t--) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int n=Integer.parseInt(st.nextToken());
            int r=Integer.parseInt(st.nextToken());
            int[] times = new int[n];
            st = new StringTokenizer(br.readLine());
            for(int i=0;i<n;i++){
                times[i]=Integer.parseInt(st.nextToken());
            }

            int charges=2;
            int rechargeTime=-1;
            int needCharge=0;

            boolean ans=true;
            for(int i=0;i<n;i++){
                if(rechargeTime+r<=times[i]){
                    charges++;
                    needCharge--;
                    if(needCharge==0){
                        rechargeTime=-1;
                    } else {
                        if(rechargeTime+2*r<=times[i]) {
                            charges++;
                            needCharge--;
                        } else{
                            rechargeTime+=r;
                        }
                    }
                }

                if(charges>0){
                    needCharge++;
                    if(rechargeTime==-1){
                        rechargeTime=times[i];
                    }
                    charges--;
                } else{
                    ans=false;
                    break;
                }
            }

            if(ans){
                System.out.println("YES");
            } else{
                System.out.println("NO");
            }
        }
    }
}
