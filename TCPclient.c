#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

int isPrime(int number){
    int i;
    for (i=2; i < number; i++){
        if (number % i == 0){
            return 0;
        }
    }
    return 1;
}


int main()
{
	// create a socket
	int network_socket;
	network_socket = socket (AF_INET, SOCK_STREAM, 0);

	// specify an andress for the socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	int connection_status = connect(network_socket,(struct sockaddr *) &server_address, sizeof(server_address));
	// check for error with the connection
	if(connection_status == -1){
		printf("Theres was an error making a connection to the remote socket \n\n");
	}

	// receive data from server
	char server_response[256];
	recv(network_socket, &server_response, sizeof(server_response),0);
	printf("-> %s\n\n",server_response);
	

	int intN, validation;
	char charN[20];
	
	while(1){
		
		recv(network_socket, &server_response, sizeof(server_response), 0);

		printf("Consumer: Received %s from server\n",server_response);
		
		intN = atoi(server_response);

		validation = isPrime(intN);
		
		if (validation == 1){

			printf("\t-> Number %s is prime!\n\n",server_response);
		}
		else{	
		
			printf("\t-> Number %s is not prime!\n\n",server_response);
		}		


		if(intN == 0){
			
			break;
		}

		memset(server_response, 0, 256);

		

	}
	
	printf("End of connection...\n\n");
	
	return 0;
}
