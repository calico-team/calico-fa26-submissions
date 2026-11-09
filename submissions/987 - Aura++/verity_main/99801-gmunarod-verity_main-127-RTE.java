import java.util.*;
import java.io.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.FileReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;

class Reader extends BufferedReader
{

   StringTokenizer st;

   public Reader()
   {
       super(new InputStreamReader(System.in));
   }

   public Reader(String fileName) throws IOException
   {
       super(new FileReader(fileName));
   }

   public void skipLine() throws IOException
   {
       String line = readLine();

       if(line == null) return;

       st = new StringTokenizer(line);
   }

   public String next() throws IOException
   {
       while(st == null || !st.hasMoreTokens())
       {
           String line = readLine();
           if(line == null) return null;
           st = new StringTokenizer(line);
       }

       return st.nextToken();
   }


   public int nextInt() throws IOException
   {
       return Integer.parseInt(next());
   }

   public double nextDouble() throws IOException
   {
       return Double.parseDouble(next());
   }
   public boolean nextBoolean() throws IOException
   {
       return Boolean.parseBoolean(next());
   }
   public long nextLong() throws IOException
   {
       return Long.parseLong(next());
   }

}

public class MyProgram
{
    static Reader scan = new Reader();
    static PrintWriter out = new PrintWriter(System.out);
    public static void main(String[] args) throws IOException
    {
       int testCases = scan.nextInt();
       for (int num = 0; num < testCases; num++)
       {
           
           int wordLength = scan.nextInt();
           int numLetters = scan.nextInt();
           String [] lettersList = new String [numLetters];
           for (int q = 0; q < lettersList.length; q++)
           {
               lettersList[q] = scan.next();
           }

            String [] guess = new String[wordLength];
            for (int j = 0; j < guess.length; j++)
            {
                guess[j] = lettersList[(int) (Math.random() * numLetters)];
            }
            for(int y = 0; y < guess.length; y++)
            {
                out.print(guess[y]);
            }
            out.println();
            out.flush();
            String response = scan.next();
            while (!response.equals("CORRECT"))
            {
                for (int x = 0; x < wordLength; x++)
                {
                    ArrayList<String> pastLets = new ArrayList<String>();
                    if (!response.substring(x,x+1).equals(guess[x]))
                    {
                        pastLets.add(guess[x]);
                        boolean newNum = true;
                        while (newNum)
                        {
                            guess[x] = lettersList[(int) (Math.random() * wordLength)];
                            for (int w = 0; w < pastLets.size(); w++)
                            {
                                if (!guess[x].equals(pastLets.get(w)))
                                {
                                    newNum = false;
                                }
                            }
                        }
                    }
                }
                for(int y = 0; y < guess.length; y++)
                {
                    out.print(guess[y]);
                }
                out.println();
                out.flush();
                response = scan.next();
            }
           
           
           
          
       }
    }
}