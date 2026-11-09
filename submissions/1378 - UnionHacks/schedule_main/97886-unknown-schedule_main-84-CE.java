import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;
public class CoursePlan {
    static class Input {
        BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st =new StringTokenizer("");
        int nextInt() throws IOException {
            while(!st.hasMoreTokens()) {
                st= new StringTokenizer(br.readLine());
            }
            return Integer.parseInt(st.nextToken());
        }
    }
    static int maxCourses(int[] prereq,int semesters, int limit) {
        int n=prereq.length-1;
        int[] depth =new int[n+1];
        int[] count=new int[n+1];
        int[] path =new int[n];
        for (int i=1;i<=n; i++) {
            if(depth[i]!=0) {
                continue;
            }
            int course=i;
            int size =0;
            while(course!=0 && depth[course]==0) {
                path[size++]=course;
                course =prereq[course];
            }
            while(size>0) {
                course=path[--size];
                depth[course] =depth[prereq[course]]+1;
                count[depth[course]]++;
            }
        }
        int deeper=0;
        long removed =0;
        for (int d=n;d>0;d--) {
            deeper +=count[d];
            int terms= Math.max(0,semesters-d+1);
            long seats =(long)terms*limit;
            if(deeper-seats > removed) {
                removed=deeper-seats;
            }
        }
        return n-(int)removed;
    }
    public static void main(String[] args) throws IOException {
        Input in =new Input();
        StringBuilder out= new StringBuilder();
        int rounds =in.nextInt();
        while(rounds-- >0) {
            int n= in.nextInt();
            int m =in.nextInt();
            int k= in.nextInt();
            int[] prereq =new int[n+1];
            for (int i=1;i<=n;i++) {
                prereq[i]=in.nextInt();
            }
            int answer =maxCourses(prereq,m,k);
            out.append(answer).append('\n');
        }
        System.out.print(out);
    }
}