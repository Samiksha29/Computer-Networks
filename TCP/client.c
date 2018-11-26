#include<string.h>
#include<sys/ioctl.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<net/if_arp.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	int sockfd,c;
	char fname[50],sip[25],*buff;
	buff=(char *)malloc(sizeof(char)*10);
	struct sockaddr_in caddr;

	int fp;

	if ((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		printf("\n Socket failure");
		exit(1);
	}
	caddr.sin_family=AF_INET;
	caddr.sin_port=htons(3490);
	caddr.sin_addr.s_addr=inet_addr("192.168.1.1");

	if(c=connect(sockfd,(struct sockaddr*)&caddr,sizeof(caddr))<0)
	{
		perror("connect");
		exit(1);
	}
	if(c==0)
		printf("\nconnected to server");
	printf("\nenter the file name - ");
	scanf("%s",fname);
	if((send(sockfd,fname,sizeof(fname),0))==-1)
	{
		printf("Failure Sending Message\n");
		close(sockfd);
		exit(1);
	}
	fp=open(fname,O_RDONLY,0640);

	while(read(fp,buff,sizeof(buff)	))
	{
		printf("%s",buff);
		if((send(sockfd,buff,strlen(buff),0))==-1)
		{
			printf("Failure Sending Message\n");
			close(sockfd);
			exit(1);
		}
		bzero(buff,sizeof(buff));
	}


	close(fp);
	close(sockfd);

	return 0;
}
