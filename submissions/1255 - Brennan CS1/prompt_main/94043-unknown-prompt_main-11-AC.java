import java.io.*;
import java.util.*;
public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        int N = Integer.parseInt(br.readLine());
        ArrayList<String> list = new ArrayList();
        for (int i = 0; i < N; i++) {
            String line = br.readLine();
            String temp = line;
            boolean check = false;
            if(line.contains("write_me")){
                temp+="make_it_sound_human";
                check=true;
            }

            if(line.contains("what_is")){
                temp+="do_not_hallucinate";
                check=true;
            }

            if(line.contains("solve")){
                temp+="make_no_mistakes";
                check=true;
            }

            if(!check){
                temp+="thank_you";
            }
            list.add(temp);
        }
        for (String s : list) {
            bw.write(s + "\n");
        }
        bw.close();
        br.close();
    }
}