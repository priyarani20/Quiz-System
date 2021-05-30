#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#define MAXLINE 1024

int main(int argc,char* argv[])
{
	  int sockfd;
	  int n;
	  socklen_t len;
	  char sendline[1024],recvline[1024];
	  char name[20];
	  struct sockaddr_in servaddr;

	  printf("\n\t\t\t**** WELCOME TO QUIZ SYSTEM ****");
	  printf("\n");
  
	  sockfd=socket(AF_INET,SOCK_DGRAM,0);  // creating socket
	  servaddr.sin_family=AF_INET;
	  servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	  servaddr.sin_port=htons(5035);
	  len=sizeof(servaddr);
	  sendto(sockfd,sendline,MAXLINE,0,(struct sockaddr*)&servaddr,len);  // sending message to server
	
	  for(int i=0; i<5;i++)
	  {
		  n=recvfrom(sockfd,recvline,MAXLINE,0,NULL,NULL);
		  recvline[n]=0;
		  printf("\nInterviewer : %s\n",recvline);
		  printf("\n\t\t Your answer: ");
		  fgets(sendline,1024,stdin);
		  sendto(sockfd,sendline,MAXLINE,0,(struct sockaddr*)&servaddr,len);
		  n=recvfrom(sockfd,recvline,MAXLINE,0,NULL,NULL);
		  printf("\nInterviewer : %s\n",recvline);
	  }
	  n=recvfrom(sockfd,recvline,MAXLINE,0,NULL,NULL);  // receiving score from server
      printf("\n\t\t *****************************");
      printf("\n\t\t     Your Total Score: %s\n",recvline);
      printf("\n\t\t          Thank You! \n");
      printf("\t\t ***************************** \n");
  return 0;
}
