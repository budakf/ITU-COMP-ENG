#include<stdio.h>
#include<stdlib.h>
#define BOYUT 300

int factorial(int n)  // 12 ve daha kucuk sayýlarýn faktoriyelini hesaplayan fonksiyon
{
 if(n==0 || n==1)
    return 1;
 else
    return n*factorial(n-1);
}

void factorial_for_big_number(int n)  //12 den buyuk sayýlarýn faktoriyelini hesaplayan fonksiyon
{
   int a[BOYUT]={0,0,6,1,0,0,9,7,4};// 12! in diziye aktarýlmýþ hali..(tersten)
   int array[BOYUT]={0};            // sonucu tutacaðým array
   int m=13;
   int i,j,k;
   int x=0;
   int remain=0;
   int hold=n;
   int number=1;
   
   while(n>12)    
     { 
      for(i=0;i<BOYUT-1;i++)
       { 
         x=remain+a[i]*m;
         remain=x/10;  
      
       if(remain>0)
         {
           array[i]=x%10;
           array[i+1]+=remain;
         }   
       }
       
        for(k=0;k<=BOYUT-1;k++)
         a[k]=array[k];    
    
      n--;
      m++;
    }
      
      printf("%d!:",hold);
 
      for(j=BOYUT-1;j>=0;)
       {
        if(number<=1)
        {                        // array in ilk elemanlarý olan sýfýrlarý ekrana yazdýrmamak için while dongüsünü kullandýk(ilk sýfýr olmayan sayi ile karþýlaþýlana kadar sýfýrlarý atlayýp sýfýr olmayan sayýlarý yazdýrdýk).
        while(array[j]==0)       // sýfýr olmayan sayýlarý yazdýrmaya baþladýktan sonra karþýlaþýlan sýfýrlarý yazdýrmak için if yapýsýný kullandýk..  
          j--;
        number++; 
        }
        printf("%d",array[j]);        
        if(j%3==0 && j!=0)
           printf(",");
        j--;
       }
}
 
int main()
{  
   int n;
   int j;
   printf("Enter:"); 
   scanf("%d",&n);
   
   if(n<0)   
     printf("Invalid Input");
   
   else if(n==0)
   {
    printf("%2d!:Cannot Calculated\n",n-2);   
    printf("%2d!:Cannot Calculated\n",n-1);
    printf("%+2d!:%d",n,factorial(n));           
   }
   
   else if(n==1)
   {
     printf("%d!:Cannot Calculated\n",n-2);   
     printf("%2d!:%d\n",n-1,factorial(n-1));
     printf("%+d!:%d",n,factorial(n)); 
   }
   
   else if(n==2 || n==3 || n==4)
   {
     printf("%d!:%2d\n",n-2,factorial(n-2));  
     printf("%d!:%2d\n",n-1,factorial(n-1));
     printf("%d!:%2d",n,factorial(n)); 
   }
   
    else if(n==5 || n==6 || n==7)
   {
     printf("%d!:%4d\n",n-2,factorial(n-2));  
     printf("%d!:%4d\n",n-1,factorial(n-1));
     printf("%d!:%4d",n,factorial(n)); 
   }
      
    else if(n==8 || n==9)
   {
     printf("%d!:%6d\n",n-2,factorial(n-2));  
     printf("%d!:%6d\n",n-1,factorial(n-1));
     printf("%d!:%6d",n,factorial(n)); 
   }
   
   else if(n==10 || n==11)  
   {
     printf("%2d!:%8d\n",n-2,factorial(n-2));
     printf("%2d!:%8d\n",n-1,factorial(n-1));
     printf("%2d!:%8d\n",n,factorial(n));
   }
   else if(n==12)  
   {
     printf("%2d!:%9d\n",n-2,factorial(n-2));
     printf("%2d!:%9d\n",n-1,factorial(n-1));
     printf("%2d!:%9d\n",n,factorial(n));
   }
   
   else if(n>=169)
     printf("Large Input for array[300]");
   
   else
    {
     if(n==13)
      {
         printf("%2d!:    %9d\n",n-2,factorial(n-2));
         printf("%2d!:    %9d\n",n-1,factorial(n-1));
         factorial_for_big_number(n);      
      }
     else if(n==14)
      {
         printf("%2d!:     %9d\n",n-2,factorial(n-2));
         factorial_for_big_number(n-1); 
         printf("\n");
         factorial_for_big_number(n);
      }
      else if(n==167)
      {
        factorial_for_big_number(n-2);
        printf("\n\n");
        factorial_for_big_number(n-1);
        printf("\n\n");             
        printf("167 is large input for array[300]");
      }
     else if(n==168)
      {
        factorial_for_big_number(n-2);
        printf("\n\n"); 
        printf("%d is large input for array[300]",n-1);
        printf("\n\n"); 
        printf("%d is large input for array[300]",n);
      }
     else
      {             
         factorial_for_big_number(n-2);
         printf("\n\n");
         factorial_for_big_number(n-1);
         printf("\n\n");
         factorial_for_big_number(n);
      }   
   
    }
  getchar();
  getchar();
  return 0;
}
