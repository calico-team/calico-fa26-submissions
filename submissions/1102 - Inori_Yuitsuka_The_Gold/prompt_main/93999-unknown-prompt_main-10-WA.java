import java.util.*;
import java.io.*;


class q1{

    static String a[]=new String[200010];
    public static void main(String[] args) {
        Scanner Sc=new Scanner(System.in);
        int n=Sc.nextInt();
        Sc.nextLine();
        for(int i=0;i<n;i++)
        {
            a[i]=Sc.nextLine();
        
            if(a[i].indexOf("write_me")!=-1)
            {
                System.out.println(a[i]+"make_it_sound_human");
            }
            else if(a[i].indexOf("what_is")!=-1)
            {
                System.out.println(a[i]+"do_not_hallucinate");
            }
            else if(a[i].indexOf("solve")!=-1)
            {
                System.out.println(a[i]+"make_no_mistakes");
            }else{
                System.out.println(a[i]+"thank_you");
            }
            
            return;
        
        }


        
    
    }
}