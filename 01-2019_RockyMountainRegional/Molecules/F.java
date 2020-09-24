/*
Systems of equations/Gaussian elimination
*/
import java.util.*;
import java.io.*;
import java.math.*;
import java.text.*;

   public class F
   {
      public static void main(String hi[]) throws Exception
      {
         BufferedReader infile = new BufferedReader(new InputStreamReader(System.in));
         StringTokenizer st = new StringTokenizer(infile.readLine());
         int N = Integer.parseInt(st.nextToken());
         int M = Integer.parseInt(st.nextToken());
         int[][] points = new int[N][2];
         for(int i=0; i < N; i++)
         {
            st = new StringTokenizer(infile.readLine());
            points[i][0] = Integer.parseInt(st.nextToken());
            points[i][1] = Integer.parseInt(st.nextToken());
         }
         ArrayDeque<Integer>[] edges = new ArrayDeque[N];
         for(int i=0; i < N; i++)
            edges[i] = new ArrayDeque<Integer>();
         for(int i=0; i < M; i++)
         {
            st = new StringTokenizer(infile.readLine());
            int a = Integer.parseInt(st.nextToken())-1;
            int b = Integer.parseInt(st.nextToken())-1;
            edges[a].add(b);
            edges[b].add(a);
         }
         double[][] leftx = new double[N][N];
         double[] rightx = new double[N];
         double[][] lefty = new double[N][N];
         double[] righty = new double[N];
         for(int i=0; i < N; i++)
         {
            if(points[i][0] == -1)
            {
               leftx[i][i] = lefty[i][i] = edges[i].size();
               for(int next: edges[i])
                  leftx[i][next] = lefty[i][next] = -1;
            }
            else
            {
               leftx[i][i] = lefty[i][i] = 1;
               rightx[i] = points[i][0];
               righty[i] = points[i][1];
            }
         }
         double[] resX = gauss(leftx, rightx);
         double[] resY = gauss(lefty, righty);
         StringBuilder sb = new StringBuilder();
         DecimalFormat df = new DecimalFormat("#####0.0000000");
         for(int i=0; i < N; i++)
            sb.append(df.format(resX[i])+" "+df.format(resY[i])+"\n");
         System.out.print(sb);
      }
      //borrowed from Princeton site
      public static double[] gauss(double[][] A, double[] b) 
      {
         int N = b.length;
         for(int p = 0; p < N; p++) 
         {
            // find pivot row and swap
            int max = p;
            for (int i = p + 1; i < N; i++)
               if (Math.abs(A[i][p]) > Math.abs(A[max][p]))
                  max = i;
            double[] temp = A[p]; A[p] = A[max]; A[max] = temp;
            double   t    = b[p]; b[p] = b[max]; b[max] = t;
            // pivot within A and b
            for (int i = p + 1; i < N; i++) {
                double alpha = A[i][p] / A[p][p];
                b[i] -= alpha * b[p];
                for (int j = p; j < N; j++) {
                    A[i][j] -= alpha*A[p][j];
                }
            }
         }
         // back substitution
         double[] x = new double[N];
         for (int i = N - 1; i >= 0; i--) 
         {
             double sum = 0.0;
             for (int j = i + 1; j < N; j++)
                 sum += A[i][j]*x[j];
             x[i] = (b[i]-sum)/A[i][i];
         }
         return x;
      }
   }