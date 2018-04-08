#include<unistd.h>
#include<stdio.h>
#include<time.h>
int quantum = 3;
int sfront = 0;
int srear = -1;
int tfront = 0;
int trear = -1;
int ttime = 0;
int tqcount =0;
int sqcount = 0;
int flag =0;
struct process
{
	int btime,atime;
	int qtype;// Query type : 0 for teacher and 1 for student
	int tatime;
	int wtime;
	int pno;// process number
	int toc;// time of completion of the process
	int rebtime;
	int inaq;
};
struct process s[1000];
struct process t[1000];
void tenq(struct process e)
{
	trear = trear+1;
	t[trear] = e;
	tqcount++;
}
void tdeq()
{
	if(trear == -1)
	{
		printf("An error with the teacher queue\n");
	}
	else
	{
		tfront = tfront+1;
		tqcount--;
	}
}
void senq(struct process e)
{
	srear = srear+1;
	s[srear] = e;
	sqcount++;
}
void sdeq()
{
	if(srear == -1)
	{
		printf("There is an error with the student queue\n");
	}
	else
	{
		sfront = sfront+1;
		sqcount--;
	}
}
void findwtime(struct process p[],int i)
{
	 // Remaining burst time array from the struct
	for(int j =0; j<i;j++)
	{
		p[j].rebtime =  p[j].btime;
	}
	for(int j =0;j<i;j++)
	{
		if(p[j].atime == 0 && p[j].qtype == 1 && p[j].inaq == 0)
		{
			senq(p[j]);
			p[j].inaq = 1;
		}
	}
	int done;
	while(1)
	{
		done = 1;
		for(int j =0;j<i;j++)
		{
			/* it is done later in the function
			if(p[j].atime <= time && p[j].qtype == 1)// <= to ==
			{
				senq(p[j]);
			}
			*/
			if(p[j].atime == ttime && p[j].qtype == 0 && p[j].inaq == 0)
			{
				tenq(p[j]);
				p[j].inaq = 1;
			}
		}
		if(tqcount!=0 ) // while(tqcount ! = 0)
		{
			int x;
			for(int j = tfront; j<=trear;j++)
			{
				//int x;
				if(t[tfront].rebtime>0)
				{
					done = 0;
					x = t[tfront].pno;
					ttime++;
					t[tfront].rebtime--;
					p[x].rebtime--;
					flag++;
					if(t[tfront].rebtime == 0)
					{
						t[tfront].wtime = ttime-t[tfront].atime-t[tfront].btime;
						p[x].wtime = ttime-p[x].atime-p[x].btime;
						s[tfront].toc = ttime;
						p[x].toc = ttime;
						flag = 0;
						sdeq();
					}
				}
				if(flag == quantum)
				{
					x = t[tfront].pno;
					struct process temp;
					temp = t[tfront];
					tdeq();
					tenq(temp);
				}
			}
		}
		if(tqcount == 0 && sqcount !=0) // while(tqcount == 0)
		{
			int x;
			if(s[sfront].rebtime>0)
			{
				done = 0;
				x = s[sfront].pno;
				ttime++;
				s[sfront].rebtime--;
				p[x].rebtime--;
				flag++;
				if(s[sfront].rebtime == 0)
				{
					s[sfront].wtime = ttime-s[sfront].atime-s[sfront].btime;
					p[x].wtime = ttime-p[x].atime-p[x].btime;
					s[sfront].toc = ttime;
					p[x].toc = ttime;
					flag = 0;
					sdeq();
				}
			}
			if(flag == quantum)
			{
				x = s[sfront].pno;
				struct process temp;
				temp = s[sfront];
				sdeq();
				senq(temp);
			}
			for(int j = 0;j<i;j++)
			{
				if(p[j].atime == ttime && p[j].qtype == 1 && p[j].inaq == 0)
				{
					senq(p[j]);
					p[j].inaq = 1;
				}
			}
			if(sqcount != 0)
			{
				for(int j =0;j<i;j++)
				{
					if(p[j].atime == ttime && p[j].qtype == 0 && p[j].inaq == 0)
					{
						struct process temp;
						temp = p[sfront];
						sdeq();
						senq(temp);
						break;
					}
				}
			}
		}
		/*for(int j = 0; j<i; j++)
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
		*/
		/*
		for(int j =0;j<i;j++)
		{
			if(p[j].rebtime != 0)
			{
				done = 0;
			}
		}*/
		//printf("value of i %d\n",i);
		/*int o = 0;
		for(int j =0;j<i;j++)
		{
			//printf("%d\n",p[j].rebtime);
			if(p[j].rebtime != 0)
			{
				o = 0;
				break;
			}
			else if(p[j].rebtime == 0)
			{
				o = 1;
			}
		}*/
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
		//printf("process p[%d], toc %d",j,p[j].toc);
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
	time_t rawtime;
	time(&rawtime);
	struct tm *tm_struct = localtime(&rawtime);
	int hour = tm_struct->tm_hour;
	if(hour<10 || hour >12)
	{
		//printf("This is the %d hour of the day\n",hour);
		printf("This is %d hour of the day so you cann't access this program\n",hour);
		return 0;
	}
	struct process p[10000];
	/*
	struct process s[10000];
	struct process t[10000];
	*/
	int ch ;// choice
	int i = 0;
	int pcount = 0;//Process count
	int tpcount =0; // teacher process count
	int spcount =0 ;// student process count
	while(1)
	{
		ch = 0;
		printf("\nPress 1 to enter process\n");
		printf("Press 0 to exit\n");
		scanf("%d",&ch);
		if(ch == 1)
		{
			//char c;
			int c;
			printf("\nEnter '1' for student process ; Enter '0' for teacher proces \n");
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
					printf("\nEnter the Arrival time for process %d :\n",pcount+1);
					scanf("%d",&p[i].atime);
					printf("Enter the burst time for process %d:\n",pcount+1);
					scanf("%d",&p[i].btime);
					p[i].pno = pcount;
					p[i].qtype = 1;
					p[i].inaq = 0;
					i++;
					spcount++;
					pcount++;
					break;
				case 0 :
					printf("\nEnter the arrival time for process %d :\n",pcount+1);
					scanf("%d",&p[i].atime);
					printf("Enter the burst time for process %d :\n",pcount+1);
					scanf("%d",&p[i].btime);
					p[i].pno = pcount;
					p[i].qtype = 0;
					i++;
					p[i].inaq = 0;
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

