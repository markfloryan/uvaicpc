/*
Polynomial Hash
*/
import java.util.*;
import java.io.*;
import java.math.*;

   public class J
   {
      static final long BASE1 = 37L;
      static final long MOD = 1000000021L;
      public static void main(String hi[]) throws Exception
      {
         long[] pow1 = new long[1000001];
         pow1[0] = 1L;
         for(int i=1; i <= 1000000; i++)
            pow1[i] = (pow1[i-1]*BASE1)%MOD;
         long invbase1 = power(BASE1, MOD-2, MOD);
         BufferedReader infile = new BufferedReader(new InputStreamReader(System.in));
         StringTokenizer st = new StringTokenizer(infile.readLine());
         int N = Integer.parseInt(st.nextToken());
         Word[] arr = new Word[N];
         for(int i=0; i < N; i++)
            arr[i] = new Word(infile.readLine(), i);
         Arrays.sort(arr, (x, y) -> {
            return x.str.length()-y.str.length();
         });
         ArrayList<Word> typos = new ArrayList<Word>();
         HashSet<Long> hashes = new HashSet<Long>();
         HashSet<String> set = new HashSet<String>();
         for(int qw=0; qw < N; qw++)
         {
            String curr = arr[qw].str;
            int M = curr.length();
            long[] prefix = new long[M];
            prefix[0] = curr.charAt(0);
            for(int i=1; i < M; i++)
            {
               prefix[i] = prefix[i-1]+(curr.charAt(i)*pow1[i])%MOD;
               if(prefix[i] >= MOD)
                  prefix[i] -= MOD;
            }
            if(M > 1)
            {
               boolean added = false;
               if(hashes.contains(prefix[M-2]))
               {
                  String temp = curr.substring(0, M-1);
                  if(set.contains(temp))
                  {
                     typos.add(arr[qw]);
                     added = true;
                  }
               }
               if(hashes.contains((invbase1*(prefix[M-1]-prefix[0]+MOD))%MOD) && !added)
               {
                  String temp = curr.substring(1);
                  if(set.contains(temp))
                  {
                     typos.add(arr[qw]);
                     added = true;
                  }
               }
               if(!added)
               {
                  for(int mid=1; mid < M-1; mid++)
                  {
                     long left = prefix[mid-1];
                     long right = prefix[M-1]-prefix[mid]+MOD;
                     right = (right*invbase1)%MOD;
                     long key = left+right;
                     if(key >= MOD)
                        key -= MOD;
                     if(hashes.contains(key))
                     {
                        String temp = curr.substring(0, mid)+curr.substring(mid+1);
                        if(set.contains(temp))
                        {
                           typos.add(arr[qw]);
                           break;
                        }
                     }
                  }
               }
            }
            hashes.add(prefix[M-1]);
            set.add(curr);
         }
         Collections.sort(typos, (x, y) -> {
            return x.dex-y.dex;
         });
         if(typos.size() == 0)
            System.out.println("NO TYPOS");
         else
         {
            StringBuilder sb = new StringBuilder();
            for(Word w: typos)
               sb.append(w.str+"\n");
            System.out.print(sb);
         }
      }
      public static long power(long x, long y, long p) 
      { 
         //0^0 = 1
         long res = 1L;      
         x = x%p;  
         while(y > 0) 
         { 
            if((y&1)==1) 
               res = (res*x)%p;
            y >>= 1;
            x = (x*x)%p;  
         } 
         return res; 
      }
   }
   class Word
   {
      public String str;
      public int dex;
      
      public Word(String a, int b)
      {
         str = a;
         dex = b;
      }
   }