#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h> 
// #include <netinet/in.h> 
#include <netdb.h>


void func(int fd){
    int bufsize = 500;
    int n;
    for (;;)
    {
        char buff[bufsize];
        bzero(buff, bufsize);
        n = 0;
        while ((buff[n++] = getchar()) != '\n');
        send(fd,buff,bufsize,0);
        bzero(buff, bufsize);
        recv(fd,buff,bufsize,0);
        printf("From Server: %s\n", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}

int main(int argc,char * argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int port = atoi(argv[1]);
    int sockfd, connfd;
    struct sockaddr_in servaddr,client;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1) {
        perror("socket creation failed...\n");
        exit(EXIT_FAILURE);
    }
    else
        printf("Socket successfully created..\n");

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    int connect_status = connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    if(connect_status==-1){
        perror("Connection failed...\n");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Connected to the server..\n");
    }
    func(sockfd);
}