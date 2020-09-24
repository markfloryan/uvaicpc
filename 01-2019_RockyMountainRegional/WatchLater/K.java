/*
Bitmask DP
*/
import java.util.*;
import java.io.*;
import java.math.*;

   public class K
   {
      public static void main(String hi[]) throws Exception
      {
         BufferedReader infile = new BufferedReader(new InputStreamReader(System.in));
         StringTokenizer st = new StringTokenizer(infile.readLine());
         int N = Integer.parseInt(st.nextToken());
         int K = Integer.parseInt(st.nextToken());
         String input = infile.readLine();
         int[] arr = new int[N];
         int boof = 0;
         int[] map = new int[6969];
         Arrays.fill(map, 420);
         for(int i=0; i < N; i++)
         {
            char c = input.charAt(i);
            if(map[c] == 420)
               map[c] = boof++;
            arr[i] = map[c];
         }
         arr = prune(arr);
         N = arr.length;
         //precompute
         ArrayList<Integer>[] buckets = new ArrayList[K];
         for(int i=0; i < K; i++)
            buckets[i] = new ArrayList<Integer>();
         for(int a=0; a < N; a++)
         {
            int mask = 0;
            boolean found = false;
            for(int i=a+1; i < N; i++)
            {
               if(arr[i] == arr[a])
               {
                  found = true;
                  break;
               }
               mask |= 1<<arr[i];
            }
            if(found)
               buckets[arr[a]].add(mask);
         }
         int[] dp = new int[1<<K];
         Arrays.fill(dp, N+N+N);
         dp[0] = 0;
         for(int mask=0; mask < dp.length; mask++)
         {
            int[] cost = new int[K];
            Arrays.fill(cost, 1);
            for(int v=0; v < K; v++)
               for(int middle: buckets[v])
                  if((mask|middle) != mask)
                     cost[v]++;
            for(int b=0; b < K; b++)
               if((mask&(1<<b)) == 0)
               {
                  int nextmask = mask|(1<<b);
                  dp[nextmask] = Math.min(dp[nextmask], dp[mask]+cost[b]);
               }
         }
         System.out.println(dp[(1<<K)-1]);
      }
      public static int[] prune(int[] arr)
      {
         ArrayList<Integer> ls = new ArrayList<Integer>();
         ls.add(arr[0]);
         for(int i=1; i < arr.length; i++)
            if(arr[i] != ls.get(ls.size()-1))
               ls.add(arr[i]);
         int[] brr = new int[ls.size()];
         for(int i=0; i < ls.size(); i++)
            brr[i] = ls.get(i);
         return brr;
      }
   }