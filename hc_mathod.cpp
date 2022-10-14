#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <float.h>
#define PI 3.14
int totaldatanumber;
struct a
	{
		int x;
		int y;
	};
	
	typedef struct a element;
	struct b
	{
		int time;
		int path;
	};
	
	typedef struct b timepath;
void shuffle(int[] );
void swap(int[],int,int );
double finddistance(int[],element[]);
void writedata(int a,int b);
element* readdata();
int main(void)
{
	double start_time;
	double end_time;
	double totalpath;
	int findtime = 0,pick1,pick2;
	double distance;
	double smallest_dis;
	element *data;
	int writedistance;
	int i;
	FILE *out,*out2;
	out = fopen("outtime.txt","w");
	fclose(out);
	out2 = fopen("outpath.txt","w");
	fclose(out2);
	data = readdata();
	
	int order[totaldatanumber];
	for(i = 0;i<totaldatanumber;i++)
		order[i] = i;
	srand(time(NULL));
	start_time = clock();

	shuffle(order);
	smallest_dis = finddistance(order,data);
	writedata(findtime,smallest_dis);
	findtime++;
	end_time = clock();	
	printf("目前找的次數是:%d ,最短距離是:%f ,找到時間是:%f \n",findtime,smallest_dis,(double)(end_time - start_time)/1000);
	while(findtime <=100000)
	{
		distance = 0;
		
		do
		{
		pick1 = (int)rand()%totaldatanumber;
		pick2 = (int)rand()%totaldatanumber;
		}while(pick1 == pick2);
		swap(order,pick1,pick2);
		distance = finddistance(order,data);
		if(findtime%2000 == 0)
		{              //writedata
		writedistance = (int)(distance);
		writedata(findtime,writedistance);
		}
		if(distance<smallest_dis)
		{
			smallest_dis = distance;
			end_time = clock();	
			printf("目前找的次數是:%d ,最短距離是:%f ,找到時間是:%f \n",findtime,smallest_dis,(double)(end_time - start_time)/1000);
		}
		else
		swap(order,pick1,pick2);
		findtime++;
	}
	printf("最短的順序是:");
	for(i = 0;i<totaldatanumber;i++)
	{
		if(i == totaldatanumber-1)
		printf("%d\n",order[i]);
		else
		printf("%d->",order[i]);
	}
system("pause");
return 0;
}


void shuffle(int a[])
{
	int i;
	int randnum;
	for(i = 0 ;i<totaldatanumber;i++)
	{
		randnum = (int)(rand()%(i+1));
		swap(a,i,randnum);
	}
}

void swap(int a[],int b,int c)
{
	int temp;
	if(b == c)
	return;
	else
	{
		temp = a[b];
		a[b] = a[c];
		a[c] = temp;
		return;
	}
	
}

double finddistance(int order[],element *data)
{
	int i;
	double xdis;
	double ydis;
	double tempdis;
	double totaldis = 0;
	for(i = 0;i<totaldatanumber-1;i++)
	{
		
		xdis= data[order[i+1]].x - data[order[i]].x;
		
		ydis= data[order[i+1]].y - data[order[i]].y;
		tempdis = sqrt((pow(xdis,2)+pow(ydis,2)));
		totaldis += tempdis; 
	}
		xdis= data[order[0]].x - data[order[totaldatanumber-1]].x;   //頭到尾距離 
		ydis= data[order[0]].y - data[order[totaldatanumber-1]].y;
		tempdis = sqrt((pow(xdis,2)+pow(ydis,2)));
		totaldis += tempdis; 
		return totaldis;
}

void writedata(int a,int b)
{
	
	char time[10] = {0},path[10] = {0},copy[10] = {0};
	FILE *ptr,*ptr2;
	int c;
	int bit;
	int i;
	int j ;
	ptr = fopen("outtime.txt","a");
	ptr2 = fopen("outpath.txt","a");
	bit = 0;
	do
	{
		c = a%10;
		copy[bit] = c+48;
		a = a/10; 
		if(a != 0 )
		bit++;
	}while(a!=0);
	j = 0;
	for(i = bit;i>=0;i--)
	{
	 time[j] = copy[i];
	j++;
	}
	bit = 0;
	copy[10] = {0};
	do
	{
		c = b%10;
		copy[bit] = c+48;
		b = b/10;
		if(b != 0 ) 
		bit++;
	}while(b!=0);
	j = 0;
	for(i = bit;i>=0;i--)
	{
	 path[j] = copy[i];
	j++;
	}
	fputs(time,ptr);
	putc('\n',ptr);
	fputs(path,ptr2);
	putc('\n',ptr2);
	printf("time:%s ,path:%s\n",time,path);
	fclose(ptr);
	fclose(ptr2);
	
}


element* readdata(void)
{
	int i = 0;
	char number[10] = {0},xais[10]= {0},yais[10]= {0},ch;
	int intnumber,intxais,intyais;
	FILE *input;
	element *data;
	input = fopen("inputdata.txt","r");
	data = (element *) malloc(1*sizeof(element));
	while(feof(input)==0)
	{
		i = 0;
		while((ch = getc(input))!=' ')
		{
			number[i] = ch;
			i++;
		}
		intnumber = atoi(number);
		data = (element *)realloc(data,sizeof(element)*intnumber) ;
		for(i = 0;i<10;i++)
		number[i] = 0; 
		i = 0;
		while((ch = getc(input))!=' ')
		{
			xais[i] = ch;
			i++;
		}
		intxais = atoi(xais);
	    (data+intnumber-1)->x = intxais; 
	    for(i = 0;i<10;i++)
		xais[i] = 0;
		i = 0;
		while((ch = getc(input))!='\n')
		{
			if(ch == EOF)   //不能漏   不然最後一行讀不進去 
			break;
			yais[i] = ch;
			i++;
		}
		intyais = atoi(yais);
	    (data+intnumber-1)->y = intyais; 
	    for(i = 0;i<10;i++)
		yais[i] = 0;
		i = 0;    
	    printf("%d ,%d ,%d\n",intnumber,(data+intnumber-1)->x,(data+intnumber-1)->y);
	}
	totaldatanumber = intnumber;
	fclose(input);
return data;
}













