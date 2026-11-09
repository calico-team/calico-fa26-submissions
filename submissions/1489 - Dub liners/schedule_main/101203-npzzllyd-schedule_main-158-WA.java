import java.io.*;
import java.util.*;

public class p6 {

    static class sort implements Comparator<int[]>{
        public int compare(int[] a, int[]b){
            if(a[0]==b[0]){
                return a[2]-b[2];
            }
            return a[0]-b[0];
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        for(int t=Integer.parseInt(br.readLine());t>0;t--) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int n=Integer.parseInt(st.nextToken());
            int m=Integer.parseInt(st.nextToken());
            int k=Integer.parseInt(st.nextToken());
            int[] p = new int[n+1];
            st = new StringTokenizer(br.readLine());
            Queue<int[]> q = new ArrayDeque<>();
            for(int i=1;i<=n;i++){
                p[i]=Integer.parseInt(st.nextToken());
                q.add(new int[]{i,p[i]});
            }

            int[][] plzWork = new int[n+1][4]; //0 is order, 1 is the id of pre req
            for(int i=0;i<n+1;i++){
                Arrays.fill(plzWork[i],-1);
            }
            int curr=1;
            while(!q.isEmpty()){
                int[] stuff = q.poll();
                int i =stuff[0];
                int pi=stuff[1];

                if(pi==0){
                    plzWork[i][0]=0;
                    plzWork[i][2]=curr;
                    plzWork[i][3]=i;
                    curr++;
                } else if (plzWork[pi][0]!=-1){
                    plzWork[i][0]=plzWork[pi][0]+1;
                    plzWork[i][1]=pi;
                    plzWork[i][2]=plzWork[pi][2];
                    plzWork[i][3]=i;
                } else{
                    q.add(stuff);
                }

            }
            Arrays.sort(plzWork,new sort());

            PriorityQueue<int[]> saveMe = new PriorityQueue<>(new sort());
            for(int i=1;i<=n;i++){
                saveMe.add(new int[]{plzWork[i][0],plzWork[i][1],plzWork[i][2],plzWork[i][3]});
            }
            //add stuff if same
            int ans=0;
            for(int i=0;i<m;i++){
                int[] ids = new int[n+1];
                for(int j=0;j<k;j++){
                    if(!saveMe.isEmpty()){
                        int[] stuff = saveMe.peek();
                        int place=stuff[0];
                        int preReq=stuff[1];
                        int group=stuff[2];
                        int id=stuff[3];
                        if(preReq!=-1&&ids[preReq]==1){
                            continue;
                        }

                        ans++;
                        ids[id]=1;
                        saveMe.poll();
                    }
                }
            }
            System.out.println(ans);
        }
    }
}
