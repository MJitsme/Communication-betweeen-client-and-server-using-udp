//importing libraries
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

//defining global variables
#define MAX 100
#define PORT 9014
#define SA struct sockaddr
#define SAI struct sockaddr_in

void chat(int sockfd,SAI server)
{
  int n,len;
  char buff[MAX];
  printf("Client ready to send message\n");
  len=sizeof(server);
  while(1)
  {
    bzero(buff,MAX);
    printf("\nEnter the message to server:");
    n=0;
    while((buff[n++]=getchar())!='\n');
    sendto(sockfd,buff,sizeof(buff),0,(SA*)&server,&len);
    if(strncmp(buff,"exit",4)==0)
    {
      printf("Client exits ....");
      break;
    }
    bzero(buff,MAX);
    recvfrom(sockfd,buff,sizeof(buff),0,(SA*)&server,(socklen_t*)&len);
    printf("Message from server: %s\n",buff);
    if(strncmp(buff,"exit",4)==0)
    {
      printf("Client exits as server exits ....");
      break;
    }
  }
}

//main function
int main()
{
  int sockfd;
  SAI server;
  sockfd=socket(AF_INET,SOCK_DGRAM,0);
  printf("Socket created successfully..\n");
  server.sin_family=AF_INET;
  server.sin_addr.s_addr=htonl(INADDR_ANY);
  server.sin_port=htons(PORT);

  chat(sockfd,server);
  close(sockfd);
  return 0;
}
