#include "http.h"
CLIENT *clnt;

int request1(char* request) {
	response *resultat;
	data1 data;
	strcpy(data.request, request);
	resultat = http_request1_1(&data, clnt);
	return resultat->fd;
}

void request2(int fd) {
	response *resultat;
	data2 data;
	data.fd = fd;

	while (1) {
		resultat = http_request2_1(&data, clnt);
		printf("%s", resultat->char_read);
		if (resultat->fd == -2) {
			printf("\nEOF\n");
			break;
		}
	}
}

int main (int argc, char *argv[]) {
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	clnt = clnt_create(host, HTTP, VERSION_UN, "tcp");

	printf("Requete: ");
	char str1[1024];
	fgets(str1, sizeof(str1), stdin);
	char *pos1 = strchr(str1, '\n');
	*pos1 = '\0';

	int fd = request1(str1);
	if (fd >= 0) {
		printf("Fichier ouvert\n");

		request2(fd);

	} else {
		printf("Fichier non trouvé\n");
	}

	exit(0);
}
