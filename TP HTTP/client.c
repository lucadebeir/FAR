#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#define PORT 10004 //port par défaut

int main(void) {

  int csock;
  struct sockaddr_in sin;

  //le client demande l'URL à l'utilisateur
  char url[256];
  printf("%s\n", "Saisissez une URL :");
  fgets(url,sizeof url, stdin);
  char *pos = strchr(url, '\n');
  *pos = '\0';

  //le client demande le PORT à l'utilisateur
  char port[256];
  printf("%s\n", "Saisissez un PORT :");
  fgets(port,sizeof port, stdin);
  char *pos2 = strchr(port, '\n');
  *pos2 = '\0';

  //calcul de l'IP de l'adresse url
  struct hostent *hp;
  hp = gethostbyname(url);

  if (hp == NULL) {
       printf("gethostbyname() failed\n");
  } else {
     printf("%s = ", hp->h_name);
     unsigned int i=0;
     while (hp -> h_addr_list[i] != NULL) {
        printf( "%s ", inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[i])));
        i++;
     }
     printf("\n");
  }


  //configuration de la Connexion
  sin.sin_addr = *(struct in_addr *) hp->h_addr;
  sin.sin_family = AF_INET;
  sin.sin_port = htons(PORT);

  //création de la socket
  csock = socket(AF_INET, SOCK_STREAM, 0);

  //tentative de Connexion
  char request[1000];
  sprintf(request, "GET / HTTP/1.1\r\nHost: %s\r\n\r\n", url);
  if (connect(csock, (struct sockaddr*)&sin, sizeof(sin))<0) {
    printf("\nError Connecting");
  } else {
    printf("\nSuccessfully connected !\n");
  }
  if (send(csock, request, strlen(request),0)<0) {
    printf("\nError with send()");
  } else {
    printf("\nSuccessfully sent request !\n");
  }

  recv(csock, request, 999, 0);
  printf("\n%s", request);


}
