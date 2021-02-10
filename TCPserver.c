#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

int randomNumber(int number){

	number = number +(rand()%100+1);

	return number;
}

int totalNumbers(){

	int numbers;
	printf("How many number would you like the program to generate ?"); scanf("%d",&numbers);

	return numbers;
}

int main(){

	char server_message[256] = "You have reached the server!";

	// create the server socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	//define the server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	// bind the socket to our specified IP and port
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

	listen(server_socket, 5);

	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);

	// send the message
	send(client_socket, server_message, sizeof(server_message), 0);

	// generating the random number (begins with value 1)
	int intN = 1;
	char charN[20];

	printf("Server Started!\n");

	int totalProducts;

	totalProducts = totalNumbers();

	printf("\nStarting now...\n");

	// sending the number
	for(int i = 1; i <= totalProducts; i++){

		if(i == totalProducts){

			intN = 0;

		}
		sprintf(charN, "%d", intN);

		send(client_socket, charN, sizeof(charN), 0);
		
		printf("Producer: Just sent number -> %s\n\n", charN);
		
		sleep(3);
		
		intN = randomNumber(intN);
	}
	
	// close the socket
	close(server_socket);

	printf("End of connection...\n\n");
	
	return 0;
}