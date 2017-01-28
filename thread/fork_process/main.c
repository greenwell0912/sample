#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>

static pthread_mutex_t	MyMutex=PTHREAD_MUTEX_INITIALIZER;

void *counter(void *arg)
{
	int i;
	pid_t pid;
	pthread_t thread_id;
	int status;
	char buf[512];

	pid=getpid();
	thread_id=pthread_self();

	printf("\tpid=%d,thread_id=%lu\n",pid,thread_id);

	/* get lock */
	status=pthread_mutex_lock(&MyMutex);
	if(status!=0){
#if (_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && ! _GNU_SOURCE
		strerror_r(status,buf,sizeof(buf));
		fprintf(stderr,"pthread_mutex_lock : %s\n",buf);
#else
		fprintf(stderr,"pthread_mutex_lock : %s\n",strerror_r(status,buf,sizeof(buf)));
#endif
		return (void *)-1;
	}
	printf("\tpid=%d,thread_id=%lu,mutex_lock:OK\n",pid,thread_id);

	for(i=0;i<10;i++){
		sleep(1);
		printf("\tpid=%d,thread_id=%lu,i=%d\n",pid,thread_id,i);
	}

	printf("\tpid=%d,thread_id=%lu end\n",pid,thread_id);

	status=pthread_mutex_unlock(&MyMutex);
	if(status!=0){
#if (_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && ! _GNU_SOURCE
		strerror_r(status,buf,sizeof(buf));
		fprintf(stderr,"pthread_mutex_unlock : %s\n",buf);
#else
		fprintf(stderr,"pthread_mutex_unlock : %s\n",strerror_r(status,buf,sizeof(buf)));
#endif
	}
	else{
		printf("\tpid=%d,thread_id=%lu,mutex_unlock:OK\n",pid,thread_id);
	}
	return (void *)0;
}

int main()
{
	pid_t pid;
	pthread_t thread_id1,thread_id2;
	int status;
	char buf[512];

	printf("Parent pid=%d,thread_id=%lu\n",getpid(),pthread_self());

	/* start thread A */
	status=pthread_create(&thread_id1,NULL,counter,(void *)10);
	pthread_detach(thread_id1);
	if(status!=0){
#if (_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && ! _GNU_SOURCE 
		strerror_r(status,buf,sizeof(buf));
		fprintf(stderr,"pthread_create : %s\n",buf);
#else
		fprintf(stderr,"pthread_create : %s\n",strerror_r(status,buf,sizeof(buf)));
#endif
	}
	else{
		printf("parent pid=%d,thread_id1=%lu\n",getpid(),thread_id1);
	}

	/* start thread B */
	status=pthread_create(&thread_id2,NULL,counter,(void *)10);
	pthread_detach(thread_id2);
	if(status!=0){
#if (_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && ! _GNU_SOURCE 
		strerror_r(status,buf,sizeof(buf));
		fprintf(stderr,"pthread_create : %s\n",buf);
#else
		fprintf(stderr,"pthread_create : %s\n",strerror_r(status,buf,sizeof(buf)));
#endif
	}
	else{
		printf("parent pid=%d,thread_id2=%lu\n",getpid(),thread_id2);
	}

	/* wait 5 sec */
	sleep(5);

	pid=fork();
	if(pid==0){
		printf("fork():Child pid=%d\n",getpid());
		/* child */
		/* unlock, but parent process is not affected */
		status=pthread_mutex_unlock(&MyMutex);
		if(status!=0){
#if (_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && ! _GNU_SOURCE 
			strerror_r(status,buf,sizeof(buf));
			fprintf(stderr,"pthread_mutex_unlock : %s\n",buf);
#else
			fprintf(stderr,"pthread_mutex_unlock : %s\n",strerror_r(status,buf,sizeof(buf)));
#endif
		}
		else{
			printf("Child Process:mutex_unlock:OK\n");
		}
	}

	/* 11 sec later, program is stopped */
	sleep(11);
	printf("parent pid=%d exit\n",getpid());

	pthread_mutex_destroy(&MyMutex);

	return(0);
}
