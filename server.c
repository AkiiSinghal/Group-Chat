/*
 *
 *  Created by Akshat Singhal on 12/04/18.
 *
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>

#define MAX 5
int connfd[MAX] = {0};
int i, e[MAX] = {0};
pthread_t tid2;
pthread_t tid[MAX];

void *read_msg(void *arg)
{
    int k = *(int *)arg;
    int l;
    char str[100];
	read(connfd[k],str, 100);
    if(strcmp(str,"exit")==0)
    {
        printf("Client %c is Offline\n",(char)(65+k));
        close(connfd[k]);
        return (NULL);
    }
    for(l=0;l<i;l++)
        if(l!=k)
            write(connfd[l], str, 100);
	printf("%c says: %s\n",str[99],str);
    pthread_create(&tid[k],NULL,read_msg,(void *)&k);;
	return (NULL);
}
void *write_msg(void *arg)
{
    int l;
    char str[100];
    fflush(stdin);
	scanf("%[^\n]%*c", str);
    str[99] = 'S';
    for(l=0;l<i;l++)
        write(connfd[l], str, 100);
    if(strcmp(str,"exit")==0)
        exit(0);
    pthread_create(&tid2,NULL,write_msg,NULL);
	return (NULL);
}
int main(int argc, char *argv[])
{
    int listenfd = 0;
    struct sockaddr_in serv_addr;
    char sendBuff[1025];
	int temp;
    time_t ticks;
    char C_name[MAX][2];
    int j[MAX];
	
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 
	
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 
	
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
	
    listen(listenfd, 10);
    
    for (i = 0; i < MAX; ++i)
    {
        C_name[i][0] = (char)(65+i);
        C_name[i][1] = '\n';
        j[i] = i;
    }
    printf("My ID : S\n");
    pthread_create(&tid2,NULL,write_msg,NULL);
    for(i = 0; i < MAX; i++)
    {
        connfd[i] = accept(listenfd, (struct sockaddr*)NULL, NULL);
        write(connfd[i], C_name[i], 5);
        printf("Client %c is Online\n",C_name[i][0]);
        pthread_create(&tid[i],NULL,read_msg,(void *)(j+i));
    }
    
}
