#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h> 
// #include <netinet/in.h> 
#include <netdb.h>

#define bufsize 500

void reverse(char *str)
{
    int len=strlen(str);
    for(int i=0;i<len/2;i++){
        char temp=str[i];
        str[i]=str[len-i-1];
        str[len-i-1]=temp;
    }
}

void func(int fd){
    char buff[bufsize];
    for (;;){
        bzero(buff, bufsize);
        recv(fd,buff,bufsize,0);
        printf("From client: %s\n", buff);
        // bzero(buff, bufsize);
        reverse(buff);
        send(fd,buff,bufsize,0);
        if((strncmp(buff, "exit", 4)) == 0){
            printf("Server Exit...\n");
            break;
        }
    }

}

int main(int argc, char* argv[]){
    if (argc != 2) {
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

    int bind_status = bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

    if (bind_status == -1) {
        perror("Bind failed...\n");
        exit(EXIT_FAILURE);
    }
    else
        printf("Bind successful\n");

    int listen_status = listen(sockfd, 5);
    if (listen_status == -1){
        perror("Listen failed...\n");
        exit(EXIT_FAILURE);
    }
    else
        printf("Server listening..\n");
    int len = sizeof(client);
    int newfd=accept(sockfd,(struct sockaddr*)&client,&len);

    if(newfd==-1){
        perror("Accept failed...\n");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Server accept the client...\n");
    }

    func(newfd);


}
