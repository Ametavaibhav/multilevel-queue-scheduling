
#include<unistd.h>
#include<stdio.h>
int quantum = 3;
struct process
{
	int btime,atime;
	int qtype;// Query type : 0 for teacher and 1 for student
	int tatime;
	int wtime;
	int pno;// process number
	int toc;// time of completion of the process
};
void findwtime(struct process p[],int i)
{
	int rebtime[i];   // Remaining burst time array
	for(int j =0; j<i;j++)
	{
		rebtime[j] =  p[j].btime;
	}
	int time =0;
	while(1)
	{
		int done;
		done = 1;
		for(int j = 0; j<i; j++)
		{
			if(rebtime[j]>0)
			{
				done = 0;
				if(rebtime[j]>=quantum)
				{
					time = time+quantum;
					rebtime[j] = rebtime[j]-quantum;
				}
				else
				{
					time = time+rebtime[j];
					p[j].wtime = time - p[j].btime - p[j].atime;
					rebtime[j] = 0;
					p[j].toc = time;
				}
			}
		}
		//printf("total time%d\n",time);
		if(done == 1)
		{
			break;
		}
	}
}
void findtatime(struct process p[],int i)
{
	for(int j =0;j<i;j++)
	{
		p[j].tatime = p[j].toc - p[j].atime;
	}
}
void findavgtime(struct process p[],int i)
{
	findwtime(p,i);
	findtatime(p,i);
	printf("Process number\t\tArrival time\t\tBurst time\t\tWaiting time\t\tTurn aroundtime\t\tprocess type\n");
	for(int j =0;j<i;j++)
	{
		printf("%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n",(j+1),p[j].atime,p[j].btime,p[j].wtime,p[j].tatime,p[j].qtype);
	}
}
int main()
{
	struct process p[10000];
	int ch ;// choice
	int i = 0;
	int pcount = 0;//Process count
	int tpcount =0; // teacher process count
	int spcount =0 ;// student process count
	while(1)
	{
		ch = 0;
		printf("Press 1 to enter process\n");
		printf("Press 0 to exit\n");
		scanf("%d",&ch);
		if(ch == 1)
		{
			//char c;
			int c;
			printf("Enter '1' for student process ; Enter '0' for teacher proces \n");
			scanf("%d",&c);
			//scanf("%s",&c);
			/*
			if(c == 's'){u = 1;}
			else if(c == 't'){u == 2;}
			else {u == 3;}
			*/
			switch(c)
			{
				case 1:
					printf("Enter the Arrival time for process %d :\n",pcount+1);
					scanf("%d",&p[i].atime);
					printf("Enter the burst time for process %d:\n",pcount+1);
					scanf("%d",&p[i].btime);
					p[i].pno = pcount;
					p[i].qtype = 1;
					i++;
					spcount++;
					pcount++;
					break;
				case 0 :
					printf("Enter the arrival time for process %d :\n",pcount+1);
					scanf("%d",&p[i].atime);
					printf("Enter the burst time for process %d :\n",pcount+1);
					scanf("%d",&p[i].btime);
					p[i].pno = pcount;
					p[i].qtype = 0;
					i++;
					tpcount++;
					pcount++;
					break;
				default :
					printf("You entered a wrong key!! Try again !!\n");
					break;
			}
		}
		else if(ch ==0 )
		{
			break;
		}
		else
		{
			printf("You entered a wrong key!! Try again !!\n");
		}
	}
	findavgtime(p,i);
	printf("total no of processes : %d\n",pcount);
	printf("total no of student processes : %d\n",spcount);
	printf("total no of teachet processes : %d\n",tpcount);
}

