#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
        pid_t pid;
        int descr[2];
        char buffer[256];
        int nombre;
        int somme=0;
        int cpt=0;
        pipe(descr);
        pid=fork();
        if (pid==0) {
                close(descr[0]); /*le fils ne peut pas lire, il ne peut que écrire*/
                int nombre;
                int reponse;
                do {
                        printf("Entrez un entier :\n"); /*Demande d'un entier*/
                        scanf("%d",&nombre); /*Saisie d'un entier*/
                        write(descr[1], &nombre, sizeof(int));
                        printf("Saisir un autre entier (0 si oui / 1 si non) : \n");
                        scanf("%d", &reponse);
                }
                while (reponse == 0);
                return EXIT_SUCCESS;
        }       
        else {
                close(descr[1]);
                int nombre;
                while (read(descr[0],&nombre,sizeof(int)) != 0) {
                        somme=somme+nombre;
                        cpt=cpt+1;
                }
                int moy=somme/cpt;
                printf("Moyenne = %d\n",moy);
        }
}
