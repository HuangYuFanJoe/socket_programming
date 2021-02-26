#include <stdio.h>
#include <pthread.h>

struct arg_struct {
    int arg1;
    int arg2;
};

struct Thread_arguments{
    int connfd;
	int count;
	char data[50];
} ;


void *print_the_arguments(void *_args)
{
    struct arg_struct *args = (struct arg_struct *)_args;
    printf("%d\n", args -> arg1);
    printf("%d\n", args -> arg2);
    pthread_exit(NULL);
    return NULL;
}

void *serverThread(void *v_args){
	struct Thread_arguments *args = (struct Thread_arguments *)v_args;


	printf("%d\n", args->count);

    char count[2] = {};
	sprintf(count, "%d", args->count);
	//char filepath[30] = "/data/image";
	//strcat(filepath, count);
	//strcat(filepath, ".png");

	//ssize_t n, total = 0;
	//FILE *fp = fopen(filepath, "wb");
	/*while((n = recv(args->connfd, args->data, MAX_LINE, 0)) > 0){
		total += n;
		if(fwrite(args->data, sizeof(char), n, fp) != n){
			perror("Write File Error");
			exit(1);
		}
		memset(args->data, 0, MAX_LINE);
	}
	fclose(fp);*/
	//close(args->connfd);
	pthread_exit(NULL);
}

int main()
{
    pthread_t some_thread;
    struct arg_struct args;
    args.arg1 = 5;
    args.arg2 = 7;

    struct Thread_arguments arg;

    int count = 0;
    while(1){
		//int connfd = accept(sockfd, (struct sockaddr *) &clientaddr, &addrlen);
		//recv(connfd, RI->requester, MAX_REQUESTER_SIZE, 0);
		//printf("Requester : %s\n",  RI->requester);
		//time_t mytime = time(NULL);
		//RI->date = ctime(&mytime);
		//printf("Date: %s\n", RI->date);
		//args->connfd = connfd;
		arg.count = count;
		printf("%d ", arg.count);
        pthread_t t;
        pthread_create(&t, NULL, &serverThread, (void *)&arg);
        //pthread_join(t, NULL);
		count = (count % 10) + 1;
	}

    if (pthread_create(&some_thread, NULL, &print_the_arguments, (void *)&args) != 0) {
        printf("Uh-oh!\n");
        return -1;
    }

    //return pthread_join(some_thread, NULL); /* Wait until thread is finished */
    return 0;
}
