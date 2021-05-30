#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#define MAXLINE 1024

int main(int argc,char **argv)
{
	  int sockfd;
	  int n;
	  socklen_t len;
	  char msg[1024],sendmsg[1024];
	  struct sockaddr_in servaddr,cliaddr;
	  sockfd=socket(AF_INET,SOCK_DGRAM,0);          // creating socket
	  servaddr.sin_family=AF_INET;                 // getting internet address (type of address  i.e IPv4)
	  servaddr.sin_addr.s_addr=INADDR_ANY;        // getting IP address the PC
	  servaddr.sin_port=htons(5035);             //  port number
	  bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)); // binding socket and structure variable
	  printf("\nBinded");
	  printf("\nListening...");
	  printf("\n ");
	  
	    while(1)      // running server in infinite loop for accepting multiple requests
        {
		    len=sizeof(cliaddr);

			//Questions set
			const char* questions[5] = {"\tQ1. What is the name of capital of India?\n\t\t    1. Delhi\n\t\t    2. Bhubaneswar\n\t\t    3. Mumbai\n\t\t    4. Agra\n",
			"\tQ2. The ASCII value of A is?\n\t\t    1. 65\n\t\t    2. 97\n\t\t    3. 68\n\t\t    4. 123\n",
			"\tQ3. The structure or format of data is called ___________ \n\t\t    1.Semantics\n\t\t    2.Struct\n\t\t    3.Syntax\n\t\t    4.Formatting\n",
			"\tQ4. How long is an IPv6 address?\n\t\t    1. 32 bits\n\t\t    2. 128 bytes\n\t\t    3. 64 bits\n\t\t    4. 128 bits\n",
			"\tQ5. CRC stands for __________ \n\t\t    1.code repeat check\n\t\t    2.cyclic redundancy check\n\t\t    3.code redundancy check\n\t\t    4.cyclic repeat check\n"};
			
			int answer[5] = {1,1,3,4,2};      // answer array mapped with question array
			n=recvfrom(sockfd,msg,MAXLINE,0,(struct sockaddr*)&cliaddr,&len);  // receiving data from client
			int total=0;
	 
			for(int i=0; i<5;i++)
			{
				strcpy(sendmsg,questions[i]);
				sendto(sockfd,sendmsg,n,0,(struct sockaddr*)&cliaddr,len); 
				n=recvfrom(sockfd,msg,MAXLINE,0,(struct sockaddr*)&cliaddr,&len);
				printf("\n Candidate : %s\n",msg);
				int ans=-1;
				sscanf(msg, "%d", &ans);
				
				if(ans==answer[i])
				{
					strcpy(sendmsg,"Correct Answer!\n");
				    total++;
				}
				else
				{
					strcpy(sendmsg,"Wrong Answer!\n");
				}
			sendto(sockfd,sendmsg,n,0,(struct sockaddr*)&cliaddr,len);  // sending correct/wrong answer message to client
			}
		char score[5];
		sprintf(score, "%d", total);
		strcpy(sendmsg,score);
		sendto(sockfd,sendmsg,n,0,(struct sockaddr*)&cliaddr,len);   //sending score to client
        }
return 0;
}
