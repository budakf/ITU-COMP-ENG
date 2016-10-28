/*Fatih Budak
  150130006
  Ýþletim Sistemleri 
  Ödev-2
*/

#include <stdio.h>          
#include <stdlib.h>         
#include <sys/types.h>     
#include <sys/shm.h>       
#include <errno.h>          
#include <semaphore.h>      
#include <fcntl.h>          

int *array; 
int *array2;                   
int *p=0;

void* func(int *id){    // Ýstenilen iþlemlerin yapýldýðý fonksiyon

	if(*id==0){
		printf("Process1 calisiyor...\n");
		int i;
		for(i=0;i<10;i++)
			array[i]=i;
		printf("T1 alanindaki sayilar: ");	
		for(i=0;i<10;i++){
			if(i!=9)
				printf("%d,", array[i]);
			else
				printf("%d", array[i]);
		}
		printf("\n");
		
	}

	if(*id==1){

		printf("Process2 calisiyor...\n");
		int i,j,k;
		
		for(i=0;i<10;i++)
			array2[i]=array[i];
		
		for(k=0;k<10;k++)
			array2[k]=( array[k]*(array[k]+1) )/2;
		printf("T2 alanindaki sayilar: ");					
		for(j=0;j<10;j++){
			if(j!=9)
				printf("%d,",array2[j]);
			else
				printf("%d",array2[j]);
		}
		printf("\n");
		
	}
	
	if(*id==2){

		printf("Process3 calisiyor...\n");
		int j,k;

		for(k=0;k<9;k++)
			array2[k]+=array2[k+1];	
		printf("Hesaplama Sonucu: ");					
		for(j=0;j<9;j++){
			if(j!=8)
				printf("%d,",array2[j]);
			else
				printf("%d",array2[j]);
		}
		printf("\n");		
	
	}

	return NULL;
	
}

int main (){
    int i;                       
    int shmid,shmid2,shmid3;            
    sem_t *sem;                   
    pid_t pid;                    
	key_t key=ftok ("/dev/null", 5); 
    key_t key2=ftok ("/dev/null", 4);
    key_t key3=ftok ("/dev/null", 3);								
		
	// shmget() paylaþýmlý bellekte tahsis iþlemi yapar.	
    shmid = shmget (key2, sizeof (int)*10, 0644 | IPC_CREAT); 		//T1 alaný  için
	shmid2= shmget(key,sizeof(int),IPC_CREAT | 0644);
	shmid3= shmget (key3, sizeof (int)*10, 0644 | IPC_CREAT); 		//T2 alaný	için
	
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
    
	//shmat() paylaþýmlý  belleðin proses tarafýndan kullanýlmasýný saðlar.
    array = (int *) shmat (shmid, NULL, 0); 
	array2 = (int *) shmat (shmid3, NULL, 0);    
 	p= (int *) shmat (shmid2, NULL, 0);
   	*p=0;
   	
    sem = sem_open ("Semaf", O_CREAT | O_EXCL, 0644, 1);  // sem_open() ile isimli semafor oluþturduk ismi:Semaf
    
    sem_unlink ("Semaf");      //eðer semafor çalýþma sýrasýnda bir sorunla karþýlaþýrsa  sem_unlink semaforun yokedilmesini saðlar

    
    for (i = 0; i < 3; i++){
        pid = fork ();
        if (pid < 0)              
            printf ("Fork error.\n");
        else if (pid == 0)		
            break;                  
    }


    
    if (pid != 0){								//Anne proses
        
        while (pid = waitpid (-1, NULL, 0)){	//anne proses sonlanmak için çocuk prosesleri bekliyor 
            if (errno == ECHILD)
                break;
        }

        
        shmdt (array);					//	shmdt() fonksiyonu, prosesin bellek bölgesini kullanýmý sona erdiðinde bellek ile olan iliþkisi bitirmektedir.
        shmctl (shmid, IPC_RMID, 0);	//  Bellek bölgesinin kullanýmý bittiðinde stmctl() kullanýlarak geri verilmelidir..
        
        shmdt (p);
        shmctl (shmid2, IPC_RMID, 0);
        
        shmdt (array2);
        shmctl (shmid3, IPC_RMID, 0);

        sem_destroy (sem);
        exit (0);
    } 

    
    else{										//Çocuk Prosesler
        sem_wait (sem);     					// P iþlemi 
        sleep (1);
        func(p);
        (*p)++;
        sem_post (sem);          				 // V iþlemi 
        exit (0);
    }
}
