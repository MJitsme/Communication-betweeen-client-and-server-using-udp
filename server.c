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

//function to chat
void chat(int sockfd,SAI client)
{
  int n,len;
  char buff[MAX];
  len=sizeof(client);
  while(1)
  {
    bzero(buff,MAX);
    recvfrom(sockfd,buff,sizeof(buff),0,(SA*)&client,(socklen_t*)&len);
    printf("\nMessage from client : %s",buff);
    if(strncmp(buff,"exit",4)==0)
    {
      printf("Server exits as Client exits...\n");
      break;
    }
    bzero(buff,MAX);
    n=0;
    printf("\nEnter the message to server: ");
    while((buff[n++]=getchar())!='\n');
    sendto(sockfd,buff,sizeof(buff),0,(SA*)&client,&len);
    if(strncmp(buff,"exit",4)==0)
    {
      printf("Server exits...\n");
      break;
    }
  }
}

//main function
int main()
{
  int sockfd;
  SAI server,client;
  sockfd=socket(AF_INET,SOCK_DGRAM,0);
  printf("Socket created successfully");
  server.sin_family=AF_INET;
  server.sin_addr.s_addr=htonl(INADDR_ANY);
  server.sin_port=htons(PORT);

  if(bind(sockfd,(SA*)&server,sizeof(server))==0)
  {
    printf("Binding successful...\n");
  }
  else
  {
    printf("binding failed..");
    return 1;
  }

  chat(sockfd,client);
  close(sockfd);
  return 0;
}
