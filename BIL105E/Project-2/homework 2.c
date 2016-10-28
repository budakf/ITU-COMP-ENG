/*
  Name: Fatih Budak
  Student No:150130006
  Course:BIL105 E
  Description: Homework 2 
*/

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define PI 3.14159266

double memory;
double Result=0; // global variables

double mod_for_power(double a,double b)//
{
  while(a>=b)
    a-=b;
  return a;          
}

double power(double a,int b)// 
{
   double re_result=1,result=1;    
   if(b==0)
     return 1;
   else if(b>0)
    { 
      for(;b>=1;b--)
        result*=a;
        
      Result=result;
      return result;
    }
   else
    { 
      b*=-1;  
      for(;b>0;b--)
        result*=a;
      re_result=1/result;
    
    Result=re_result;
    return re_result;
    }
}

long long int faktoriyel(double a)//
{   
  if(a==1 || a==0) 
    Result=1;
  else if(a<0)
    Result=a;
  else if(mod_for_power(a,2)!=1 && mod_for_power(a,2)!=0 && mod_for_power(a,2)!=-1)
    Result=0;     
  else if(a>1 && a<21)
    Result=a*(double)faktoriyel(a-1);
  
  else if(a>=21)
    Result=-a; 
  return (long long int)Result;
}       

double sin(double a)//
{
 double isaretci=1,result=0;
 int i;
 if(a<0)
   while(a<0)
     a+=360;
 if(a>360)
   while(a>360)
     a-=360;
 if(a>=0 && a<=90)
  a=a*PI/180;
 if(a>90 && a<=180)
  a=(180-a)*PI/180;
 if(a>180 && a<=270)
  a=(180-a)*PI/180;
 if(a>270 && a<=360)
  a=(a-360)*PI/180;
 
 for(i=1;i<20;i+=2,isaretci*=-1)
  result+=(power(a,i)/(double)faktoriyel(i))*isaretci;
    
    Result=result;
    return Result;
}

double cos(double a)//
{    
  Result=sin(90-a);//sin fonksiyonu cos fonksiyonunun 90 derece önünden gider.
  return Result;
} 

double tan(double a)//
{
  if(cos(a)!=0)
   Result=sin(a)/cos(a);
  else
   Result=a;// özel durum*************
  return Result;
}

double absolute(double a)//
{
  if(a<0)      
    Result=-1.0*a;
  else
    Result=a;

  return Result;
}

double exponent(double b,double a)//
{
    Result=b*(double)power(10.0,(int)a);
    return Result;    
}

double add(double a, double b)//
{
  Result=a+b;
  return Result;
}

double subtract(double a, double b)//
{
  Result=a-b;
  return Result;
}

double multipy(double a, double b)//
{
  Result=a*b;
  return Result;
}

double divide(double a, double b)//
{
  if(b!=0)
    Result=a/b;
  else 
   Result=0;
   
  return Result;
}

double mod(double a,double b)//
{
  while(a>=b)
    a-=b;
  Result=a;
  return a;          
}
double pi()
{
  int i,isaret=1; 
  double result=0;    
  for(i=1;i<100000;i+=2,isaret*=-1)
       result+=((double)4/i)*isaret; 
  
  Result=result;
  return Result;  
}

void error_message(char *array)
{
           printf("Ýnvalid input\n");
           printf("Choose from the operators below:\n");
           printf("----------------------------------------------------------\n");
           printf("  sine (S), cosine (N), tangent (T), exponent (E)\n");
           printf("  power (W), absolute (A), factorial (F)\n");
           printf("  add (+), subtract (-), divide(/), multiply(*), modulus (%)\n"); 
           printf("  Pi (P) \n");
           printf("  Quit(Q)\n");
           printf("  Memory (M)\n");
           printf("  Clear (C)\n");
           printf("  Memory Clear (MC)\n");
           printf("  Memory Return (MR)\n");
           printf("----------------------------------------------------------\n");
           printf("  Enter user input: Q\n");
}

void switch_function(char *array,double i)
{
switch(*array)
      {
      
       case 'S'://
            Result=sin(i);
            printf("Sin(%.0f)=%f\n",i,Result);
            break;
       case 'N'://
            Result=cos(i);
            printf("Cos(%.0f)=%f\n",i,Result);
            break;
       case 'T'://
            Result=tan(i);
            if(i!=0)
             {
              if(Result!=i)
                printf("Tan(%.0f)=%.2f\n",i,tan(i));
              else
                printf("Invalid Operation\n");
             }
            else
              printf("Tan(%.0f)=0\n",i);
            break;
       case 'E':
            Result=exponent(Result,i);
            printf("%.0f\n",Result);
            break;
       case 'W':
            if((mod_for_power(i,2)!=1 && mod_for_power(i,2)!=0 ))
             printf("Ýnvalid Operation\n"); 
            else if(i>=0)
            {
              Result=power(Result,(int)i);
              printf("%f\n",Result);
            }
            else if(i<=0 && (mod_for_power(i,2)==1 || mod_for_power(i,2)==0))
            {
              Result=power(Result,(int)i);
              printf("%f\n",Result);
            }
            
            break;
       case 'A'://
            Result=absolute(Result);
            printf("%.2f\n",Result);
            break;
       case 'F'://
            Result=faktoriyel(Result);
            if(Result>0) 
               printf("%.0f\n",Result);
            else if(Result==i)
               printf("Ýnvalid operation\n");
            else if(Result==-i)
                printf("Too much bigger integer to calculate factorial\n");
            else
               printf("this factorial cannot be calculated due to being a decimal number \n");
            break;
       case '+':
            Result=add(Result,i);
            printf("%.2f\n",Result);
            break;
       case '-':
            Result=subtract(Result,i);
            printf("%.2f\n",Result); 
            break;
       case '*':
            Result=multipy(Result,i);
            printf("%.2f\n",Result); 
            break;
       case '/':
            Result=divide(Result,i);
            if(i!=0)
              printf("%.2f\n",Result);
            else if(i==0)
              printf("The division cannot be calculated \n");
            break;
       case '%':
            Result=mod(Result,i);
            printf("%.2f\n",Result);
            break;
       case 'P':// 
            Result=pi();
            printf("%.2f\n",Result);
            break;
       case 'C'://
            Result=0;
            break;
       case 'M'://            
         if(array[1]=='C')
            memory=0;
         else if(array[1]=='R')
            {
             printf("%f\n",memory);
             Result=memory; 
            }
         else  
            memory=Result;
         break;  
       case ' ': case '\n':
            break;
       case 'Q':
           printf("Quit..");
           break;
            
       default:
           error_message(array);
           break;
      } 
}

int main()
{     
  char array[100],array_2[100];
  double i;
   
  
  printf("Enter user input:");
  scanf("%s",array);
  
  while(*array!='Q')
  {  
   if(isdigit(*array) || (*array=='-' && (isdigit(*(array+1)))))// ilk girilen deger sayi ise..
    { 
      Result=atof(array);
      printf("Enter user input:");
      scanf("%s",array);
      if(*array=='S' || *array=='N'||*array=='T'||*array=='A'||*array=='F'||*array=='P'||*array=='M'||*array=='C')
        switch_function(array,Result);
      else if(*array=='+' || *array=='-'||*array=='*'||*array=='/'||*array=='%'||*array=='W'||*array=='E')
       {
         printf("Enter user input:");
         scanf("%s",array_2);
        if(isdigit(*array_2) || (*array_2=='-' && isdigit(*(array_2+1)))) 
        {
          i=atof(array_2);
          switch_function(array,i);                                  
        }
        else
        {     // input yapýlacak iþleme uygun deðilse (yani % den sonra /  gibi bir iþlem geldiyse sayý girene kadar while kalýr sayý girince çýkar ve iþlemi yaptýrýr.  )
          while(!(isdigit(*array_2)) && !(isdigit(*(array_2+1))))
           {
             printf("Invalid input for the operator %c\n",*array);
             printf("Enter user input:");
             scanf("%s",array_2);
           }
          i=atof(array_2);
          switch_function(array,i);
        }
       }
      else if(*array=='Q')
         break;
      else
          error_message(array);  
                                      
    }// ilk girilen deger sayi ise..
    
    
   else // ilk girilen deger sayi deðilse ise..
    {
      if(*array=='S' || *array=='N'||*array=='T'||*array=='A'||*array=='F'||*array=='P'||*array=='M'||*array=='C')
        switch_function(array,Result);
      else if(*array=='+' || *array=='-'||*array=='*'||*array=='/'||*array=='%'||*array=='W'||*array=='E')
       {
         printf("Enter user input:");
         scanf("%s",array_2);
         if(isdigit(*array_2)|| isdigit(*(array_2+1)))
          {
            i=atof(array_2);
            switch_function(array,i);
          }
         else//
          {
           while(!(isdigit(*array_2)) && (!isdigit(*(array_2+1)))) 
            {
              printf("Invalid input for the operator %c\n",*array);
              printf("Enter user input:");
              scanf("%s",array_2);
            }
           i=atof(array_2);
           switch_function(array,i);
          }
       }   
    else
      error_message(array);
    }
    printf("Enter user input:");
    scanf("%s",array);
  }
  
    printf("Quit..\n");

   return 0;
}
