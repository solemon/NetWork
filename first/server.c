//printf
#include <stdio.h>
//exit
#include <stdlib.h>
//close, open, read, write
#include <unistd.h>
//memset
#include <string.h>

//htons inet_addr
#include <arpa/inet.h>

//socket bind connect send recv
#include <sys/types.h>
#include <sys/socket.h>

#define SERVER_PORT 8888
#define SERVER_IP "127.0.0.1"
#define QUEUE 10
int create_socket(){
	int sock_fd;
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if( sock_fd == -1 ){
		perror("socket create failed\n");
		exit(1);
	}
	return sock_fd;
}
void bind_port(int sock_fd){
	struct sockaddr_in server;

	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	if( bind(sock_fd, (struct sockaddr*)(&server), sizeof(struct sockaddr))== -1)
	{
		perror("bind error");
		exit(1);
	}
	return;
}
void listen_port(int sock_fd){
	if( listen(sock_fd, QUEUE) != 0 ){
		perror("listen error");
		exit(1);
	}
}

int start_up(){
	int sock_fd;
	sock_fd = create_socket();
	bind_port(sock_fd);
	listen_port(sock_fd);
	printf("startup successful!\n");
	return sock_fd;
}

void accept_req(int sock_fd){
	struct sockaddr_in client;
	socklen_t len = sizeof(client);
	while(1){
		int client_fd = accept(sock_fd, (struct sockaddr*)(&client), &len);
		if( client_fd == -1){
			perror("accept error");
			return;
		}
		printf("The client ip is :%s\n", inet_ntoa(client.sin_addr));
		printf("The client port is :%d\n", client.sin_port );
		close(client_fd);
	}
	return;
}

int main(int argc, char *argv[]){
	int sock_fd = start_up();
	accept_req(sock_fd);
	close(sock_fd);
	return 0;
}
