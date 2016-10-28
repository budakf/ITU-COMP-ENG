#include <stdio.h> 
#include <string.h>      
#include <stdlib.h>         
#include <sys/types.h>     
#include <sys/shm.h>       
#include <errno.h>          
#include <semaphore.h>      
#include <fcntl.h>  


sem_t *s1, *s2, *sm;  
char *array;                   
int *p,*q;
 
void yayinla() {   
        sem_wait(s2);
          sem_wait(sm);
				if(*p%3==1)
					strcpy(array,"Yeni Yiliniz kutlu olsun!");
				else if(*p%3==2)
					strcpy(array,"Herkese iyi tatiller!");
				else
					strcpy(array,"Bugun Madonnanin dogum gunu. ");

        	    printf("Haber kaynagi %d yayinladi =====>%s\n",*p,array);
          sem_post(sm);
        sem_post(s1);
   
}
 
void haberi_oku(int n){ 
        sem_wait(s1);
          sem_wait(sm);
         		printf("\tAbone %d Haber %d i okudu\n",(*q)++,*p);
		
		if(*q<n+1){
			sem_post(s1);
		}	
			
		sem_post(sm);	 
							
		if(*q>=n+1) {
			(*p)++; 
			*q=1;    
			sem_post(s2);	     		
		} 
			
    
}


int main (){

    int i;                       
    int shmid,shmid2,shmid3;            
                           
	key_t key=4687; 
    key_t key2=4688;
	key_t key3=4689;						
		
	// shmget() paylasilan bellekte tahsis islemi yapar.	
    shmid = shmget (key2, sizeof (char)*100, 0644 | IPC_CREAT); 		// Shared memories 
	shmid2= shmget(key,sizeof(int),IPC_CREAT | 0644);
	shmid3= shmget(key3,sizeof(int),IPC_CREAT | 0666);
	
    if (shmid < 0){                           
        perror ("shmget\n");				//  Hata kontrolleri
        exit (1);
    }
    
    if (shmid2 < 0){                          
        perror ("shmget\n");
        exit (1);
    }
    
	if (shmid3 < 0){                          
        perror ("shmget\n");
        exit (1);
    }

    
	//shmat() paylasilan  bellegin proses tarafindan kullanilmasini saglar.
    array = (char *) shmat (shmid, NULL, 0); 
 	p= (int *) shmat (shmid2, NULL, 0);
	q= (int *) shmat (shmid3, NULL, 0);	
	*p=1;
	*q=1;
	
   		
	int m,n;
	printf("Haber kaynagi prosesi sayisini giriniz:");
	scanf("%d",&m);	
	
	printf("Abone proses sayisini giriniz:");
	scanf("%d",&n);	
	printf("\n");
    pid_t pid[m],temp;

	s1 = sem_open ("Semaf1", O_CREAT | O_EXCL, 0644,0 );  // sem_open() ile isimli semafor olusturduk ismi:Semaf
    sem_unlink ("Semaf1");      //eðer semafor Calisma sirasinda bir sorunla karsilasirsa  sem_unlink semaforun yokedilmesini saglar  
	
	s2 = sem_open ("Semaf2", O_CREAT | O_EXCL, 0644, 1);  
    sem_unlink ("Semaf2");      

	sm = sem_open ("Semaf3", O_CREAT | O_EXCL, 0644, 1); 
    sem_unlink ("Semaf3");     


	pid[0]=getpid();     // Anne prosesin pid sini arrayin ilk elemanina attik
     
    for (i = 1; i <= m; i++){   //Haber kaynagi proseslerini fork'ladik
        pid[i] = fork ();
        if (pid[i] < 0)              
            printf ("Fork error.\n");
        else if (pid[i] == 0)	
		  break;      
		            
    }

	int j=1;

	if(getpid()!=pid[0]) //Cocuk proses ise yayinla 
		yayinla();	
	
	else if(getpid()==pid[0]){	//Anne proses ise Abone prosesleri fork'la
		
		for (i = 1; i <=n; i++){
       		temp = fork();
        	if (temp < 0)              
             	 printf ("Fork error.\n");
        	else if (temp == 0)	
		 		 break;      
		          
    	}
	   	
		if(temp==0)
			while(j++<=m)			
				haberi_oku(n);
					
			
		}	   
   
    
    if (pid[0]==getpid()){								//Anne proses

        while (pid[0] = waitpid (-1, NULL, 0)){	//anne proses sonlanmak icin cocuk prosesleri bekliyor 
            if (errno == ECHILD)
                break;
        }

        
        shmdt (array);					//	shmdt() fonksiyonu, prosesin bellek bölgesini kullanmasi sona erdiginde bellek ile olan iliskisi bitirmektedir.
        shmctl (shmid, IPC_RMID, 0);	//  Bellek bolgesinin kullanimi bittiginde stmctl() kullanilarak sisteme geri verilmelidir..
        
        shmdt (p);
        shmctl (shmid2, IPC_RMID, 0);
		
		shmdt (q);
        shmctl (shmid3, IPC_RMID, 0);
        
 
        sem_destroy (s1);
		sem_destroy (s2);
		sem_destroy (sm);
        exit (0);
    } 


}

