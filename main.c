#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "temp_functions.h"

int main(int argc, char **argv)
{
	if (argc==1)
	{
		printf ("Hello! Welcome to TEMPERATURE SENSOR STATISTICS app\nEnter \"prog.exe -h\" for help\n");
		return 0;
	}
	else
	{
		static uint8_t monthN=0,h=0;
		static char *filename=0;
		int8_t rez=0;
		while ((rez=getopt(argc,argv, "hf:m:"))!=-1)
		{
			switch (rez)
			{
				case '?':
					printf("Enter \"prog.exe -h\" for help\n");
					return 1;
				break;
				case 'h':
					h=1;
				break;
				case 'f':
					filename=optarg;
				break;
				case 'm':
					monthN=atoi(optarg);
					if (monthN<1 || monthN>12)
					{
						printf ("Month number must be between 1 and 12.\n");
						return 0;
					}	
				break;
			}
		}
		if (h==1)
			Help();
		else 
		{
			if (argc>5)
				printf("Too many arguments. Enter \"prog.exe -h\" for help/n");
			else
			{
				struct sensor* info=malloc(SIZE*sizeof(struct sensor));
				if (argc==3 && filename!=0)
				{
					if (AddInfo(info,filename)!=0)
					{
						printf ("Reading file %s...\n",filename);
						AllTimeReport(info);
					}
				}
				if (argc==5 && monthN!=0)
				{
					if (AddInfo(info,filename)!=0)
					{
						printf ("Reading file %s...\n",filename);
						MonthReport (info,monthN);
					}
				}				
				if (argc==3 && monthN!=0)
					printf ("\"-m\" key use only with \"-f\" key\n");
			}
		}
		return 0;
	}
}
