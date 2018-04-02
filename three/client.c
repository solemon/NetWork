//printf
#include <stdio.h>
//ecit
#include <stdlib.h>

//memset
#include <string.h>

//htons inet_addr
#include <arpa/inet.h>

//socket bind connect send recv
#include <sys/types.h>
#include <sys/socket.h>

#define SERVER_PORT 8888
#define SERVER_IP "127.0.0.1"

int create_socket(){
	int sock_fd;
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if( sock_fd == -1 ){
		perror("socket create failed\n");
		exit(1);
	}
	return sock_fd;
}

void con_server(int sock_fd){
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port=htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	if( connect(sock_fd, (struct sockaddr*)(&server_addr), sizeof(struct sockaddr)) == -1 ){
		perror("Connect Error!\n");
		exit(1);
	}
	printf("Connect successful\n");
	return;
}

int main(int argc, char *argv[]){
	
	int sock_fd;

	sock_fd = create_socket();
	con_server(sock_fd);

	char recv_msg[1024];
	//need memset function before useing recv_msg;
	int recv_len = recv(sock_fd, recv_msg, sizeof(recv_msg), 0);
	recv_msg[recv_len] = '\0';
	printf("I have recved message:%s\n", recv_msg);
	return 0;
}
