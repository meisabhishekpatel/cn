#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>



void func(int fd){
    // send(fd, buf, strlen(buf), 0);
    int bufsize = 500;
    int n;
    for (;;){
        // char buf[500];
        // bzero(buf, 500);
        // n = 0;
        // while ((buf[n++] = getchar()) != '\n');
        // send(fd, buf, strlen(buf), 0);
        // bzero(buf, sizeof(buf));
        // recv(fd, buf, strlen(buf), 0);
        // printf("from server %s", buf);

        char buff[bufsize];
        bzero(buff, bufsize);
        printf("Enter the string :");
        n = 0;
        while ((buff[n++] = getchar()) != '\n');
        send(fd,buff,bufsize,0);
        bzero(buff, bufsize);
        recv(fd,buff,bufsize,0);
        printf("From Server: %s\n", buff);
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
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    

    int len = sizeof(client);
    int status = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if(status==-1){
        perror("connect failed\n");
        exit(EXIT_FAILURE);
    }
    else{
        printf("connection successfull\n");
    }

    func(sockfd);

    // close(newsfd);
    close(sockfd);
}
