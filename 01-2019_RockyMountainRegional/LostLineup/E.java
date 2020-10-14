/*
Greedy/Sorting
*/
import java.util.*;
import java.io.*;
import java.math.*;

   public class E
   {
      public static void main(String hi[]) throws Exception
      {
         BufferedReader infile = new BufferedReader(new InputStreamReader(System.in));
         StringTokenizer st = new StringTokenizer(infile.readLine());
         int N = Integer.parseInt(st.nextToken());
         Thing[] arr = new Thing[N-1];
         st = new StringTokenizer(infile.readLine());
         for(int i=0; i < N-1; i++)
            arr[i] = new Thing(i+2, Integer.parseInt(st.nextToken()));
         Arrays.sort(arr);
         System.out.print("1 ");
         for(Thing x: arr)
            System.out.print(x.dex+" ");
      }
   }
   class Thing implements Comparable<Thing>
   {
      public int dex;
      public int val;
      
      public Thing(int a, int b)
      {
         dex = a;
         val = b;
      }
      public int compareTo(Thing oth)
      {
         return val-oth.val;
      }
   }