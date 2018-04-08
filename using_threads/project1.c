#include<unistd.h>
#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/wait.h>
void *studentfun()
{
	printf("Welcome Student\n");
}
void *teacherfun()
{
	printf("Welcome Teacher\n");
}
int main()
{
	int n;
	int threadcount = -1;
	int teachercount =0;
	int studentcount = 0;
	pthread_t p[1000];
	while(1)
	{
		printf("Enter 1 if you are a student and 2 if you are a teacher and 0 to exit the program\n");
		scanf("%d",&n);
		//threadcount++;
		if(n == 1)
		{
			threadcount++;
			studentcount++;
			pthread_create(&p[threadcount],NULL,studentfun,NULL);
			pthread_join(p[threadcount],NULL);
		}
		else if(n == 2)
		{
			threadcount++;
			teachercount++;
			pthread_create(&p[threadcount],NULL,teacherfun,NULL);
			pthread_join(p[threadcount],NULL);
		}
		else if(n == 0)
		{
			break;
		}
		else
		{
			printf("Enter your choice correctly\n");
		}
	}
	printf("total number of queries handled : %d\n",(threadcount+1));
	printf("total number of student queries handled :%d\n",studentcount);
	printf("total number of teacher queries handled :%d\n",teachercount);
}
