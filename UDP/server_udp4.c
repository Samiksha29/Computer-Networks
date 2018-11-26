#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<fcntl.h>

#define sourcePORT 4950
#define MAXBUFLEN 50

int main(int argc, char *argv[])
{
	int sockfd,fp,len,cnt=0;
	struct sockaddr_in source_addr;
	struct sockaddr_in their_addr;
	int addr_len, numbytes;
	char buf[11],*fname,ack[2]="0";
	fname=(char *)malloc(sizeof(char)*20);

	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		exit(1);

	source_addr.sin_family = AF_INET;
	source_addr.sin_port = htons(sourcePORT);
	source_addr.sin_addr.s_addr = INADDR_ANY;
	memset(&(source_addr.sin_zero), '\0', 8);

	if(bind(sockfd, (struct sockaddr *)&source_addr, sizeof(struct sockaddr)) == -1)
		exit(1);
	addr_len = sizeof(struct sockaddr);
	if((numbytes = recvfrom(sockfd, fname, MAXBUFLEN-1, 0, (struct sockaddr *)&their_addr, &addr_len)) == -1)
	{
		perror("error while receiving message...");    
		exit(1);
	}
	else
		printf("message received successfully....\n");

	printf("message contains \"%s\"\n", fname);


	fp=open(fname,O_WRONLY|O_CREAT,0600);
	while(recvfrom(sockfd, buf, MAXBUFLEN-1, 0, (struct sockaddr *)&their_addr, &addr_len))
	{
		if(strcmp(buf,"EXIT$")==0)
		{
			printf("\n\nThe file has been transferred\n");
			close(fp);
			close(sockfd);
			return 0;
		}
		len=strlen(buf);	
		while(buf[len-1]!='$')
		{
			strcpy(ack,"0");
			printf("\nPacket No:%d \t received..%c",cnt,ack[0]);
			sendto(sockfd,ack,MAXBUFLEN-1,0,(struct sockaddr *)&their_addr,sizeof(struct sockaddr)); 			
			recvfrom(sockfd, buf, MAXBUFLEN-1, 0, (struct sockaddr *)&their_addr, &addr_len);
			len=strlen(buf);
		}
		strcpy(ack,"1");
		sendto(sockfd,ack,MAXBUFLEN-1,0,(struct sockaddr *)&their_addr,sizeof(struct sockaddr)); 
		write(fp,buf,strlen(buf));
		printf("\nPacket No:%d \t received..%c",cnt,ack[0]);
		cnt++;
		bzero(buf,sizeof(buf));
	}	
	if(close(fp));
	printf("file not received...!\n");
	if(close(sockfd) != 0)
		printf("socket closing failed!\n");

	return 0;
}
