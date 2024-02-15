#include <sys/types.h>   /* cho cac ham lien quan den socket*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <stdio.h> /*cho prinf */
#include <unistd.h> /*cho cac ham lien quan toi he thong */
#include <string.h> /*cho memset() */
#include <stdlib.h>


//tao socket
//goi ham connect de gui connection request toi server
//send and receive data
const int portNumber =54321;

int main(int argc, char ** argv)
{

    //tao socket
    int socketFd= socket(AF_INET,SOCK_STREAM,0);
    if (socketFd < 0){
        perror("socket client failed \n");
        exit(EXIT_FAILURE);
    }
    //mo ta dia chi socket
    struct sockaddr_in stServerAddress;
    memset(&stServerAddress,0,sizeof(stServerAddress));
    stServerAddress.sin_family= AF_INET;
    stServerAddress.sin_port = htons(portNumber);

    //lay address cua server dung ham gethostbyname
    struct hostent *server = gethostbyname("192.168.1.117");

    memcpy((char *)&stServerAddress.sin_addr.s_addr,(char *)server->h_addr,server->h_length);
    
    // goi ham connect
    
    if(connect(socketFd,(struct sockaddr *)&stServerAddress,sizeof(stServerAddress)) <0)
    {
        perror("Error connect to server \n");
        exit(EXIT_FAILURE);
    }
    //send and receive data
    char* msg= "hello from client";
    send(socketFd,msg,strlen(msg),0);
    
    char buffer[1024]={0};
    int n= read (socketFd,buffer,sizeof(buffer));
    printf("Client Receive data: %s \n",buffer);
    if(n <0){
        perror("Read from socket error \n");
        exit(EXIT_FAILURE);
    }
    close(socketFd);
    return 0;
}
