/*
 *
 *  Created by Akshat Singhal on 12/04/18.
 *
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <pthread.h>

int sockfd = 0;
char id[2];
pthread_t tid1,tid2;

void *read_msg(void *arg)
{
    char str[100];
	read(sockfd,str, 100);
    if(strcmp(str,"exit")==0)
    {
        printf("OK Bye!\n");
        close(sockfd);
        exit(0);
    }
    printf("%c says: %s\n",str[99],str);
    pthread_create(&tid1,NULL,read_msg,NULL);
	return (NULL);
}
void *write_msg(void *arg)
{
    char str[100];
    fflush(stdout);
	scanf("%[^\n]%*c", str);
    str[99] = id[0];
	write(sockfd, str, 100);
    if(strcmp(str,"exit")==0)
    {
        close(sockfd);
        exit(0);
    }
    pthread_create(&tid2,NULL,write_msg,NULL);
	return (NULL);
}
int main(int argc, char *argv[])
{
    int n = 0;
    char recvBuff[1024];int temp;
    struct sockaddr_in serv_addr; 
	char s[100];

    if(argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    } 
	
    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 
	
    memset(&serv_addr, '0', sizeof(serv_addr)); 
	
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); 
	printf("Server address used is: %s\n", argv[1]);
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 
	
    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
		printf("\n Error : Connect Failed \n");
		return 1;
    }
    read(sockfd, id, 5);
    printf("My ID : %c\n", id[0]);
    pthread_create(&tid1,NULL,read_msg,NULL);
    pthread_create(&tid2,NULL,write_msg,NULL);
    while(1);
    return 0;
}
