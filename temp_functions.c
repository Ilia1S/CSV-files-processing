#include <stdio.h>
#include <stdint.h>
#include "temp_functions.h"

void Help ()
{
	printf("\nTEMPERATURE SENSOR STATISTICS uploads statistics from temperature sensor and compiles reports for year or month.\n");
	printf("prog.exe -f <filename.csv> [-m <month number 1 to 12>]\n");
	printf("   -h \t\t\t Description of the functionality of the app. List of keys and their assignment.\n");
	printf("   -f <filename.csv> \t Input file for processing.\n");
	printf("   -m <month number> \t Use only with \"-f\". If this key is set, statistics are displayed only for the specified month.\n\t\t\t If this key is not set - for the whole year.\n");
}
uint8_t AddInfo (struct sensor* info, char *filename)
{
	FILE *fp;
	fp=fopen(filename, "r");
	int8_t r;
	uint32_t i=0;
	if (fp==NULL)
	{
		printf("Error occured while opening the file\n");
		fclose(fp);
		return 0;
	}
	else
	{
		while ((r=fscanf(fp,"%hu;%hhu;%hhu;%hhu;%hhu;%hhd",&info[i].year,&info[i].month,&info[i].day,&info[i].hour,&info[i].minute,&info[i].temperature))>0)
		{
			if (r<6)
			{
				char s[20];
				r=fscanf(fp,"%[^\n]",s);
				info[i].temperature=-100;
			}
			if (r==0)
				break;
		i++;
		}
		fclose(fp);
		return 1;
	}
}
float AverageM (struct sensor* info, uint8_t monthN)
{
	float sum=0;
	uint32_t i=0,k=0;
	for (i=0;i<SIZE;i++)
	{
		if (info[i].temperature==-100)
			continue;
		if (info[i].month==monthN)
		{
			sum+=info[i].temperature;
			k++;
		}
	}
	if (k==0)
		return -100;
	return sum/k;
}
int8_t MinTempM (struct sensor* info, uint8_t monthN)
{
	int8_t min=100;
	uint32_t i=0;
	for (i=0;i<SIZE;i++)
	{
		if (info[i].month==monthN)
		{
			if (info[i].temperature==-100)
				continue;
			if (info[i].temperature<min)
				min=info[i].temperature;
		}
	}
	if (min==100)
		return -1;
	return min;
}
int8_t MaxTempM (struct sensor* info, uint8_t monthN)
{
	int8_t max=-100;
	uint32_t i=0;
	for (i=0;i<SIZE;i++)
	{
		if (info[i].month==monthN)
		{
			if (info[i].temperature==-100)
				continue;
			if (info[i].temperature>max)
				max=info[i].temperature;
		}
	}
	if (max==-100)
		return -1;
	return max;
}
float AverageY (struct sensor* info, uint16_t yearN)
{
	float sum=0;
	uint32_t i=0,k=0;
	for (i=0;i<SIZE;i++)
	{
		if (info[i].temperature==-100)
			continue;
		if (info[i].year==yearN)
		{
			sum+=info[i].temperature;
			k++;
		}
	}
	return sum/k;
}
int8_t MinTempY (struct sensor* info, uint16_t yearN)
{
	int8_t min=99;
	uint32_t i=0;
	for (i=0;i<SIZE;i++)
	{
		if (info[i].year==yearN)
		{
			if (info[i].temperature==-100)
				continue;
			if (info[i].temperature<min)
				min=info[i].temperature;
		}
	}
	return min;
}
int8_t MaxTempY (struct sensor* info, uint16_t yearN)
{
	int8_t max=-99;
	uint32_t i=0;
	for (i=0;i<SIZE;i++)
	{
		if (info[i].year==yearN)
		{
			if (info[i].temperature==-100)
				continue;
			if (info[i].temperature>max)
				max=info[i].temperature;
		}
	}
	return max;
}
void AllTimeReport (struct sensor* info)
{
	char* mname[] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
	printf("-------------------------------------\n");
	printf("   TEMPERATURE SENSOR STATISTICS   \n");
	printf("-------------------------------------\n");
	printf("     Month |  Min  |  Max  |   Avg  |\n");
	printf("-------------------------------------\n");
	for (int8_t monthN=1;monthN<=12;monthN++)
		if (MinTempM(info,monthN)==-1)
		{
			printf("%11s|        no data         |\n",mname[monthN-1]);
		}
		else
			printf ("%11s|%+7d|%+7d|%+8.1f|\n", mname[monthN-1],+MinTempM(info,monthN),+MaxTempM(info,monthN),+AverageM(info,monthN));
	printf("-------------------------------------\n");
	printf("      Year |  Min  |  Max  |   Avg  |\n");
	printf("-------------------------------------\n");
	for (uint16_t yearN=2021;yearN<=2021;yearN++)
		printf ("%11d|%+7d|%+7d|%+8.1f|\n", yearN,+MinTempY(info,yearN),+MaxTempY(info,yearN),+AverageY(info,yearN));
	printf("-------------------------------------\n");
}
void MonthReport (struct sensor* info,uint8_t monthN)
{
	char* mname[] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
	printf("-------------------------------------\n");
	printf("    TEMPERATURE SENSOR STATISTICS    \n");
	printf("-------------------------------------\n");
	printf("     Month |  Min  |  Max  |   Avg  |\n");
	printf("-------------------------------------\n");
	printf ("%11s|%+7d|%+7d|%+8.1f|\n", mname[monthN-1],+MinTempM(info,monthN),+MaxTempM(info,monthN),+AverageM(info,monthN));
	printf("-------------------------------------\n");
}
