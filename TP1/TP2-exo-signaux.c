#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void traitement () {
	printf("L'entier est négatif !\n");
}

int main(void) {
	pid_t pid;
	int p[2];
	pipe(p);
    pid=fork();
	if (pid==0) {
		while(1) {
			close(p[1]); //le fils ne peut que lire, et pas écrire dans le tube
			int nombre;
			read(p[0],&nombre,sizeof(int));
			if (nombre<0) {
				kill(getppid(),SIGUSR1); //émission du signal
			}
                //return EXIT_SUCCESS; à mettre que quand le programme finit ! pas le cas ici
        }
	}
	else {

		while(1) {
			signal(SIGUSR1,traitement); //réception du signal				
			close(p[0]); //le père ne peut que écrire et pas lire dans le tube
			int nombre;
			printf("Entrez un entier :\n"); /*Demande d'un entier*/
		    scanf("%d",&nombre); /*Saisie d'un entier*/
			write(p[1], &nombre, sizeof(int));
			sleep(1);
        }
	}   
}    


