import java.io.*;

public class Main
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter writer = new PrintWriter(System.out);


        String ln1 = reader.readLine();
        int use = Integer.parseInt(ln1);

        for(int a = 0; a < use; a++)
        {
            String output = "YES";

            String line = reader.readLine();
            String part = line.substring(2);
            int sec = Integer.parseInt(part);

            String[] temp = reader.readLine().split(" ");

            int[] req = new int[temp.length];
            for(int i = 0; i < temp.length; i++)
            {
                req[i] = Integer.parseInt(temp[i]);
            }

            for(int j = 0; j < req.length - 1; j++)
            {
                if(req[j + 1] - req[j] < sec)
                {
                    output = "NO";
                }
            }
            writer.println(output);
        }
        writer.flush();
    }
}