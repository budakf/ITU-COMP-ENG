#include<stdio.h>

int main()
{
    int choice=1,height,width,thickness,i,j,thickness_hold; 

   while(choice!=0)    
      {  
     printf("Enter the height for your rectangle:");
     scanf("%d",&height);  
     while(height>20 || height<1)
       {
         printf("You should new number between 1 and 20 for height.\n");
         printf("Enter the height for your rectangle:");
         scanf("%d",&height);
       }
     
     printf("Enter the width for your rectangle:");
     scanf("%d",&width);
     while(width>20 || width<1)
       {
         printf("You should new number between 1 and 20 for width.\n");
         printf("Enter the width for your rectangle:");
         scanf("%d",&width);
       }
   
     printf("Enter the thickness:");
     scanf("%d",&thickness);
     while(thickness>20 || thickness<1)
       {
         printf("You should new number between 1 and 20 for thickness.\n");
         printf("Enter the thickness for your rectangle:");
         scanf("%d",&thickness);
       }
     
     thickness_hold=thickness;    
   
     if(height>2*thickness && height>=3 && width>=3)//First situation
      {
        for(i=1;i<=thickness;i++)//First step..
          {
            for(j=1;j<=width;j++)
              printf("*");
            printf("\n");   
          }    
        for(i=1;i<=(height-2*thickness_hold);i++)//Most important step..
          {
              while(width<=2*thickness)
               thickness--;
              for(j=1;j<=thickness;j++)
                printf("*");
              for(j=1;j<=(width-2*thickness);j++)
                printf(" ");
              for(j=1;j<=thickness;j++)
                printf("*");
            printf("\n"); 
          }
        thickness=thickness_hold;
       
        for(i=1;i<=thickness;i++)//Last step..
          {
            for(j=1;j<=width;j++)
              printf("*");
            printf("\n");   
          }    
      }     
   
   else if(width>2*thickness && width>=3 && height>=3)//Second situation
      { 
        while(height<=2*thickness)
           thickness--;
         for(i=1;i<=thickness;i++)//First step..
          {
            for(j=1;j<=width;j++)
              printf("*");
            printf("\n");   
          }
        
         for(i=1;i<=(height-2*thickness);i++)//Most important step..
          {
             for(j=1;j<=thickness_hold;j++)
                printf("*");
              for(j=1;j<=(width-2*thickness_hold);j++)
                printf(" ");
              for(j=1;j<=thickness_hold;j++)
                printf("*");
            printf("\n"); 
          }
           
         for(i=1;i<=thickness;i++)//Last step..
           {
             for(j=1;j<=width;j++)
               printf("*");
             printf("\n");   
           }    
      }     
       
   else 
      {
        printf("It is not possible to draw your rectangle with the specified thickness.\nThe rectangle without the thickness option is drawn below:\n");
        for(i=1;i<=height;i++)
         {
           for(j=1;j<=width;j++)
              printf("*");
           printf("\n");
         }    
      }
           printf("Do you want to continue? (1 for Yes, 0 for No):");
           scanf("%d",&choice); 
         while(choice!=1 && choice!=0) 
          {
           printf("You should enter 1 to continue 0 to exit.\n");
           printf("Do you want to continue? (1 for Yes, 0 for No):");
           scanf("%d",&choice);
          }
      }  
         return 0;
}
     
             
               
               
               
               
               
               
               
               
               
               
               
