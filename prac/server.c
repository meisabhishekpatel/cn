#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>



void func(int fd){
    // send(fd, buf, strlen(buf), 0);
    char buf[500];
    int n;
    for (;;){
        bzero(buf, 500);
        recv(fd, buf, 500, 0);
        printf("from client %s\n To client", buf);
        bzero(buf, 500);
        n = 0;
        while ((buf[n++] = getchar()) != '\n');
        send(fd, buf, strlen(buf), 0);
    }
}

int main(int argc,char* argv[]){
    if(argc!=2){
        perror("Usage: ./server port\n");
        exit(EXIT_FAILURE);
    }
    int port = atoi(argv[1]);
    struct sockaddr_in servaddr, client;
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1){
        perror("Socket creation failed...\n");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Socket successfully created...\n");
    }
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    servaddr.sin_family = AF_INET;
    int bind_status = bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if(bind_status==-1){
        perror("bind error");
        exit(EXIT_FAILURE);
    }
    else
        printf("Bind successfull\n");
    int listen_status = listen(sockfd, 5);
    if(listen_status==-1){
        perror("listen error");
        exit(EXIT_FAILURE);
    }
    else{
        printf("server is listening on %d\n", port);
    }

    int len = sizeof(client);
    int newsfd = accept(sockfd, (struct sockaddr *)&client, &len);
    if(newsfd==-1){
        perror("Accept failed\n");
        exit(EXIT_FAILURE);
    }
    else{
        printf("connection successfull\n");
    }

    func(newsfd);

    close(newsfd);
    close(sockfd);
}
