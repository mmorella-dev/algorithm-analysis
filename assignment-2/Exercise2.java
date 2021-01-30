/* package codechef; // don't place package name! */
// Copyright ahmede 2020

import java.util.Scanner;

/* Name of the class has to be "Main" only if the class is public. */
class Exercise2 {
        
    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        int[] numbers = { 10, 5, 15, 12};
        int highest;
        int lowest;
        double avg;
        highest =  myMax(numbers);
        avg = myAvg(numbers);
 
        System.out.println("The highest number " + highest); 
        System.out.println("The average of the numbers: " + avg);
 
        int[] outNumbers = myCopy(numbers);

        System.out.println("The oroginal array");
        printNumbers(outNumbers);

        myReverse(outNumbers);

        System.out.println("The reverse array");
        printNumbers(outNumbers);
         
        System.out.println("These are the prime numbers in the array");
        printPrimeNumbers(outNumbers);
        
    }
    public static int  myMax(int[] a) {
       int max = a[0];
       for(int i=1; i < a.length; i++)
          if ( a[i] > max)
                max = a[i];

    return max; 
  }

   public static double myAvg(int[] a) {
     int n = a.length;
     double sum = 0.0;
     for (int i=0; i < n; i++)
         sum += a[i];

     double average = sum /n;
     return average; 
    }
    public static int[] myCopy(int[] a) {
          int n = a.length;
          int [] b = new int[n];
          for(int i=0; i < n; i++)
             b[i] = a[i];

      return b; 
    }

    public static void printNumbers(int[] a){
      for(int i=0; i < a.length; i++)
        System.out.println(a[i]);  
       }

    public static void myReverse(int[] a) {
       int n = a.length;
       for (int i = 0; i < n/2; i++) {
          int temp = a[i];
          a[i] = a[n- i-1];
          a[n - i - 1] = temp;  

      }

   }

    public static boolean isPrime(long num) {
       if ( num < 2) return false;
       for (long i = 2; i * i <= num; i++)
              if ( num % i == 0) return false;
       return true;
 
    }

    public static void printPrimeNumbers(int[] a){
      for (int i=0; i < a.length; i++)
         if (isPrime(a[i]))
            System.out.println(a[i]);
    } 
}
