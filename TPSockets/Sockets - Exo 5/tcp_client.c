// $Id$

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#define PORT 10000

int continu=1;

void fermerC(){
	continu = 0;
}

int main(void) {

  signal (SIGINT, fermerC);
  int sock;
  struct sockaddr_in sin;

  /* Création de la socket */
  sock = socket(AF_INET, SOCK_STREAM, 0);
 
  /* Configuration de la connexion */
  sin.sin_addr.s_addr = inet_addr("127.0.0.1");
  sin.sin_family = AF_INET;
  sin.sin_port = htons(PORT);
 
  /* Tentative de connexion au serveur */
  connect(sock, (struct sockaddr*)&sin, sizeof(sin));
  printf("Connexion a %s sur le port %d\n", inet_ntoa(sin.sin_addr),
         htons(sin.sin_port));

  /*Reception message serveur */
  char buffer[32]="";
  recv(sock, buffer, 32, 0);
  printf("Message du serveur : %s \n", buffer);

  /*envoie d'un message au serveur*/
while(continu==1) {
	char buffer2[32]="";
	char *pos;
	printf("Entrez un message pour le serveur : \n");
	fgets(buffer2,32, stdin);
	pos = strchr(buffer2, '\n');
	*pos = '\0';
	send(sock, buffer2, 32, 0);
}

  /* Fermeture de la socket client */
  close(sock);

  return EXIT_SUCCESS;

}//main
