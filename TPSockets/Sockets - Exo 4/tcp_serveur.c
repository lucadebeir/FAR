// $Id$

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define PORT 10000

int main(void) {

  /* Socket et contexte d'adressage du serveur */
  struct sockaddr_in sin;
  int sock;
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

  /* Attente d'une connexion client */
	while (1){
		csock = accept(sock, (struct sockaddr*)&csin, &crecsize);
 		printf("Un client se connecte avec la socket %d de %s:%d\n",
         	csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
		pid_t pid= fork();
		if (pid==0){

  /*Envoie d'un message au client*/
  char buffer1[32]="Bonjour !";
  send(csock, buffer1, 32, 0);

  /*Reception d'un message*/
  char buffer3[32]="";
  recv(csock, buffer3, 32, 0);
  printf("Message du client : %s \n", buffer3);

  /* Fermeture de la socket client et de la socket serveur */
  close(csock);
	exit(0);}}
  close(sock);

  return EXIT_SUCCESS;

}//main
