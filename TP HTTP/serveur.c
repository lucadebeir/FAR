// $Id$

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#define PORT 10004


void tuerZombie() {
  wait(0);
}

int main(void) {

  /* Socket et contexte d'adressage du serveur */
  struct sockaddr_in sin;
  int sock;
  signal (SIGCHLD, tuerZombie);
  socklen_t recsize = sizeof(sin);

  /* Socket et contexte d'adressage du client */
  struct sockaddr_in csin;
  int csock;
  socklen_t crecsize = sizeof(csin);

  /* Création d'une socket */
  sock = socket(AF_INET, SOCK_STREAM, 0);

  /* Configuration */
  sin.sin_addr.s_addr = htonl(INADDR_ANY);  /* Adresse IP automatique */
  sin.sin_family = AF_INET;                 /* Protocole familial (IP) */
  sin.sin_port = htons(PORT);               /* Listage du port */
  bind(sock, (struct sockaddr*)&sin, recsize);


  /* Démarrage du listage (mode server) */
  listen(sock, 5);
while(1) {
  /* Attente d'une connexion client */
	csock = accept(sock, (struct sockaddr*)&csin, &crecsize);
 	printf("Un client se connecte avec la socket %d de %s:%d\n",
       	csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
	pid_t pid= fork();
	char buffer2[32]="";
	if (pid==0){

    recv(csock, buffer2, 32, 0);
    char *tok = strtok(buffer2," ");

    if(strcmp(tok,"GET")==0){ //vérifie si c'est bien une requête GET
      printf("La socket %d envoie une requete de type GET\n",csock);
      tok=strtok(NULL," ");
      if(strcmp(tok,"/")==0){ //s'il n'y a qu'un slash après GET, on envoie le fichier index.html au client (fichier par défault)
        tok="index.html";
      }
      FILE* request = NULL;
      request = fopen(tok,"r"); //permet de récupérer ce qu'il y a écrit dans le fichier
      char fichier[300] ="";
      if(request!=NULL){
            fgets(fichier, 300, request);
						send(csock, fichier, strlen(fichier), 0); //on l'envoie au client grâce à une socket
						fclose(request);
      }
    }
    tok = strtok(NULL," ");
    printf("%s\n",tok);
    printf("Un client se déconnecte avec la socket %d de %s:%d\n",csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
    shutdown(csock,2);
    exit(0);
  }

  /* Fermeture de la socket client et de la socket serveur */
  close(csock);}
  close(sock);

  return EXIT_SUCCESS;

}//main
