#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "http.h"

void *
http_null_1_svc(void *argp, struct svc_req *rqstp)
{
	static char * result;

	/*
	 * insert server code here
	 */

	return (void *) &result;
}

response *
http_request1_1_svc(data1 *argp, struct svc_req *rqstp)
{
	static response  result;
	char* http_token = strtok(argp->request, " ");
	char* requested_file = strtok(NULL, " ");

	if (strcmp(http_token, "GET") == 0) {
		if (access(requested_file, F_OK | R_OK) == 0) {
			FILE *file;
			file = fopen(requested_file, "r");
			result.fd = fileno(file);
			//fclose(file);
		} else {
			result.fd = -1;
		}

	} else {
		result.fd = -1;
	}
	return &result;
}

response *
http_request2_1_svc(data2 *argp, struct svc_req *rqstp)
{
	static response  result;
	FILE *file = fdopen(argp->fd, "r");
	result.byte_read_nbr = fread(result.char_read, 1, BUFFER_SIZE, file);
	if (result.byte_read_nbr < BUFFER_SIZE) {
		result.fd = -2;
		fclose(file);
	}
	return &result;
}
